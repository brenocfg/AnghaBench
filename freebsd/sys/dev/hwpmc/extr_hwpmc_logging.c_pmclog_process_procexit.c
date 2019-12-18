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
struct pmclog_procexit {int dummy; } ;
struct pmc_process {TYPE_2__* pp_pmcs; TYPE_1__* pp_proc; } ;
struct pmc_owner {int dummy; } ;
struct pmc {int /*<<< orphan*/  pm_id; struct pmc_owner* pm_owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  pp_pmcval; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PMCDBG3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_EMIT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 
 int PMC_TO_ROWINDEX (struct pmc*) ; 
 int /*<<< orphan*/  PROCEXIT ; 

void
pmclog_process_procexit(struct pmc *pm, struct pmc_process *pp)
{
	int ri;
	struct pmc_owner *po;

	ri = PMC_TO_ROWINDEX(pm);
	PMCDBG3(LOG,EXT,1,"pm=%p pid=%d v=%jx", pm, pp->pp_proc->p_pid,
	    pp->pp_pmcs[ri].pp_pmcval);

	po = pm->pm_owner;

	PMCLOG_RESERVE(po, PROCEXIT, sizeof(struct pmclog_procexit));
	PMCLOG_EMIT32(pm->pm_id);
	PMCLOG_EMIT32(pp->pp_proc->p_pid);
	PMCLOG_EMIT64(pp->pp_pmcs[ri].pp_pmcval);
	PMCLOG_DESPATCH(po);
}