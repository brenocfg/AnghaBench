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
struct vnode {int dummy; } ;
struct tty {struct session* t_session; } ;
struct session {int /*<<< orphan*/ * s_leader; int /*<<< orphan*/ * s_ttydp; struct vnode* s_ttyvp; struct tty* s_ttyp; } ;
struct proc {int p_flag; scalar_t__ p_pgrp; struct session* p_session; int /*<<< orphan*/  p_children; TYPE_1__* p_pptr; } ;
struct TYPE_2__ {scalar_t__ p_pgrp; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  REVOKEALL ; 
 scalar_t__ SESS_LEADER (struct proc*) ; 
 int /*<<< orphan*/  SESS_LOCK (struct session*) ; 
 int /*<<< orphan*/  SESS_UNLOCK (struct session*) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  VOP_REVOKE (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  fixjobc (struct proc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_signal_pgrp (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 scalar_t__ vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

void
killjobc(void)
{
	struct session *sp;
	struct tty *tp;
	struct proc *p;
	struct vnode *ttyvp;

	p = curproc;
	MPASS(p->p_flag & P_WEXIT);
	/*
	 * Do a quick check to see if there is anything to do with the
	 * proctree_lock held. pgrp and LIST_EMPTY checks are for fixjobc().
	 */
	PROC_LOCK(p);
	if (!SESS_LEADER(p) &&
	    (p->p_pgrp == p->p_pptr->p_pgrp) &&
	    LIST_EMPTY(&p->p_children)) {
		PROC_UNLOCK(p);
		return;
	}
	PROC_UNLOCK(p);

	sx_xlock(&proctree_lock);
	if (SESS_LEADER(p)) {
		sp = p->p_session;

		/*
		 * s_ttyp is not zero'd; we use this to indicate that
		 * the session once had a controlling terminal. (for
		 * logging and informational purposes)
		 */
		SESS_LOCK(sp);
		ttyvp = sp->s_ttyvp;
		tp = sp->s_ttyp;
		sp->s_ttyvp = NULL;
		sp->s_ttydp = NULL;
		sp->s_leader = NULL;
		SESS_UNLOCK(sp);

		/*
		 * Signal foreground pgrp and revoke access to
		 * controlling terminal if it has not been revoked
		 * already.
		 *
		 * Because the TTY may have been revoked in the mean
		 * time and could already have a new session associated
		 * with it, make sure we don't send a SIGHUP to a
		 * foreground process group that does not belong to this
		 * session.
		 */

		if (tp != NULL) {
			tty_lock(tp);
			if (tp->t_session == sp)
				tty_signal_pgrp(tp, SIGHUP);
			tty_unlock(tp);
		}

		if (ttyvp != NULL) {
			sx_xunlock(&proctree_lock);
			if (vn_lock(ttyvp, LK_EXCLUSIVE) == 0) {
				VOP_REVOKE(ttyvp, REVOKEALL);
				VOP_UNLOCK(ttyvp, 0);
			}
			vrele(ttyvp);
			sx_xlock(&proctree_lock);
		}
	}
	fixjobc(p, p->p_pgrp, 0);
	sx_xunlock(&proctree_lock);
}