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
struct pmc {int pm_flags; int /*<<< orphan*/  pm_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATT ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct proc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCDBG5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*,int /*<<< orphan*/ ,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_FLAG_REMOVE ; 
 int PMC_F_ATTACH_DONE ; 
 int PMC_F_DESCENDANTS ; 
 int /*<<< orphan*/  PMC_TO_ROWINDEX (struct pmc*) ; 
 int /*<<< orphan*/  PRC ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  p_sibling ; 
 int pmc_detach_one_process (struct proc*,struct pmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_sx ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmc_detach_process(struct proc *p, struct pmc *pm)
{
	struct proc *top;

	sx_assert(&pmc_sx, SX_XLOCKED);

	PMCDBG5(PRC,ATT,1, "detach pm=%p ri=%d proc=%p (%d, %s)", pm,
	    PMC_TO_ROWINDEX(pm), p, p->p_pid, p->p_comm);

	if ((pm->pm_flags & PMC_F_DESCENDANTS) == 0)
		return pmc_detach_one_process(p, pm, PMC_FLAG_REMOVE);

	/*
	 * Traverse all children, detaching them from this PMC.  We
	 * ignore errors since we could be detaching a PMC from a
	 * partially attached proc tree.
	 */

	sx_slock(&proctree_lock);

	top = p;

	for (;;) {
		(void) pmc_detach_one_process(p, pm, PMC_FLAG_REMOVE);

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

 done:
	sx_sunlock(&proctree_lock);

	if (LIST_EMPTY(&pm->pm_targets))
		pm->pm_flags &= ~PMC_F_ATTACH_DONE;

	return 0;
}