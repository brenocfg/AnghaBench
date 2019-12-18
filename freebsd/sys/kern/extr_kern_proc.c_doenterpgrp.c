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
struct proc {struct pgrp* p_pgrp; int /*<<< orphan*/  p_session; } ;
struct pgrp {int /*<<< orphan*/  pg_members; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_LOCK_ASSERT (struct pgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SESS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  fixjobc (struct proc*,struct pgrp*,int) ; 
 int /*<<< orphan*/  p_pglist ; 
 int /*<<< orphan*/  pgdelete (struct pgrp*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
doenterpgrp(struct proc *p, struct pgrp *pgrp)
{
	struct pgrp *savepgrp;

	sx_assert(&proctree_lock, SX_XLOCKED);
	PROC_LOCK_ASSERT(p, MA_NOTOWNED);
	PGRP_LOCK_ASSERT(pgrp, MA_NOTOWNED);
	PGRP_LOCK_ASSERT(p->p_pgrp, MA_NOTOWNED);
	SESS_LOCK_ASSERT(p->p_session, MA_NOTOWNED);

	savepgrp = p->p_pgrp;

	/*
	 * Adjust eligibility of affected pgrps to participate in job control.
	 * Increment eligibility counts before decrementing, otherwise we
	 * could reach 0 spuriously during the first call.
	 */
	fixjobc(p, pgrp, 1);
	fixjobc(p, p->p_pgrp, 0);

	PGRP_LOCK(pgrp);
	PGRP_LOCK(savepgrp);
	PROC_LOCK(p);
	LIST_REMOVE(p, p_pglist);
	p->p_pgrp = pgrp;
	PROC_UNLOCK(p);
	LIST_INSERT_HEAD(&pgrp->pg_members, p, p_pglist);
	PGRP_UNLOCK(savepgrp);
	PGRP_UNLOCK(pgrp);
	if (LIST_EMPTY(&savepgrp->pg_members))
		pgdelete(savepgrp);
}