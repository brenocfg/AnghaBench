#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* argname; TYPE_4__* decls; } ;
struct TYPE_8__ {int arg_num; char* proc_name; int /*<<< orphan*/  res_type; TYPE_2__ args; int /*<<< orphan*/  res_prefix; } ;
typedef  TYPE_3__ proc_list ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_1__ decl; struct TYPE_9__* next; } ;
typedef  TYPE_4__ decl_list ;
typedef  int bool_t ;

/* Variables and functions */
 char* RESULT ; 
 char* ampr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 scalar_t__ newstyle ; 
 int /*<<< orphan*/  ptype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stringfix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
printbody(proc_list *proc)
{
	decl_list *l;
	bool_t args2 = (proc->arg_num > 1);

	/*
	 * For new style with multiple arguments, need a structure in which
	 *  to stuff the arguments.
	 */
	

	if (newstyle && args2) {
		f_print(fout, "\t%s", proc->args.argname);
		f_print(fout, " arg;\n");
	}
	if (!mtflag) {
		f_print(fout, "\tstatic ");
		if (streq(proc->res_type, "void")) {
			f_print(fout, "char ");
		} else {
			ptype(proc->res_prefix, proc->res_type, 0);
		}
		f_print(fout, "%s;\n", RESULT);
		f_print(fout, "\n");
		f_print(fout, "\tmemset((char *)%s%s, 0, sizeof (%s));\n",
			ampr(proc->res_type), RESULT, RESULT);

	}
	if (newstyle && !args2 &&
	    (streq(proc->args.decls->decl.type, "void"))) {
		/* newstyle, 0 arguments */

		if (mtflag)
			f_print(fout, "\t return ");
		else
			f_print(fout, "\t if ");

		f_print(fout,
			"(clnt_call(clnt, %s,\n\t\t(xdrproc_t) xdr_void, ",
			proc->proc_name);
		f_print(fout,
			"(caddr_t) NULL,\n\t\t(xdrproc_t) xdr_%s, (caddr_t) %s%s,",
			stringfix(proc->res_type), (mtflag)?"":ampr(proc->res_type),
			RESULT);

		if (mtflag)
			f_print(fout, "\n\t\tTIMEOUT));\n");
		else
			f_print(fout, "\n\t\tTIMEOUT) != RPC_SUCCESS) {\n");

	} else if (newstyle && args2) {
		/*
		 * Newstyle, multiple arguments
		 * stuff arguments into structure
		 */
		for (l = proc->args.decls;  l != NULL; l = l->next) {
			f_print(fout, "\targ.%s = %s;\n",
				l->decl.name, l->decl.name);
		}
		if (mtflag)
			f_print(fout, "\treturn ");
		else
			f_print(fout, "\tif ");			
		f_print(fout,
			"(clnt_call(clnt, %s,\n\t\t(xdrproc_t) xdr_%s",
			proc->proc_name,proc->args.argname);
		f_print(fout,
			", (caddr_t) &arg,\n\t\t(xdrproc_t) xdr_%s, (caddr_t) %s%s,",
			stringfix(proc->res_type), (mtflag)?"":ampr(proc->res_type),
			RESULT);
		if (mtflag)
			f_print(fout, "\n\t\tTIMEOUT));\n");
		else
			f_print(fout, "\n\t\tTIMEOUT) != RPC_SUCCESS) {\n");
	} else {		/* single argument, new or old style */
		if (!mtflag)
			f_print(fout,
			"\tif (clnt_call(clnt, %s,\n\t\t(xdrproc_t) xdr_%s, (caddr_t) %s%s,\n\t\t(xdrproc_t) xdr_%s, (caddr_t) %s%s,\n\t\tTIMEOUT) != RPC_SUCCESS) {\n",
			proc->proc_name,
			stringfix(proc->args.decls->decl.type),
			(newstyle ? "&" : ""),
			(newstyle ? proc->args.decls->decl.name : "argp"),
			stringfix(proc->res_type), ampr(proc->res_type),
			RESULT);
		else
			
		f_print(fout,
			"\treturn (clnt_call(clnt, %s,\n\t\t(xdrproc_t) xdr_%s, (caddr_t) %s%s,\n\t\t(xdrproc_t) xdr_%s, (caddr_t) %s%s,\n\t\tTIMEOUT));\n",
			proc->proc_name,
			stringfix(proc->args.decls->decl.type),
			(newstyle ? "&" : ""),
			(newstyle ? proc->args.decls->decl.name : "argp"),
			stringfix(proc->res_type), "",
			RESULT);
	}
	if (!mtflag) {
		f_print(fout, "\t\treturn (NULL);\n");
		f_print(fout, "\t}\n");

		if (streq(proc->res_type, "void")) {
			f_print(fout, "\treturn ((void *)%s%s);\n",
				ampr(proc->res_type), RESULT);
		} else {
			f_print(fout, "\treturn (%s%s);\n",
				ampr(proc->res_type), RESULT);
		}
	}
}