#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  vers_num; TYPE_4__* procs; int /*<<< orphan*/  vers_name; } ;
typedef  TYPE_3__ version_list ;
struct TYPE_7__ {TYPE_5__* decls; } ;
struct TYPE_10__ {int arg_num; char const* proc_name; int /*<<< orphan*/  res_type; int /*<<< orphan*/  res_prefix; TYPE_1__ args; struct TYPE_10__* next; } ;
typedef  TYPE_4__ proc_list ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; } ;
struct TYPE_11__ {TYPE_2__ decl; struct TYPE_11__* next; } ;
typedef  TYPE_5__ decl_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 int /*<<< orphan*/  newstyle ; 
 int /*<<< orphan*/  ptype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvname (char const*,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tirpcflag ; 

__attribute__((used)) static void
write_sample_client(const char *program_name, version_list *vp)
{
	proc_list *proc;
	int i;
	decl_list *l;

	f_print(fout, "\n\nvoid\n");
	pvname(program_name, vp->vers_num);
	f_print(fout, "(char *host)\n{\n");
	f_print(fout, "\tCLIENT *clnt;\n");

	i = 0;
	for (proc = vp->procs; proc != NULL; proc = proc->next) {
		f_print(fout, "\t");
		if (mtflag) {
			f_print(fout, "enum clnt_stat retval_%d;\n\t", ++i);
			ptype(proc->res_prefix, proc->res_type, 1);
			f_print(fout, "result_%d;\n", i);
		} else {
			ptype(proc->res_prefix, proc->res_type, 1);
			f_print(fout, " *result_%d;\n",++i);
		}
		/* print out declarations for arguments */
		if(proc->arg_num < 2 && !newstyle) {
			f_print(fout, "\t");
			if(!streq(proc->args.decls->decl.type, "void"))
				ptype(proc->args.decls->decl.prefix,
				      proc->args.decls->decl.type, 1);
			else
				f_print(fout, "char * "); /* cannot have "void" type */
			f_print(fout, " ");
			pvname(proc->proc_name, vp->vers_num);
			f_print(fout, "_arg;\n");
		} else if (!streq(proc->args.decls->decl.type, "void")) {
			for (l = proc->args.decls; l != NULL; l = l->next) {
				f_print(fout, "\t");
				ptype(l->decl.prefix, l->decl.type, 1);
				if (strcmp(l->decl.type,"string") >= 1)
				    f_print(fout, " ");
				pvname(proc->proc_name, vp->vers_num);
				f_print(fout, "_%s;\n", l->decl.name);
			}
		}
	}

	/* generate creation of client handle */
	f_print(fout, "\n#ifndef\tDEBUG\n");
	f_print(fout, "\tclnt = clnt_create(host, %s, %s, \"%s\");\n",
		program_name, vp->vers_name, tirpcflag? "netpath" : "udp");
	f_print(fout, "\tif (clnt == (CLIENT *) NULL) {\n");
	f_print(fout, "\t\tclnt_pcreateerror(host);\n");
	f_print(fout, "\t\texit(1);\n\t}\n");
	f_print(fout, "#endif\t/* DEBUG */\n\n");

	/* generate calls to procedures */
	i = 0;
	for (proc = vp->procs; proc != NULL; proc = proc->next) {
		if (mtflag)
			f_print(fout, "\tretval_%d = ",++i);
		else
			f_print(fout, "\tresult_%d = ",++i);
		pvname(proc->proc_name, vp->vers_num);
		if (proc->arg_num < 2 && !newstyle) {
			f_print(fout, "(");
			if(streq(proc->args.decls->decl.type, "void"))
				/* cast to void * */
				f_print(fout, "(void *)");
			f_print(fout, "&");
			pvname(proc->proc_name, vp->vers_num);
			if (mtflag)
				f_print(fout, "_arg, &result_%d, clnt);\n",
					i);
			else
				f_print(fout, "_arg, clnt);\n");

		} else if (streq(proc->args.decls->decl.type, "void")) {
			if (mtflag)
				f_print(fout, "(&result_%d, clnt);\n", i);
			else
				f_print(fout, "(clnt);\n");
		}
		else {
			f_print(fout, "(");
			for (l = proc->args.decls;  l != NULL; l = l->next) {
				pvname(proc->proc_name, vp->vers_num);
				f_print(fout, "_%s, ", l->decl.name);
			}
			if (mtflag)
				f_print(fout, "&result_%d, ", i);
				
			f_print(fout, "clnt);\n");
		}
		if (mtflag) {
			f_print(fout, "\tif (retval_%d != RPC_SUCCESS) {\n", i);

		} else {
			f_print(fout, "\tif (result_%d == (", i);
			ptype(proc->res_prefix, proc->res_type, 1);
			f_print(fout, "*) NULL) {\n");
		}
		f_print(fout, "\t\tclnt_perror(clnt, \"call failed\");\n");
		f_print(fout, "\t}\n");
	}

	f_print(fout, "#ifndef\tDEBUG\n");
	f_print(fout, "\tclnt_destroy(clnt);\n");
	f_print(fout, "#endif\t	/* DEBUG */\n");
	f_print(fout, "}\n");
}