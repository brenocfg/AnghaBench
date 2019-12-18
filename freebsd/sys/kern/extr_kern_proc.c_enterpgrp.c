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
struct session {scalar_t__ s_sid; int /*<<< orphan*/  s_login; int /*<<< orphan*/ * s_ttyp; int /*<<< orphan*/ * s_ttydp; int /*<<< orphan*/ * s_ttyvp; int /*<<< orphan*/  s_count; struct proc* s_leader; int /*<<< orphan*/  s_mtx; } ;
struct proc {scalar_t__ p_pid; struct session* p_session; int /*<<< orphan*/  p_flag; } ;
struct pgrp {int /*<<< orphan*/  pg_sigiolst; scalar_t__ pg_jobc; int /*<<< orphan*/  pg_members; scalar_t__ pg_id; struct session* pg_session; int /*<<< orphan*/  pg_mtx; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct pgrp*,int /*<<< orphan*/ ) ; 
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int /*<<< orphan*/  PGRPHASH (scalar_t__) ; 
 int /*<<< orphan*/  PGRP_LOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PROC_ID_GROUP ; 
 int /*<<< orphan*/  PROC_ID_SESSION ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  P_CONTROLT ; 
 int /*<<< orphan*/  SESS_LEADER (struct proc*) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  doenterpgrp (struct proc*,struct pgrp*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_hash ; 
 int /*<<< orphan*/ * pgfind (scalar_t__) ; 
 int /*<<< orphan*/  proc_id_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sess_hold (struct session*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
enterpgrp(struct proc *p, pid_t pgid, struct pgrp *pgrp, struct session *sess)
{

	sx_assert(&proctree_lock, SX_XLOCKED);

	KASSERT(pgrp != NULL, ("enterpgrp: pgrp == NULL"));
	KASSERT(p->p_pid == pgid,
	    ("enterpgrp: new pgrp and pid != pgid"));
	KASSERT(pgfind(pgid) == NULL,
	    ("enterpgrp: pgrp with pgid exists"));
	KASSERT(!SESS_LEADER(p),
	    ("enterpgrp: session leader attempted setpgrp"));

	mtx_init(&pgrp->pg_mtx, "process group", NULL, MTX_DEF | MTX_DUPOK);

	if (sess != NULL) {
		/*
		 * new session
		 */
		mtx_init(&sess->s_mtx, "session", NULL, MTX_DEF);
		PROC_LOCK(p);
		p->p_flag &= ~P_CONTROLT;
		PROC_UNLOCK(p);
		PGRP_LOCK(pgrp);
		sess->s_leader = p;
		sess->s_sid = p->p_pid;
		proc_id_set(PROC_ID_SESSION, p->p_pid);
		refcount_init(&sess->s_count, 1);
		sess->s_ttyvp = NULL;
		sess->s_ttydp = NULL;
		sess->s_ttyp = NULL;
		bcopy(p->p_session->s_login, sess->s_login,
			    sizeof(sess->s_login));
		pgrp->pg_session = sess;
		KASSERT(p == curproc,
		    ("enterpgrp: mksession and p != curproc"));
	} else {
		pgrp->pg_session = p->p_session;
		sess_hold(pgrp->pg_session);
		PGRP_LOCK(pgrp);
	}
	pgrp->pg_id = pgid;
	proc_id_set(PROC_ID_GROUP, p->p_pid);
	LIST_INIT(&pgrp->pg_members);

	/*
	 * As we have an exclusive lock of proctree_lock,
	 * this should not deadlock.
	 */
	LIST_INSERT_HEAD(PGRPHASH(pgid), pgrp, pg_hash);
	pgrp->pg_jobc = 0;
	SLIST_INIT(&pgrp->pg_sigiolst);
	PGRP_UNLOCK(pgrp);

	doenterpgrp(p, pgrp);

	return (0);
}