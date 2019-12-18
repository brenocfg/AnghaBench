#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct kinfo_vmentry {scalar_t__ kve_start; char* kve_path; } ;
struct kinfo_proc {int dummy; } ;
typedef  int /*<<< orphan*/  rd_err_e ;
struct TYPE_9__ {int /*<<< orphan*/  rda_procstat; int /*<<< orphan*/  rda_php; } ;
typedef  TYPE_2__ rd_agent_t ;
struct TYPE_8__ {scalar_t__ a_val; } ;
struct TYPE_10__ {scalar_t__ a_type; TYPE_1__ a_un; } ;
typedef  TYPE_3__ Elf_Auxinfo ;

/* Variables and functions */
 scalar_t__ AT_BASE ; 
 int /*<<< orphan*/  KERN_PROC_PID ; 
 int /*<<< orphan*/  RD_ERR ; 
 int /*<<< orphan*/  RD_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  proc_getpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procstat_freeauxv (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  procstat_freeprocs (int /*<<< orphan*/ ,struct kinfo_proc*) ; 
 int /*<<< orphan*/  procstat_freevmmap (int /*<<< orphan*/ ,struct kinfo_vmentry*) ; 
 TYPE_3__* procstat_getauxv (int /*<<< orphan*/ ,struct kinfo_proc*,int*) ; 
 struct kinfo_proc* procstat_getprocs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct kinfo_vmentry* procstat_getvmmap (int /*<<< orphan*/ ,struct kinfo_proc*,int*) ; 
 scalar_t__ rtld_syms (TYPE_2__*,char const*,scalar_t__) ; 

rd_err_e
rd_reset(rd_agent_t *rdap)
{
	struct kinfo_proc *kp;
	struct kinfo_vmentry *kve;
	Elf_Auxinfo *auxv;
	const char *rtldpath;
	u_long base;
	rd_err_e rderr;
	int count, i;

	kp = NULL;
	auxv = NULL;
	kve = NULL;
	rderr = RD_ERR;

	kp = procstat_getprocs(rdap->rda_procstat, KERN_PROC_PID,
	    proc_getpid(rdap->rda_php), &count);
	if (kp == NULL)
		return (RD_ERR);
	assert(count == 1);

	auxv = procstat_getauxv(rdap->rda_procstat, kp, &count);
	if (auxv == NULL)
		goto err;

	base = 0;
	for (i = 0; i < count; i++) {
		if (auxv[i].a_type == AT_BASE) {
			base = auxv[i].a_un.a_val;
			break;
		}
	}
	if (i == count)
		goto err;

	rtldpath = NULL;
	kve = procstat_getvmmap(rdap->rda_procstat, kp, &count);
	if (kve == NULL)
		goto err;
	for (i = 0; i < count; i++) {
		if (kve[i].kve_start == base) {
			rtldpath = kve[i].kve_path;
			break;
		}
	}
	if (i == count)
		goto err;

	if (rtld_syms(rdap, rtldpath, base) != 0)
		goto err;

	rderr = RD_OK;

err:
	if (kve != NULL)
		procstat_freevmmap(rdap->rda_procstat, kve);
	if (auxv != NULL)
		procstat_freeauxv(rdap->rda_procstat, auxv);
	if (kp != NULL)
		procstat_freeprocs(rdap->rda_procstat, kp);
	return (rderr);
}