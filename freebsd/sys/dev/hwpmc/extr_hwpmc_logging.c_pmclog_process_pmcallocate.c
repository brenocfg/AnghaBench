#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmclog_pmcallocatedyn {int dummy; } ;
struct pmclog_pmcallocate {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_ev_name; } ;
struct pmc_soft {TYPE_1__ ps_ev; } ;
struct pmc_owner {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pm_reloadcount; } ;
struct pmc {TYPE_2__ pm_sc; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  pm_event; int /*<<< orphan*/  pm_id; struct pmc_owner* pm_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PMCALLOCATE ; 
 int /*<<< orphan*/  PMCALLOCATEDYN ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*) ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH_SYNC (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_EMIT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_EMITNULLSTRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_EMITSTRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PMC_CLASS_SOFT ; 
 int /*<<< orphan*/  PMC_NAME_MAX ; 
 scalar_t__ PMC_TO_CLASS (struct pmc*) ; 
 struct pmc_soft* pmc_soft_ev_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_soft_ev_release (struct pmc_soft*) ; 

void
pmclog_process_pmcallocate(struct pmc *pm)
{
	struct pmc_owner *po;
	struct pmc_soft *ps;

	po = pm->pm_owner;

	PMCDBG1(LOG,ALL,1, "pm=%p", pm);

	if (PMC_TO_CLASS(pm) == PMC_CLASS_SOFT) {
		PMCLOG_RESERVE(po, PMCALLOCATEDYN,
		    sizeof(struct pmclog_pmcallocatedyn));
		PMCLOG_EMIT32(pm->pm_id);
		PMCLOG_EMIT32(pm->pm_event);
		PMCLOG_EMIT32(pm->pm_flags);
		PMCLOG_EMIT32(0);
		PMCLOG_EMIT64(pm->pm_sc.pm_reloadcount);
		ps = pmc_soft_ev_acquire(pm->pm_event);
		if (ps != NULL)
			PMCLOG_EMITSTRING(ps->ps_ev.pm_ev_name,PMC_NAME_MAX);
		else
			PMCLOG_EMITNULLSTRING(PMC_NAME_MAX);
		pmc_soft_ev_release(ps);
		PMCLOG_DESPATCH_SYNC(po);
	} else {
		PMCLOG_RESERVE(po, PMCALLOCATE,
		    sizeof(struct pmclog_pmcallocate));
		PMCLOG_EMIT32(pm->pm_id);
		PMCLOG_EMIT32(pm->pm_event);
		PMCLOG_EMIT32(pm->pm_flags);
		PMCLOG_EMIT32(0);
		PMCLOG_EMIT64(pm->pm_sc.pm_reloadcount);
		PMCLOG_DESPATCH_SYNC(po);
	}
}