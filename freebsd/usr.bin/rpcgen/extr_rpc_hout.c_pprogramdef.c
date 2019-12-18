#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  vers_num; TYPE_4__* procs; int /*<<< orphan*/  vers_name; struct TYPE_14__* next; } ;
typedef  TYPE_3__ version_list ;
struct TYPE_15__ {int /*<<< orphan*/  proc_num; int /*<<< orphan*/  proc_name; struct TYPE_15__* next; } ;
typedef  TYPE_4__ proc_list ;
struct TYPE_12__ {TYPE_3__* versions; int /*<<< orphan*/  prog_num; } ;
struct TYPE_13__ {TYPE_1__ pr; } ;
struct TYPE_16__ {int /*<<< orphan*/  def_name; TYPE_2__ def; } ;
typedef  TYPE_5__ definition ;

/* Variables and functions */
 int /*<<< orphan*/  define_printed (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  locase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pargdef (TYPE_5__*) ; 
 int /*<<< orphan*/  pdispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfreeprocdef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprocdef (TYPE_4__*,TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  puldefine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tblflag ; 

__attribute__((used)) static void
pprogramdef(definition *def, int headeronly)
{
	version_list *vers;
	proc_list *proc;
	const char *ext;

	pargdef(def);

	puldefine(def->def_name, def->def.pr.prog_num);
	for (vers = def->def.pr.versions; vers != NULL; vers = vers->next) {
		if (tblflag) {
			f_print(fout,
				"extern struct rpcgen_table %s_%s_table[];\n",
				locase(def->def_name), vers->vers_num);
			f_print(fout,
				"extern %s_%s_nproc;\n",
				locase(def->def_name), vers->vers_num);
		}
		puldefine(vers->vers_name, vers->vers_num);

		f_print(fout, "\n");
		ext = "extern  ";
		if (headeronly) {
			f_print(fout, "%s", ext);
			pdispatch(def->def_name, vers->vers_num);
		}
		for (proc = vers->procs; proc != NULL; proc = proc->next) {
			if (!define_printed(proc, def->def.pr.versions)) {
				puldefine(proc->proc_name, proc->proc_num);
			}
			f_print(fout, "%s", ext);
			pprocdef(proc, vers, "CLIENT *", 0);
			f_print(fout, "%s", ext);
			pprocdef(proc, vers, "struct svc_req *", 1);
		}
		pfreeprocdef(def->def_name, vers->vers_num);
	}
}