#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  pointerp; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ xdrfunc ;
struct TYPE_6__ {int /*<<< orphan*/  val; struct TYPE_6__* next; } ;
typedef  TYPE_2__ list ;
typedef  int /*<<< orphan*/  definition ;

/* Variables and functions */
 scalar_t__ CCflag ; 
 int /*<<< orphan*/  add_warning () ; 
 TYPE_2__* defined ; 
 char const* extendfile (char const*,char const*) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (void*) ; 
 long ftell (int /*<<< orphan*/ ) ; 
 void* generate_guard (char const*) ; 
 int /*<<< orphan*/ * get_definition () ; 
 scalar_t__ mtflag ; 
 int /*<<< orphan*/  open_input (char const*,char const*) ; 
 int /*<<< orphan*/  open_output (char const*,char const*) ; 
 int /*<<< orphan*/  print_datadef (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_funcdef (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_xdr_func_def (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcgen_table_dcl ; 
 scalar_t__ tblflag ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 TYPE_1__* xdrfunc_head ; 

__attribute__((used)) static void
h_output(const char *infile, const char *define, int extend, const char *outfile, int headeronly)
{
	definition *def;
	const char *outfilename;
	long tell;
	const char *guard;
	list *l;
	xdrfunc *xdrfuncp;
	void *tmp = NULL;

	open_input(infile, define);
	outfilename =  extend ? extendfile(infile, outfile) : outfile;
	open_output(infile, outfilename);
	add_warning();
	if (outfilename || infile){
		guard = tmp = generate_guard(outfilename ? outfilename: infile);
	} else
		guard = "STDIN_";

	f_print(fout, "#ifndef _%s\n#define	_%s\n\n", guard,
		guard);

	f_print(fout, "#include <rpc/rpc.h>\n");

	if (mtflag)
		f_print(fout, "#include <pthread.h>\n");

	/* put the C++ support */
	if (!CCflag) {
		f_print(fout, "\n#ifdef __cplusplus\n");
		f_print(fout, "extern \"C\" {\n");
		f_print(fout, "#endif\n\n");
	}

	/* put in a typedef for quadprecision. Only with Cflag */

	tell = ftell(fout);

	/* print data definitions */
	while ( (def = get_definition()) ) {
		print_datadef(def, headeronly);
	}

	/*
	 * print function declarations.
	 *  Do this after data definitions because they might be used as
	 *  arguments for functions
	 */
	for (l = defined; l != NULL; l = l->next) {
		print_funcdef(l->val, headeronly);
	}
	/* Now  print all xdr func declarations */
	if (xdrfunc_head != NULL){

		f_print(fout,
			"\n/* the xdr functions */\n");

		if (CCflag){
			f_print(fout, "\n#ifdef __cplusplus\n");
			f_print(fout, "extern \"C\" {\n");
			f_print(fout, "#endif\n");
		}

		xdrfuncp = xdrfunc_head;
		while (xdrfuncp != NULL){
			print_xdr_func_def(xdrfuncp->name, xdrfuncp->pointerp);
			xdrfuncp = xdrfuncp->next;
		}
	}

	if (extend && tell == ftell(fout)) {
		(void) unlink(outfilename);
	} else if (tblflag) {
		f_print(fout, rpcgen_table_dcl);
	}

	f_print(fout, "\n#ifdef __cplusplus\n");
	f_print(fout, "}\n");
	f_print(fout, "#endif\n");

	f_print(fout, "\n#endif /* !_%s */\n", guard);
	free(tmp);
}