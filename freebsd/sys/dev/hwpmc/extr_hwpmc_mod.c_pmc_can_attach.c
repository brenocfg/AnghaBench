#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {scalar_t__ cr_uid; scalar_t__ cr_svuid; scalar_t__ cr_ruid; int cr_ngroups; int /*<<< orphan*/  cr_svgid; int /*<<< orphan*/  cr_rgid; int /*<<< orphan*/ * cr_groups; } ;
struct proc {struct ucred* p_ucred; } ;
struct pmc {TYPE_1__* pm_owner; } ;
struct TYPE_2__ {struct proc* po_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int /*<<< orphan*/  groupmember (int /*<<< orphan*/ ,struct ucred*) ; 

__attribute__((used)) static int
pmc_can_attach(struct pmc *pm, struct proc *t)
{
	struct proc *o;		/* pmc owner */
	struct ucred *oc, *tc;	/* owner, target credentials */
	int decline_attach, i;

	/*
	 * A PMC's owner can always attach that PMC to itself.
	 */

	if ((o = pm->pm_owner->po_owner) == t)
		return 0;

	PROC_LOCK(o);
	oc = o->p_ucred;
	crhold(oc);
	PROC_UNLOCK(o);

	PROC_LOCK(t);
	tc = t->p_ucred;
	crhold(tc);
	PROC_UNLOCK(t);

	/*
	 * The effective uid of the PMC owner should match at least one
	 * of the {effective,real,saved} uids of the target process.
	 */

	decline_attach = oc->cr_uid != tc->cr_uid &&
	    oc->cr_uid != tc->cr_svuid &&
	    oc->cr_uid != tc->cr_ruid;

	/*
	 * Every one of the target's group ids, must be in the owner's
	 * group list.
	 */
	for (i = 0; !decline_attach && i < tc->cr_ngroups; i++)
		decline_attach = !groupmember(tc->cr_groups[i], oc);

	/* check the read and saved gids too */
	if (decline_attach == 0)
		decline_attach = !groupmember(tc->cr_rgid, oc) ||
		    !groupmember(tc->cr_svgid, oc);

	crfree(tc);
	crfree(oc);

	return !decline_attach;
}