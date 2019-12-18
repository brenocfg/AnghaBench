#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  vers_num; TYPE_7__* procs; struct TYPE_16__* next; } ;
typedef  TYPE_6__ version_list ;
struct TYPE_15__ {int /*<<< orphan*/  argname; TYPE_4__* decls; } ;
struct TYPE_17__ {int arg_num; int /*<<< orphan*/  proc_name; int /*<<< orphan*/  res_type; TYPE_5__ args; struct TYPE_17__* next; int /*<<< orphan*/  res_prefix; } ;
typedef  TYPE_7__ proc_list ;
struct TYPE_11__ {TYPE_6__* versions; } ;
struct TYPE_12__ {TYPE_1__ pr; } ;
struct TYPE_18__ {int /*<<< orphan*/  def_name; TYPE_2__ def; } ;
typedef  TYPE_8__ definition ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  prefix; } ;
struct TYPE_14__ {TYPE_3__ decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG ; 
 int /*<<< orphan*/  RESULT ; 
 int /*<<< orphan*/  RETVAL ; 
 int /*<<< orphan*/  ROUTINE ; 
 int /*<<< orphan*/  RQSTP ; 
 int /*<<< orphan*/  TRANSP ; 
 int /*<<< orphan*/  _errbuf ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 scalar_t__ newstyle ; 
 int /*<<< orphan*/  nullproc (TYPE_7__*) ; 
 int /*<<< orphan*/  p_xdrfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_err_message (char*) ; 
 int /*<<< orphan*/  print_return (char*) ; 
 int /*<<< orphan*/  printerr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printif (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvname_svc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ timerflag ; 

__attribute__((used)) static void
write_program(definition *def, const char *storage)
{
	version_list *vp;
	proc_list *proc;
	int filled;

	for (vp = def->def.pr.versions; vp != NULL; vp = vp->next) {
		f_print(fout, "\n");
		if (storage != NULL) {
			f_print(fout, "%s ", storage);
		}
		f_print(fout, "void\n");
		pvname(def->def_name, vp->vers_num);

		f_print(fout, "(struct svc_req *%s, ", RQSTP);
		f_print(fout, "SVCXPRT *%s)\n", TRANSP);
		f_print(fout, "{\n");

		filled = 0;
		f_print(fout, "\tunion {\n");
		for (proc = vp->procs; proc != NULL; proc = proc->next) {
			if (proc->arg_num < 2) { /* single argument */
				if (streq(proc->args.decls->decl.type,
					  "void")) {
					continue;
				}
				filled = 1;
				f_print(fout, "\t\t");
				ptype(proc->args.decls->decl.prefix,
				      proc->args.decls->decl.type, 0);
				pvname(proc->proc_name, vp->vers_num);
				f_print(fout, "_arg;\n");

			} else {
				filled = 1;
				f_print(fout, "\t\t%s", proc->args.argname);
				f_print(fout, " ");
				pvname(proc->proc_name, vp->vers_num);
				f_print(fout, "_arg;\n");
			}
		}
		if (!filled) {
			f_print(fout, "\t\tint fill;\n");
		}
		f_print(fout, "\t} %s;\n", ARG);
	
		if (mtflag) {
			f_print(fout, "\tunion {\n");
			for (proc = vp->procs; proc != NULL; proc = proc->next) {
				if (streq(proc->res_type, "void")) {
					continue;
				}
				f_print(fout, "\t\t");
				ptype(proc->res_prefix, proc->res_type, 0);
				pvname(proc->proc_name, vp->vers_num);
				f_print(fout, "_res;\n");
			}
			f_print(fout, "\t} %s;\n", RESULT);
			f_print(fout, "\tbool_t %s;\n", RETVAL);
			
		} else
			f_print(fout, "\tchar *%s;\n", RESULT);

		f_print(fout, "\txdrproc_t xdr_%s, xdr_%s;\n", ARG, RESULT);
		if (mtflag)
			f_print(fout,
				"\tbool_t (*%s)(char *, void *, struct svc_req *);\n",
				ROUTINE);
		else
			f_print(fout,
				"\tchar *(*%s)(char *, struct svc_req *);\n",
				ROUTINE);
		f_print(fout, "\n");

		if (timerflag) {
			if (mtflag)
				f_print(fout, "\tpthread_mutex_lock(&_svcstate_lock);\n");

			f_print(fout, "\t_rpcsvcstate = _SERVING;\n");				
			if (mtflag)
				f_print(fout, "\tpthread_mutex_unlock(&_svcstate_lock);\n");
		}

		f_print(fout, "\tswitch (%s->rq_proc) {\n", RQSTP);
		if (!nullproc(vp->procs)) {
			f_print(fout, "\tcase NULLPROC:\n");
			f_print(fout,
				"\t\t(void) svc_sendreply(%s,\n\t\t\t"
				"(xdrproc_t) xdr_void, (char *)NULL);\n",
				TRANSP);
			print_return("\t\t");
			f_print(fout, "\n");
		}
		for (proc = vp->procs; proc != NULL; proc = proc->next) {
			f_print(fout, "\tcase %s:\n", proc->proc_name);
			if (proc->arg_num < 2) { /* single argument */
				p_xdrfunc(ARG, proc->args.decls->decl.type);
			} else {
				p_xdrfunc(ARG, proc->args.argname);
			}
			p_xdrfunc(RESULT, proc->res_type);

			if (mtflag)
				f_print(fout,
					"\t\t%s = (bool_t (*) (char *,  void *,  struct svc_req *))",
					ROUTINE);
			else
				f_print(fout,
					"\t\t%s = (char *(*)(char *, struct svc_req *)) ",
					ROUTINE);
			if (newstyle) { /* new style: calls internal routine */
				f_print(fout, "_");
			}
			if (!newstyle)
				pvname_svc(proc->proc_name, vp->vers_num);
			else
				pvname(proc->proc_name, vp->vers_num);
			f_print(fout, ";\n");
			f_print(fout, "\t\tbreak;\n\n");
		}
		f_print(fout, "\tdefault:\n");
		printerr("noproc", TRANSP);
		print_return("\t\t");
		f_print(fout, "\t}\n");

		f_print(fout,
			"\t(void) memset((char *)&%s, 0, sizeof (%s));\n",
			ARG, ARG);
		printif("getargs", TRANSP, "(caddr_t) &", ARG);
		printerr("decode", TRANSP);
		print_return("\t\t");
		f_print(fout, "\t}\n");

		if (!mtflag)
			f_print(fout, "\t%s = (*%s)((char *)&%s, %s);\n",
				RESULT, ROUTINE, ARG, RQSTP);
		else
			f_print(fout, "\t%s = (bool_t) (*%s)((char *)&%s, (void *)&%s, %s);\n",
				RETVAL, ROUTINE, ARG, RESULT, RQSTP);


		if (mtflag)
			f_print(fout,
				"\tif (%s > 0 && !svc_sendreply(%s, xdr_%s, (char *)&%s)) {\n",
				RETVAL, TRANSP, RESULT, RESULT);
		else
			f_print(fout,
				"\tif (%s != NULL && !svc_sendreply(%s, xdr_%s, %s)) {\n",
				RESULT, TRANSP, RESULT, RESULT);

		printerr("systemerr", TRANSP);
		f_print(fout, "\t}\n");

		printif("freeargs", TRANSP, "(caddr_t) &", ARG);
		(void) sprintf(_errbuf, "unable to free arguments");
		print_err_message("\t\t");
		f_print(fout, "\t\texit(1);\n");
		f_print(fout, "\t}\n");
		/* print out free routine */
		if (mtflag) {
			f_print(fout,"\tif (!");
			pvname(def->def_name, vp->vers_num);
			f_print(fout,"_freeresult(%s, xdr_%s, (caddr_t) &%s))\n",
				TRANSP, RESULT, RESULT);
			(void) sprintf(_errbuf, "unable to free results");
			print_err_message("\t\t");
			f_print(fout, "\n");
		}
		print_return("\t");
		f_print(fout, "}\n");
	}
}