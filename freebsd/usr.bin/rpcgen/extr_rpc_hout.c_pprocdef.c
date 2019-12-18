#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vers_num; } ;
typedef  TYPE_1__ version_list ;
struct TYPE_7__ {int /*<<< orphan*/  proc_name; int /*<<< orphan*/  res_type; int /*<<< orphan*/  res_prefix; } ;
typedef  TYPE_2__ proc_list ;

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 int /*<<< orphan*/  parglist (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  ptype (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvname_svc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pprocdef(proc_list *proc, version_list *vp, const char *addargtype, int server_p)
{
	if (mtflag) {/* Print MT style stubs */
		if (server_p)
			f_print(fout, "bool_t ");
		else
			f_print(fout, "enum clnt_stat ");
	} else {
		ptype(proc->res_prefix, proc->res_type, 1);
		f_print(fout, "* ");
	}
	if (server_p)
		pvname_svc(proc->proc_name, vp->vers_num);
	else
		pvname(proc->proc_name, vp->vers_num);

	parglist(proc, addargtype);
}