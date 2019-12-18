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
struct tty {int dummy; } ;
struct session {struct tty* s_ttyp; } ;
struct pgrp {int /*<<< orphan*/  pg_mtx; int /*<<< orphan*/  pg_id; struct session* pg_session; int /*<<< orphan*/  pg_sigiolst; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct pgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  M_PGRP ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_LOCK_ASSERT (struct pgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_ID_GROUP ; 
 int /*<<< orphan*/  SESS_LOCK_ASSERT (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  free (struct pgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funsetownlst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_hash ; 
 int /*<<< orphan*/  proc_id_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sess_release (struct session*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_pgrp (struct tty*,struct pgrp*) ; 

__attribute__((used)) static void
pgdelete(struct pgrp *pgrp)
{
	struct session *savesess;
	struct tty *tp;

	sx_assert(&proctree_lock, SX_XLOCKED);
	PGRP_LOCK_ASSERT(pgrp, MA_NOTOWNED);
	SESS_LOCK_ASSERT(pgrp->pg_session, MA_NOTOWNED);

	/*
	 * Reset any sigio structures pointing to us as a result of
	 * F_SETOWN with our pgid.
	 */
	funsetownlst(&pgrp->pg_sigiolst);

	PGRP_LOCK(pgrp);
	tp = pgrp->pg_session->s_ttyp;
	LIST_REMOVE(pgrp, pg_hash);
	savesess = pgrp->pg_session;
	PGRP_UNLOCK(pgrp);

	/* Remove the reference to the pgrp before deallocating it. */
	if (tp != NULL) {
		tty_lock(tp);
		tty_rel_pgrp(tp, pgrp);
	}

	proc_id_clear(PROC_ID_GROUP, pgrp->pg_id);
	mtx_destroy(&pgrp->pg_mtx);
	free(pgrp, M_PGRP);
	sess_release(savesess);
}