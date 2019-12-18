#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type_handler {char* getarg_type; int /*<<< orphan*/  (* free ) (char*) ;int /*<<< orphan*/  (* defval ) (char*,struct assignment*) ;} ;
struct TYPE_2__ {char* value; struct assignment* assignment; } ;
struct assignment {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfile ; 
 int /*<<< orphan*/  cprint (int,char*,...) ; 
 int /*<<< orphan*/  ex (struct assignment*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct assignment* find (struct assignment*,char*) ; 
 struct type_handler* find_handler (struct assignment*) ; 
 struct assignment* find_next (struct assignment*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gen_name (char*) ; 
 int /*<<< orphan*/  gen_options (struct assignment*,char*) ; 
 int /*<<< orphan*/  hprint (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* make_name (struct assignment*) ; 
 char* strdup (char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char*,struct assignment*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 
 int /*<<< orphan*/  stub3 (char*) ; 

__attribute__((used)) static void
gen_wrapper(struct assignment *as)
{
    struct assignment *name;
    struct assignment *arg;
    struct assignment *opt1;
    struct assignment *function;
    struct assignment *tmp;
    char *n, *f;
    int nargs = 0;
    int narguments = 0;

    name = find(as, "name");
    n = strdup(name->u.value);
    gen_name(n);
    arg = find(as, "argument");
    if (arg)
        narguments++;
    opt1 = find(as, "option");
    function = find(as, "function");
    if(function)
	f = function->u.value;
    else
	f = n;


    if(opt1 != NULL) {
	gen_options(opt1, n);
	hprint(0, "int %s(struct %s_options*, int, char **);\n", f, n);
    } else {
	hprint(0, "int %s(void*, int, char **);\n", f);
    }

    fprintf(cfile, "static int\n");
    fprintf(cfile, "%s_wrap(int argc, char **argv)\n", n);
    fprintf(cfile, "{\n");
    if(opt1 != NULL)
	cprint(1, "struct %s_options opt;\n", n);
    cprint(1, "int ret;\n");
    cprint(1, "int optidx = 0;\n");
    cprint(1, "struct getargs args[] = {\n");
    for(tmp = find(as, "option");
	tmp != NULL;
	tmp = find_next(tmp, "option")) {
	struct assignment *type = find(tmp->u.assignment, "type");
	struct assignment *lopt = find(tmp->u.assignment, "long");
	struct assignment *sopt = find(tmp->u.assignment, "short");
	struct assignment *aarg = find(tmp->u.assignment, "argument");
	struct assignment *help = find(tmp->u.assignment, "help");

	struct type_handler *th;

	cprint(2, "{ ");
	if(lopt)
	    fprintf(cfile, "\"%s\", ", lopt->u.value);
	else
	    fprintf(cfile, "NULL, ");
	if(sopt)
	    fprintf(cfile, "'%c', ", *sopt->u.value);
	else
	    fprintf(cfile, "0, ");
	th = find_handler(type);
	fprintf(cfile, "%s, ", th->getarg_type);
	fprintf(cfile, "NULL, ");
	if(help)
	    fprintf(cfile, "\"%s\", ", help->u.value);
	else
	    fprintf(cfile, "NULL, ");
	if(aarg) {
	    fprintf(cfile, "\"%s\"", aarg->u.value);
            narguments++;
	} else
	    fprintf(cfile, "NULL");
	fprintf(cfile, " },\n");
    }
    cprint(2, "{ \"help\", 'h', arg_flag, NULL, NULL, NULL }\n");
    cprint(1, "};\n");
    cprint(1, "int help_flag = 0;\n");

    for(tmp = find(as, "option");
	tmp != NULL;
	tmp = find_next(tmp, "option")) {
	char *s;
	struct assignment *type = find(tmp->u.assignment, "type");

	struct assignment *defval = find(tmp->u.assignment, "default");

	struct type_handler *th;

	s = make_name(tmp->u.assignment);
	th = find_handler(type);
	(*th->defval)(s, defval);
	free(s);
    }

    for(tmp = find(as, "option");
	tmp != NULL;
	tmp = find_next(tmp, "option")) {
	char *s;
	s = make_name(tmp->u.assignment);
	cprint(1, "args[%d].value = &opt.%s;\n", nargs++, s);
	free(s);
    }
    cprint(1, "args[%d].value = &help_flag;\n", nargs++);
    cprint(1, "if(getarg(args, %d, argc, argv, &optidx))\n", nargs);
    cprint(2, "goto usage;\n");

    {
	int min_args = -1;
	int max_args = -1;
	char *end;
	if(narguments == 0) {
	    max_args = 0;
	} else {
	    if((tmp = find(as, "min_args")) != NULL) {
		min_args = strtol(tmp->u.value, &end, 0);
		if(*end != '\0') {
		    ex(tmp, "min_args is not numeric");
		    exit(1);
		}
		if(min_args < 0) {
		    ex(tmp, "min_args must be non-negative");
		    exit(1);
		}
	    }
	    if((tmp = find(as, "max_args")) != NULL) {
		max_args = strtol(tmp->u.value, &end, 0);
		if(*end != '\0') {
		    ex(tmp, "max_args is not numeric");
		    exit(1);
		}
		if(max_args < 0) {
		    ex(tmp, "max_args must be non-negative");
		    exit(1);
		}
	    }
	}
	if(min_args != -1 || max_args != -1) {
	    if(min_args == max_args) {
		cprint(1, "if(argc - optidx != %d) {\n",
		       min_args);
		cprint(2, "fprintf(stderr, \"Need exactly %u parameters (%%u given).\\n\\n\", argc - optidx);\n", min_args);
		cprint(2, "goto usage;\n");
		cprint(1, "}\n");
	    } else {
		if(max_args != -1) {
		    cprint(1, "if(argc - optidx > %d) {\n", max_args);
		    cprint(2, "fprintf(stderr, \"Arguments given (%%u) are more than expected (%u).\\n\\n\", argc - optidx);\n", max_args);
		    cprint(2, "goto usage;\n");
		    cprint(1, "}\n");
		}
		if(min_args != -1) {
		    cprint(1, "if(argc - optidx < %d) {\n", min_args);
		    cprint(2, "fprintf(stderr, \"Arguments given (%%u) are less than expected (%u).\\n\\n\", argc - optidx);\n", min_args);
		    cprint(2, "goto usage;\n");
		    cprint(1, "}\n");
		}
	    }
	}
    }

    cprint(1, "if(help_flag)\n");
    cprint(2, "goto usage;\n");

    cprint(1, "ret = %s(%s, argc - optidx, argv + optidx);\n",
	   f, opt1 ? "&opt": "NULL");

    /* free allocated data */
    for(tmp = find(as, "option");
	tmp != NULL;
	tmp = find_next(tmp, "option")) {
	char *s;
	struct assignment *type = find(tmp->u.assignment, "type");
	struct type_handler *th;
	th = find_handler(type);
	if(th->free == NULL)
	    continue;
	s = make_name(tmp->u.assignment);
	(*th->free)(s);
	free(s);
    }
    cprint(1, "return ret;\n");

    cprint(0, "usage:\n");
    cprint(1, "arg_printusage (args, %d, \"%s\", \"%s\");\n", nargs,
	   name->u.value, arg ? arg->u.value : "");
    /* free allocated data */
    for(tmp = find(as, "option");
	tmp != NULL;
	tmp = find_next(tmp, "option")) {
	char *s;
	struct assignment *type = find(tmp->u.assignment, "type");
	struct type_handler *th;
	th = find_handler(type);
	if(th->free == NULL)
	    continue;
	s = make_name(tmp->u.assignment);
	(*th->free)(s);
	free(s);
    }
    cprint(1, "return 0;\n");
    cprint(0, "}\n");
    cprint(0, "\n");
}