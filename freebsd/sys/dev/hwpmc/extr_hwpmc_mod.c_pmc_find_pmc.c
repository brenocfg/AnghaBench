#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pmc_process {TYPE_1__* pp_pmcs; } ;
struct pmc_owner {int dummy; } ;
struct pmc {int pm_flags; struct pmc_owner* pm_owner; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;
struct TYPE_6__ {int /*<<< orphan*/  td_proc; } ;
struct TYPE_5__ {size_t pmd_npmc; } ;
struct TYPE_4__ {struct pmc* pp_pmc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  FND ; 
 int /*<<< orphan*/  PMC ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCDBG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,struct pmc*) ; 
 int /*<<< orphan*/  PMC_FLAG_NONE ; 
 int PMC_F_ATTACHED_TO_OWNER ; 
 int PMC_F_DESCENDANTS ; 
 size_t PMC_ID_TO_ROWINDEX (int /*<<< orphan*/ ) ; 
 TYPE_3__* curthread ; 
 TYPE_2__* md ; 
 struct pmc_owner* pmc_find_owner_descriptor (int /*<<< orphan*/ ) ; 
 struct pmc* pmc_find_pmc_descriptor_in_process (struct pmc_owner*,int /*<<< orphan*/ ) ; 
 struct pmc_process* pmc_find_process_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmc_find_pmc(pmc_id_t pmcid, struct pmc **pmc)
{

	struct pmc *pm, *opm;
	struct pmc_owner *po;
	struct pmc_process *pp;

	PMCDBG1(PMC,FND,1, "find-pmc id=%d", pmcid);
	if (PMC_ID_TO_ROWINDEX(pmcid) >= md->pmd_npmc)
		return (EINVAL);

	if ((po = pmc_find_owner_descriptor(curthread->td_proc)) == NULL) {
		/*
		 * In case of PMC_F_DESCENDANTS child processes we will not find
		 * the current process in the owners hash list.  Find the owner
		 * process first and from there lookup the po.
		 */
		if ((pp = pmc_find_process_descriptor(curthread->td_proc,
		    PMC_FLAG_NONE)) == NULL) {
			return ESRCH;
		} else {
			opm = pp->pp_pmcs[PMC_ID_TO_ROWINDEX(pmcid)].pp_pmc;
			if (opm == NULL)
				return ESRCH;
			if ((opm->pm_flags & (PMC_F_ATTACHED_TO_OWNER|
			    PMC_F_DESCENDANTS)) != (PMC_F_ATTACHED_TO_OWNER|
			    PMC_F_DESCENDANTS))
				return ESRCH;
			po = opm->pm_owner;
		}
	}

	if ((pm = pmc_find_pmc_descriptor_in_process(po, pmcid)) == NULL)
		return EINVAL;

	PMCDBG2(PMC,FND,2, "find-pmc id=%d -> pmc=%p", pmcid, pm);

	*pmc = pm;
	return 0;
}