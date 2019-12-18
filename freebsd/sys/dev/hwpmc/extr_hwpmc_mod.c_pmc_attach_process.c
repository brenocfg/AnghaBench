#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct proc {struct proc* p_pptr; int /*<<< orphan*/  p_children; int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; } ;
struct pmc {int pm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATT ; 
 int EPERM ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct proc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCDBG5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*,int /*<<< orphan*/ ,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PMC_F_DESCENDANTS ; 
 int PMC_PP_ENABLE_MSR_ACCESS ; 
 int /*<<< orphan*/  PMC_TO_ROWINDEX (struct pmc*) ; 
 int /*<<< orphan*/  PRC ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  p_sibling ; 
 int pmc_attach_one_process (struct proc*,struct pmc*) ; 
 int /*<<< orphan*/  pmc_detach_process (struct proc*,struct pmc*) ; 
 int /*<<< orphan*/  pmc_sx ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmc_attach_process(struct proc *p, struct pmc *pm)
{
	int error;
	struct proc *top;

	sx_assert(&pmc_sx, SX_XLOCKED);

	PMCDBG5(PRC,ATT,1, "attach pm=%p ri=%d proc=%p (%d, %s)", pm,
	    PMC_TO_ROWINDEX(pm), p, p->p_pid, p->p_comm);


	/*
	 * If this PMC successfully allowed a GETMSR operation
	 * in the past, disallow further ATTACHes.
	 */

	if ((pm->pm_flags & PMC_PP_ENABLE_MSR_ACCESS) != 0)
		return EPERM;

	if ((pm->pm_flags & PMC_F_DESCENDANTS) == 0)
		return pmc_attach_one_process(p, pm);

	/*
	 * Traverse all child processes, attaching them to
	 * this PMC.
	 */

	sx_slock(&proctree_lock);

	top = p;

	for (;;) {
		if ((error = pmc_attach_one_process(p, pm)) != 0)
			break;
		if (!LIST_EMPTY(&p->p_children))
			p = LIST_FIRST(&p->p_children);
		else for (;;) {
			if (p == top)
				goto done;
			if (LIST_NEXT(p, p_sibling)) {
				p = LIST_NEXT(p, p_sibling);
				break;
			}
			p = p->p_pptr;
		}
	}

	if (error)
		(void) pmc_detach_process(top, pm);

 done:
	sx_sunlock(&proctree_lock);
	return error;
}