
#ifndef Expert_Version_3_0
#define Expert_Version_3_0


#include <cstdio>
#include <cstdlib>

#include <windows.h>

using namespace std;

//for functions begin

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//for functions end

struct ssylka
{
    char Ntype; //0_ --      1_Any asss  2_any conv  3_objects   4_conversions   5_bad ssylka
    int x1;     //Numb       Nass        Numb        Nname       Numb
    int x2;     //-          Nvariants   -           Nargs       -
    int x3;     //-          -           -           Nvariants   -

    ssylka()
    {
        Ntype = 0;
        x1 = 0;
        x2 = 0;
        x3 = 0;
    }

    ssylka(char a, int b = 0, int c = 0, int d = 0)
    {
        Ntype = a;
        x1 = b;
        x2 = c;
        x3 = d;
    }

    bool operator==(const ssylka &x)
    {
        if (x.Ntype == Ntype && x.x1 == x1 && x.x2 == x2 && x.x3 == x3)
            return true;
        else
            return false;
    }

    bool operator!=(const ssylka &x)
    {
        if (x.Ntype != Ntype || x.x1 != x1 || x.x2 != x2 || x.x3 != x3)
            return true;
        else
            return false;
    }
};

template <typename _Ty> 
struct Array
{
    int N;      //Count of elements
    _Ty *mas;   //Elements
    int free;   //Free elements

    Array()
    {
        N = 0;
        free = 0;
        mas = NULL;
    }

    Array(const _Ty data[], const int newN)
    {
        N = newN;
        free = 0;
        mas = new _Ty[newN];
        for (int i = 0; i < N; i++)
            mas[i] = data[i];
    }

    Array(const Array &It)
    {
        this->N = It.N;
        this->free = It.free;
        this->mas = new _Ty[It.N + It.free];
        for (int i = 0; i < It.N + It.free; i++)
            this->mas[i] = It.mas[i];
    }

    void operator=(const Array &It)
    {
        this->clear();
        this->N = It.N;
        this->free = It.free;
        if (It.N != 0)
            this->mas = new _Ty[It.N + It.free];
        for (int i = 0; i < It.N + It.free; i++)
            this->mas[i] = It.mas[i];
    }

    void clear()
    {
        if (mas != NULL)
            delete[] mas;
        mas = NULL;
        N = 0;
        free = 0;
    }

    void resize(int newN, bool ready)
    {
        if (newN == 0)
        {
            this->clear();
            return;
        }

        if (newN == N)
            return;

        _Ty *p = new _Ty[newN];
        int l = min(N + free, newN);
        if ((N + free) != 0)
        {
            for (int i = 0; i < l; i++)
                p[i] = mas[i];
            delete[] mas;
        }
        if (ready)
        {
            N = newN;
            free = 0;
        }
        else
        {
            N = l;
            free = (newN - l);
        }
        mas = p;
    }


    void push_back(const _Ty &x)
    {
        if (free)
        {
            free--;
            mas[N] = x;
            N++;
        }
        else
        {
            this->resize(2 * N + 1, false);
            free--;
            mas[N] = x;
            N++;
        }
    }

    bool operator==(const Array &It)
    {
        if (N != It.N)
            return false;
        for (int i = 0; i < N; i++)
            if (mas[i] != It.mas[i])
                return false;
        return true;
    }

    bool operator!=(const Array &It)
    {
        if (N != It.N)
            return true;
        for (int i = 0; i < N; i++)
            if (mas[i] != It.mas[i])
                return true;
        return false;
    }

    void pop_back()
    {
        if (N > 0)
        {
            resize(N - 1, true);
        }
    }
    ~Array()
    {
        if (mas != NULL)
            delete[] mas;
        mas = NULL;
        N = 0;
        free = 0;
    }
};

struct object
{
    int Name;
    Array < ssylka > Args;
    Array < ssylka > Conv;
    void operator=(const object &it)
    {
        Name = it.Name;
        Args = it.Args;
        Conv = it.Conv;
    }
};

struct spec_object
{
    int Name;
    Array < spec_object > Args;
    void operator=(const spec_object &it)
    {
        Name = it.Name;
        Args = it.Args;
    }
	bool operator==(const spec_object &it)
	{
		if (Name != it.Name)
			return false;
		if (Args != it.Args)
			return false;
		return true;
	}

	bool operator!=(const spec_object &it)
	{
		if (Name != it.Name)
			return true;
		if (Args != it.Args)
			return true;
		return false;
	}
};

struct conversion
{
    char type;                          //1 - termin        2 - any_...     3 - old......
    int Numb;                           //numb_name_termin  numb any        -
    //ssylka p;                           //-                 -               ssylka
    Array < conversion > args;          //arguments         -               -
    Array < int > bys;

    conversion()
    {
        type = 0;
        Numb = 0;
        //p = ssylka(0, 0, 0, 0);
        args.clear();
        bys.clear();
    }

    void clear()
    {
        type = 0;
        Numb = 0;
        //p = ssylka(0, 0, 0, 0);
        args.clear();
        bys.clear();
    }

    bool operator==(const conversion &it)
    {
        if (type != it.type)
            return false;
        if (Numb != it.Numb)
            return false;
        if (args != it.args)
            return false;
        if (bys != it.bys)
            return false;
        return true;
    }

    bool operator!=(const conversion &it)
    {
        if (type != it.type)
            return true;
        if (Numb != it.Numb)
            return true;
        if (args != it.args)
            return true;
        if (bys != it.bys)
            return true;
        return false;
    }

    ~conversion()
    {
        args.clear();
        bys.clear();
    }
};

struct bor_node
{
    bor_node* mas[256];
    int numb;

    bor_node()
    {
        numb = -1;
        for (int i = 0; i < 256; i++)
            mas[i] = NULL;
    }

    ~bor_node()
    {
        numb = -1;
        for (int i = 0; i < 256; i++)
            if (mas[i] != NULL)
                delete mas[i];
    }
};

struct BOR
{
    bor_node *mas[256];
    int N;

    BOR()
    {
        N = 0;
        for (int i = 0; i < 256; i++)
            mas[i] = NULL;
    }

    int Word(Array < char > &str)
    {
        bor_node *p;

        if (mas[str.mas[0]] == NULL)
            mas[str.mas[0]] = new bor_node(); 

        p = mas[str.mas[0]];

        int i = 1;
        while (i != str.N)
        {
            if (p->mas[str.mas[i]] == NULL)
                p->mas[str.mas[i]] = new bor_node();
            p = p->mas[str.mas[i]];
            i++;
        }
        if (p->numb == -1)
            p->numb = N++;
        return p->numb;
    }

    ~BOR()
    {
        for (int i = 0; i < 256; i++)
            if (mas[i] != NULL)
                delete mas[i];
    }
};

//for functions begin
inline void fReadStr(FILE* file, Array < char > &str)//I getting clear string
{
    char c;
    str.clear();
    fscanf(file, "%c", &c);
    while ((c == ' ' || c == '\n' || c == '\t') && !feof(file))
    {
        fscanf(file, "%c", &c);
    }
    while (c != ' ' && c != '\n' && c != '\t' && !feof(file))
    {
        str.push_back(c);
        fscanf(file, "%c", &c);
    }
    str.resize(str.N, true);
}
inline void fWriteStr(FILE *file, Array < char > &str)
{
    for (int i = 0; i < str.N; i++)
        fprintf(file, "%c", str.mas[i]);
}

inline bool CmpStr(Array < char > &str1, Array < char > &str2)
{
    if (str1.N != str2.N)
        return false;
    for (int i = 0; i < str1.N; i++)
        if (str1.mas[i] != str2.mas[i])
            return false;
    return true;
}

//for functions end
Array < char > exp_associated("associated", 10);
Array < char > exp_association("association", 11);
Array < char > exp_is("is", 2);
Array < char > exp_any("any", 3);
Array < char > exp_any_("any_", 4);
Array < char > exp_to("to", 2);
Array < char > exp_of("of", 2);
Array < char > exp_by("by", 2);
Array < char > exp_with("with", 4);
Array < char > exp_object("object", 6);
Array < char > exp_conversion("conversion", 10);
Array < char > exp_marck(",", 1);
Array < char > exp_pointmarck(";", 1);
Array < char > exp_point(".", 1);
Array < char > exp_as("as", 2);
Array < char > exp_END_FILE_KOVALSKY("END_FILE_KOVALSKY", 17);
Array < char > exp_Question("Question", 8);
Array < char > exp_comments("comments", 8);
Array < char > exp_end_comments("end_comments", 12);

const int BigNnn = 50000;
static spec_object blahblah[BigNnn];
static spec_object Queue[BigNnn];

struct Expert_v_3_0
{
    BOR nameston;                                       // imena
    BOR asston;                                         // svazi
    Array < Array < char > > ntonames;                  // str imena
    Array < Array < char > > ntoass;                    // str svazi
    Array < conversion > conversions;                   // mas conv
    Array < Array < ssylka > > anyass;                  // [ass][variat]
    Array < Array < ssylka > > anyconv;                 // [numb] N-args ssyl's-elements
    Array < Array < Array < object > > > objects;       // [name][args][variant]
    Array < Array < Array < ssylka > > > graf;          // [ass][name] N-count ssyl's-edges
    Array < bool > Mets;                                // [ass][name] bool met
    FILE *input, *output;
    Array < Array < Array < spec_object > > > spec_objects;
    //static spec_object blahblah[200];
    //static spec_object Queue[BigNnn];

    void Init(FILE* in, FILE* out)
    {
        input = in;
        output = out;
        fprintf(output, "comments\n//File created by expert Kovalsky version 3.0//\nend_comments\n\n\n");
    }

    bool test_association(int x1, int x2, int numbass)
    {
        int ItIt = 1;
        
        bool ans = false;
       
        Mets.resize(asston.N, true);
       
        int start = x1, finish = x2;
      
        int  size = asston.N;
       
        int size2 =nameston.N;
        

        Mets.resize(size2, true);
        
        for (int j = 0; j < size2; j++)
        {
           
            Mets.mas[j] = false;
           
        }
       

        int *queue = new int[size2];
      
        int begin = 0;
       
        int end = 0;
      
        queue[begin++] = start;
       
        int current;
       
        ssylka p;

        while (end != begin)
        {
           
            current = queue[end++];
           
            Mets.mas[current] = true;
           
            if (current == finish)
            {
                
                ans = true;
               
                goto the_end;
            }
            
            size = graf.mas[numbass].mas[current].N;
            for (int i = 0; i < size; i++)
            {
                p = graf.mas[numbass].mas[current].mas[i];
                if (p.Ntype == 0)
                {
                    if (!Mets.mas[p.x1])
                        queue[begin++] = p.x1;
                }
                else if (p.Ntype == 3)
                {
                    if (!Mets.mas[p.x1])
                        queue[begin++] = p.x1;
                }
               
            }
            

        }
       
the_end:
        delete[] queue;
        return ans;
    }
    bool Spec_test_association(int x1, Array < int > &finishis, int numbass)
    {
        bool ans = false;
        Mets.resize(asston.N, true);
        int start = x1;
        int  size = asston.N;
        int size2 =nameston.N;

        Mets.resize(size2, true);
        for (int j = 0; j < size2; j++)
            Mets.mas[j] = false;

        int *queue = new int[size2];
        int begin = 0;
        int end = 0;
        queue[begin++] = start;
        int current;
        ssylka p;
        while (end != begin)
        {
            current = queue[end++];
            Mets.mas[current] = true;
            for (int i = 0; i < finishis.N; i++)
                if (current == finishis.mas[i] && current != start)
                {
                    ans = true;
                    goto the_end;
                }
            size = graf.mas[numbass].mas[current].N;
            for (int i = 0; i < size; i++)
            {
                p = graf.mas[numbass].mas[current].mas[i];
                if (p.Ntype == 0)
                {
                    if (!Mets.mas[p.x1])
                        queue[begin++] = p.x1;
                }
                else if (p.Ntype == 3)
                {
                    if (!Mets.mas[p.x1])
                        queue[begin++] = p.x1;
                }
            }

        }
the_end:
        delete[] queue;
        return ans;
    }
	void AddSpecObject(spec_object &x)
	{
		spec_objects.mas[x.Name].resize(max(spec_objects.mas[x.Name].N, x.Args.N + 1), true);
		spec_objects.mas[x.Name].mas[x.Args.N].push_back(x);
	}

	bool HaveSpecObject(spec_object &x)
	{
		if (spec_objects.mas[x.Name].N <= x.Args.N)
			return false;
		int size = spec_objects.mas[x.Name].mas[x.Args.N].N;
		for (int i = 0; i < size; i++)
			if (x == spec_objects.mas[x.Name].mas[x.Args.N].mas[i])
				return true;
		return false;
	}

	bool Testing(spec_object &x, int type)
	{
		int x1, x2, x3;
		x1 = x.Name;
		x2 = x.Args.N;
		if ((x2 == 0) && (type == 1))
			return true;
		x3 = objects.mas[x1].mas[x2].N;
		for (int i = 0; i < x3; i++)
			if (objects.mas[x1].mas[x2].mas[i].Conv.N > 0)
				if (type == 1)
					return  false;
				else
					return true;

		x3 = x.Args.N;
		for (int i = 0; i < x3; i++)
			if (Testing(x.Args.mas[i], 2))
				if (type == 1)
					return false;
				else
					return true;

		if (type == 1)
			return true;
		else
			return false;
	}

    bool Contakt(spec_object &x, ssylka T)
    {
        if (T.Ntype == 1)
        {

            int numbass = T.x1;

            T = anyass.mas[T.x1].mas[T.x2];

            if (!test_association(x.Name, T.x1, numbass))
                return false;
            else
                return true;
        }
        else
        {

            if (x.Name != objects.mas[T.x1].mas[T.x2].mas[T.x3].Name ||
                x.Args.N != objects.mas[T.x1].mas[T.x2].mas[T.x3].Args.N)
            {

                return false;
            }

            object *p = &objects.mas[T.x1].mas[T.x2].mas[T.x3];

            int size = x.Args.N;

            for (int i = 0; i < size; i++)
            {

                if (!Contakt(x.Args.mas[i], p->Args.mas[i]))
                {

                    return false;

                }

            }

            return true;
        }
    }
    void GetNewObject(spec_object &original, spec_object &p, conversion &conve)
    {

        if (conve.type == 1)
        {

            p.Args.clear();

            p.Name = conve.Numb;

            p.Args.resize(conve.args.N, true);

            int size = conve.args.N;

            for (int i = 0; i < size; i++)
            {

                GetNewObject(original, p.Args.mas[i], conve.args.mas[i]);

            }

            return;
        }
        else
        {

            spec_object *TtT;

		    TtT = &original.Args.mas[conve.Numb - 1];

            int N = conve.bys.N;

            for (int i = 0; i < N; i++)
            {

                TtT = &(TtT->Args.mas[conve.bys.mas[i] - 1]);

            }

            p = (*TtT);

            return;
        }
    }

	void Transform (spec_object &x, Array < int > &path, int &begin)
	{
		int k = path.N;

		spec_object *p = &x;

		for (int i = 0; i < k; i++)
			p = &(p->Args.mas[path.mas[i]]);



		spec_object copy_p, copy;

		copy_p = (*p);

		copy = x;


		int x1 = p->Name;

		int x2 = p->Args.N;

		int x3;

		int size;

		if (objects.mas[x1].N <= x2)
			goto end_transform;

		x3 = objects.mas[x1].mas[x2].N;

        size = 0;

		for (int i = 0; i < x3; i++)
		{
            if (Contakt(copy_p, ssylka(3, x1, x2, i)))
            {
                size = objects.mas[x1].mas[x2].mas[i].Conv.N;
                for (int j = 0; j < size; j++)
                {
                    GetNewObject(copy_p, *p, conversions.mas[objects.mas[x1].mas[x2].mas[i].Conv.mas[j].x1]);
                    if (!HaveSpecObject(x))
                    {
                        AddSpecObject(x);
                        Queue[begin] = x;
                        begin = (begin + 1) % BigNnn;
                    }
                }
            }
            
		}

end_transform:
		x = copy;
		size = copy_p.Args.N;
        for (int i = 0; i < size; i++)
        {
            path.push_back(i);
            Transform(x, path, begin);
        }
		path.pop_back();
        return;
	}
    void fPrintObject(spec_object &x)
    {
        fWriteStr(output, ntonames.mas[x.Name]);
        fprintf(output, " ");
        int size = x.Args.N;
        if (size > 0)
        {
            fprintf(output, "of ");
            for (int i = 0; i < size; i++)
            {
                fPrintObject(x.Args.mas[i]);
                fprintf(output, " ");
                if (i != size - 1)
                    fprintf(output, ", ");
            }
        }
        fprintf(output, ".");
    }
    void Question(object *x, int no, Array < char > &stringi, ssylka *p, int ns)
    {
        int eta;
        graf.resize(asston.N, true);
        for (int i = 0; i < asston.N; i++)
            graf.mas[i].resize(nameston.N, true);
        fscanf(input, "%d", &eta);
        fReadStr(input, stringi);
        if (CmpStr(exp_association, stringi))
        {
            fReadStr(input, stringi);
            GetObject(x, no++, stringi, p, ns);//---------------
            fReadStr(input, stringi);
            fReadStr(input, stringi);
            fReadStr(input, stringi);
            int numbass = asston.Word(stringi);
            fReadStr(input, stringi);
            fReadStr(input, stringi);
            GetObject(x, no++, stringi, p, ns);//---------------
            if (test_association(x[no - 2].Name, x[no - 1].Name, numbass))
                fprintf(output, "YES\n");
            else
                fprintf(output, "NO\n");
            return;
        }
        if (CmpStr(exp_object, stringi))
        {
            Array < int > anys;
            Array < int > nmcurrent;//current names
            Array < int > nmnew;//new names
            anys.clear();
            nmcurrent.clear();
            nmnew.clear();
            fReadStr(input, stringi);
            while (CmpStr(exp_any, stringi))
            {
                fReadStr(input, stringi);//associ
                fReadStr(input, stringi);//as
                fReadStr(input, stringi);//name
                anys.push_back(asston.Word(stringi));
                fReadStr(input, stringi);//with
                fReadStr(input, stringi);//....
            }
            GetObject(x, no, stringi, p, ns);//---------------
            int K = anys.N - 1;
            int size = nameston.N;
            nmcurrent.push_back(x[no].Name);
            while (K > -1)
            {
                for (int i = 0; i < size; i++)
                {
                    if (Spec_test_association(i, nmcurrent, anys.mas[K]))
                    {
                        nmnew.push_back(i);
                    }
                }
                nmcurrent = nmnew;
                nmnew.clear();
                K--;
            }
            size = min(eta, nmcurrent.N);
            for (int i = 0; i < size; i++)
            {
                fWriteStr(output, ntonames.mas[nmcurrent.mas[i]]);
                fprintf(output, " . ;\n");
            }
            return;
        }
        if (CmpStr(exp_conversion, stringi))
        {
            fReadStr(input, stringi);
			fReadStr(input, stringi);
			int type;//1 = object 2 = conv

			if (CmpStr(exp_object, stringi))
				type = 1;
			else
				type = 2;

            Array < int > path;
            //Queue
            //X
            Array < spec_object > ans;

			path.clear();
			ans.clear();

            int begin = 0;
            int end = 0;
            fReadStr(input, stringi);
            SpecGetObject(&blahblah[0], 0, stringi);
            Queue[begin] = blahblah[0];
            begin = (begin + 1) % BigNnn;
			/*init*/
            spec_objects.clear();
			spec_objects.resize(nameston.N, true);
			/*end init*/
            AddSpecObject(blahblah[0]);
            while (end != begin && ans.N < eta)
            {
                blahblah[0] = Queue[end];
				printf("end: %d .. begin: %d .. answers: %d\n", end, begin, ans.N);
                end = (end + 1) % BigNnn;
                if (Testing(blahblah[0], type))
				{
					ans.push_back(blahblah[0]);
					if (type == 1)
						goto the_end;
				}
				else
				{
					if (type != 1)
						goto the_end;
				}
				Transform(blahblah[0], path, begin);

the_end:
				int d = 0;
            }
            ///*?*/oihoijoij
            int CNN = min(ans.N, eta);
            for (int i = 0; i < CNN; i++)
            {
                fPrintObject(ans.mas[i]);//no writing
                fprintf(output, " ;\n");
            }
            return;
        }

    }

    ssylka GetSsylkaOnObject(object &x)
    {
        char type = 3;
        int x1 = x.Name;
        int x2 = x.Args.N;
        int x3 = -1;
        int size = objects.mas[x1].mas[x2].N;
        int sizen = x.Args.N;

        for (int i = 0; i < size; i++)
        {
            int size2 = objects.mas[x1].mas[x2].mas[i].Args.N;
            if (size2 != sizen)
                continue;
            for (int j = 0; j < size2; j++)
            {
                if (x.Args.mas[j] != objects.mas[x1].mas[x2].mas[i].Args.mas[j])
                    goto Again;
            }
            x3 = i;
            break;
Again:
            int d = 0;
        }
        if (x3 == -1)
            return ssylka (5); //return  bad ssylka
        return ssylka (type, x1, x2, x3);
    }

    void GetSsylka(object *x, int no, Array < char > &name, ssylka *p, int ns)
    {
        fReadStr(input, name);
        if (CmpStr(exp_association, name))
        {
            p[ns].Ntype = 1;
            fReadStr(input, name);
            fReadStr(input, name);
            int k = asston.N;
            p[ns].x1 = asston.Word(name);
            if (asston.N > k)
            {
                ntoass.push_back(name);
                k = -1;
            }
            fReadStr(input, name);
            fReadStr(input, name);
            if (CmpStr(exp_any, name))
            {
                GetSsylka(x, no, name, p, ns + 1);
                anyass.resize(max(p[ns].x1 + 1, anyass.N), true);
                int size = anyass.mas[p[ns].x1].N;
                for (int i = 0; i < size; i++)
                    if (p[ns + 1] == anyass.mas[p[ns].x1].mas[i])
                    {
                        p[ns].x2 = i;
                        return;
                    }
                anyass.mas[p[ns].x1].push_back(p[ns + 1]);
                p[ns].x2 = size;
                return;
            }
            else
            {
                GetObject(x, no, name, p, ns + 1);
                p[ns + 1] = GetSsylkaOnObject(x[no]);
                anyass.resize(max(p[ns].x1 + 1, anyass.N), true);
                int size = anyass.mas[p[ns].x1].N;
                for (int i = 0; i < size; i++)
                    if (p[ns + 1] == anyass.mas[p[ns].x1].mas[i])
                    {
                        p[ns].x2 = i;
                        return;
                    }
                anyass.mas[p[ns].x1].push_back(p[ns + 1]);
                p[ns].x2 = size;
                return;
            }

        }
        else // any conversion
        {
            p[ns].Ntype = 2;
            Array < ssylka > q;
            q.clear();

            fReadStr(input, name);
            if (CmpStr(exp_of, name))
            {
                fReadStr(input, name);
                while (!CmpStr(exp_point, name))
                {
                    if (CmpStr(exp_marck, name))
                        goto Read;
                    if (CmpStr(exp_any, name))
                    {
                        GetSsylka(x, no + 1, name, p, ns);
                        q.push_back(p[ns]);
                        goto Read;
                    }
                    GetObject(x, no + 1, name, p, ns);
                    q.push_back(GetSsylkaOnObject(x[no + 1]));
Read:
                    fReadStr(input, name);
                }
            }

            int size = anyconv.N;
            for (int i = 0; i < size; i++)
                if (q == anyconv.mas[i])
                {
                    p[ns].x1 = i;
                    return;
                }
            anyconv.push_back(q);
            p[ns].x1 = size;
            return;
        }
    }
    void GetObject(object *x, int no, Array < char > &name, ssylka *p, int ns)
    {
        x[no].Args.clear();
        x[no].Conv.clear();
        x[no].Name = 0;
        int k = nameston.N;
        x[no].Name = nameston.Word(name);
        if (nameston.N > k)
        {
            ntonames.push_back(name);
            k = -1;
        }
        fReadStr(input, name);
        if (CmpStr(exp_of, name))
        {
            fReadStr(input, name);
            while (!CmpStr(exp_point, name))
            {
                if (CmpStr(exp_marck, name))
                    goto Read;
                if (CmpStr(exp_any, name))
                {
                    GetSsylka(x, no + 1, name, p, ns);
                    x[no].Args.push_back(p[ns]);
                    goto Read;
                }
                GetObject(x, no + 1, name, p, ns);
                x[no].Args.push_back(GetSsylkaOnObject(x[no + 1]));
Read:
                fReadStr(input, name);
            }
        }
        if (k == -1)
        {
            objects.resize(nameston.N, true);
        }
        objects.mas[x[no].Name].resize(max(objects.mas[x[no].Name].N, x[no].Args.N + 1), true);
        int size = objects.mas[x[no].Name].mas[x[no].Args.N].N;
        for (int i = 0; i < size; i++)
            if (x[no].Args == objects.mas[x[no].Name].mas[x[no].Args.N].mas[i].Args)
                return;
        objects.mas[x[no].Name].mas[x[no].Args.N].push_back(x[no]);
        return;
    }

    void SpecGetObject(spec_object *x, int no, Array < char > &name)
    {
        x[no].Args.clear();
        x[no].Name = 0;
        int k = nameston.N;
        x[no].Name = nameston.Word(name);
        fReadStr(input, name);
        if (CmpStr(exp_of, name))
        {
            fReadStr(input, name);
            while (!CmpStr(exp_point, name))
            {
                if (CmpStr(exp_marck, name))
                    goto Read;
                SpecGetObject(x, no + 1, name);
                x[no].Args.push_back(x[no + 1]);
Read:
                fReadStr(input, name);
            }
        }
        return;
    }

    void AddAssociation (object *x, int no, Array < char > &stringi, ssylka *p, int ns)
    {
        fReadStr(input, stringi);
        Array < char > nameass;
        fReadStr(input, nameass);
        int k = asston.N;
        int numbass = asston.Word(nameass);
        if (asston.N > k)
        {
            ntoass.push_back(nameass);
            k = -1;
        }
        fReadStr(input, stringi);//read with
        fReadStr(input, stringi);//any or term
        if (CmpStr(exp_any, stringi))
        {
            GetSsylka(x, no, stringi, p, ns);
            int minisize = max(graf.N, asston.N);
            graf.resize(minisize, true);
            for (int i = 0; i < minisize; i++)
                graf.mas[i].resize(max(graf.mas[i].N, nameston.N), true);
            int size = graf.mas[numbass].mas[x[no - 1].Name].N;
            for (int i = 0; i < size; i++)
                if ( graf.mas[numbass].mas[x[no - 1].Name].mas[i] == p[ns])
                    return;
            graf.mas[numbass].mas[x[no - 1].Name].push_back(p[ns]);
            return;
        }
        //only term
        GetObject(x, no, stringi, p, ns);
        p[ns] = GetSsylkaOnObject(x[no]);

        int minisize = max(graf.N, asston.N);
        graf.resize(minisize, true);
        for (int i = 0; i < minisize; i++)
            graf.mas[i].resize(max(graf.mas[i].N, nameston.N), true);

        int size = graf.mas[numbass].mas[x[no - 1].Name].N;
        for (int i = 0; i < size; i++)
            if ( graf.mas[numbass].mas[x[no - 1].Name].mas[i] == p[ns])
                return;
        graf.mas[numbass].mas[x[no - 1].Name].push_back(p[ns]);
        return;
        

    }

    void GetConversion(Array < char > &stringi, conversion &tmp)
    {
        conversion currenttmp;
        //fReadStr(input, stringi);
        if (CmpStr(exp_any_, stringi))
        {
            tmp.type = 2;
            fscanf(input, "%d", &tmp.Numb);
            fReadStr(input, stringi);
            int n;
            while (! CmpStr(exp_point, stringi))
            {
                fscanf(input, "%d", &n);
                tmp.bys.push_back(n);
                fReadStr(input, stringi);
            }
        }
        else
        {
            tmp.type = 1;
            int k = nameston.N;
            tmp.Numb = nameston.Word(stringi);
            if (nameston.N > k)
            {
                ntonames.push_back(stringi);
                k = -1;
            }
            fReadStr(input, stringi);
            if (CmpStr(exp_of, stringi))
            {
                fReadStr(input, stringi);
                while (!CmpStr(exp_point, stringi))
                {
                    if (CmpStr(exp_marck, stringi))
                        goto Read;
                    if (CmpStr(exp_any_, stringi))
                    {
                        currenttmp.clear();
                        GetConversion(stringi, currenttmp);
                        tmp.args.push_back(currenttmp);
                        goto Read;
                    }
                    currenttmp.clear();
                    GetConversion(stringi, currenttmp);
                    tmp.args.push_back(currenttmp);
    Read:
                    fReadStr(input, stringi);
                }
            }

        }
        return;
    }

    void MainLoop()
    {
        object tmpo[200];
        int on, sn;
        ssylka tmps[200];
        conversion tmpc;
        Array < char > stringi;
LoopIng:
        on = 0;
        sn = 0;
        fReadStr(input, stringi);
        if (CmpStr(stringi, exp_END_FILE_KOVALSKY))
        {
            fWriteStr(output, exp_END_FILE_KOVALSKY);
            fprintf(output, "\n");
            return;
        }
        if (CmpStr(stringi, exp_comments))
        {
            fReadStr(input, stringi);
            while(!CmpStr(stringi, exp_end_comments))
                fReadStr(input, stringi);
            goto LoopIng;
        }
        if (CmpStr(stringi, exp_Question))
        {
            Question(&tmpo[0], on, stringi, &tmps[0], sn);
            goto LoopIng;
        }
        if (CmpStr(stringi, exp_pointmarck))
            goto LoopIng;
        GetObject(&tmpo[0], on++, stringi, &tmps[0], sn);

        //heven 1 object
        //inputting command

        fReadStr(input, stringi);

        if (CmpStr(exp_associated, stringi))
        {
            AddAssociation(&tmpo[0], on, stringi, &tmps[0], sn);
            goto LoopIng;
        }
        if (CmpStr(exp_pointmarck, stringi))
            goto LoopIng;
        if (CmpStr(exp_is, stringi))
        {
            fReadStr(input, stringi);
            if (CmpStr(exp_object, stringi))
                goto LoopIng;

            fReadStr(input, stringi);   //read to
            fReadStr(input, stringi);   //read name conversion
            tmpc.clear();               //clear tmp conversion

            GetConversion(stringi, tmpc);
            int size = conversions.N;
            int nummb = -1;
            for (int i = 0; i < size; i++)
                if (conversions.mas[i] == tmpc)
                {
                    nummb = i;
                    goto have_conv;
                }
            nummb = size;
            conversions.push_back(tmpc);
have_conv:
            tmps[sn] = GetSsylkaOnObject(tmpo[0]);
            objects.mas[tmps[sn].x1].mas[tmps[sn].x2].mas[tmps[sn].x3].Conv.push_back(ssylka(4, nummb));
        }

        goto LoopIng;

    }

    ~Expert_v_3_0()
    {
        input = NULL;
        output = NULL;
    }

};


#endif
