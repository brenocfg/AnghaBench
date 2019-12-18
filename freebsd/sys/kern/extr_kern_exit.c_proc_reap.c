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
struct thread {struct proc* td_proc; } ;
struct proc {scalar_t__ p_state; scalar_t__ p_oppid; int /*<<< orphan*/ * p_sigacts; int /*<<< orphan*/ * p_args; TYPE_3__* p_ucred; int /*<<< orphan*/  p_rux; int /*<<< orphan*/  p_ru; int /*<<< orphan*/  p_crux; TYPE_2__* p_stats; scalar_t__ p_xsig; scalar_t__ p_xexit; int /*<<< orphan*/ * p_klist; int /*<<< orphan*/  p_pid; int /*<<< orphan*/ * p_procdesc; int /*<<< orphan*/  p_pwait; int /*<<< orphan*/  p_ksi; TYPE_1__* p_pptr; int /*<<< orphan*/  p_slock; } ;
struct TYPE_6__ {int /*<<< orphan*/  cr_ruidinfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_cru; } ;
struct TYPE_4__ {scalar_t__ p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PTRACE ; 
 int KW_EXITCODE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/ * PIDHASHLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_ID_PID ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ PRS_ZOMBIE ; 
 int /*<<< orphan*/  RACCT_NPROC ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int WNOWAIT ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chgproccnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (TYPE_3__*) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavepgrp (struct proc*) ; 
 int /*<<< orphan*/  mac_proc_destroy (struct proc*) ; 
 int /*<<< orphan*/  mtx_spin_wait_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nprocs ; 
 int /*<<< orphan*/  p_hash ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  pargs_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pksignal (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_clear_orphan (struct proc*) ; 
 int /*<<< orphan*/  proc_id_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc* proc_realparent (struct proc*) ; 
 int /*<<< orphan*/  proc_reparent (struct proc*,struct proc*,int) ; 
 int /*<<< orphan*/  proc_set_cred (struct proc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_zone ; 
 int /*<<< orphan*/  procdesc_reap (struct proc*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  racct_proc_exit (struct proc*) ; 
 int /*<<< orphan*/  racct_sub (struct proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reaper_abandon_children (struct proc*,int) ; 
 int /*<<< orphan*/  reaper_clear (struct proc*) ; 
 int /*<<< orphan*/  ruadd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigacts_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_wait (struct proc*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct proc*) ; 
 int /*<<< orphan*/  vm_waitproc (struct proc*) ; 
 int /*<<< orphan*/  wakeup (struct proc*) ; 

void
proc_reap(struct thread *td, struct proc *p, int *status, int options)
{
	struct proc *q, *t;

	sx_assert(&proctree_lock, SA_XLOCKED);
	PROC_LOCK_ASSERT(p, MA_OWNED);
	KASSERT(p->p_state == PRS_ZOMBIE, ("proc_reap: !PRS_ZOMBIE"));

	mtx_spin_wait_unlocked(&p->p_slock);

	q = td->td_proc;

	if (status)
		*status = KW_EXITCODE(p->p_xexit, p->p_xsig);
	if (options & WNOWAIT) {
		/*
		 *  Only poll, returning the status.  Caller does not wish to
		 * release the proc struct just yet.
		 */
		PROC_UNLOCK(p);
		sx_xunlock(&proctree_lock);
		return;
	}

	PROC_LOCK(q);
	sigqueue_take(p->p_ksi);
	PROC_UNLOCK(q);

	/*
	 * If we got the child via a ptrace 'attach', we need to give it back
	 * to the old parent.
	 */
	if (p->p_oppid != p->p_pptr->p_pid) {
		PROC_UNLOCK(p);
		t = proc_realparent(p);
		PROC_LOCK(t);
		PROC_LOCK(p);
		CTR2(KTR_PTRACE,
		    "wait: traced child %d moved back to parent %d", p->p_pid,
		    t->p_pid);
		proc_reparent(p, t, false);
		PROC_UNLOCK(p);
		pksignal(t, SIGCHLD, p->p_ksi);
		wakeup(t);
		cv_broadcast(&p->p_pwait);
		PROC_UNLOCK(t);
		sx_xunlock(&proctree_lock);
		return;
	}
	PROC_UNLOCK(p);

	/*
	 * Remove other references to this process to ensure we have an
	 * exclusive reference.
	 */
	sx_xlock(PIDHASHLOCK(p->p_pid));
	LIST_REMOVE(p, p_hash);
	sx_xunlock(PIDHASHLOCK(p->p_pid));
	LIST_REMOVE(p, p_sibling);
	reaper_abandon_children(p, true);
	reaper_clear(p);
	PROC_LOCK(p);
	proc_clear_orphan(p);
	PROC_UNLOCK(p);
	leavepgrp(p);
	if (p->p_procdesc != NULL)
		procdesc_reap(p);
	sx_xunlock(&proctree_lock);

	proc_id_clear(PROC_ID_PID, p->p_pid);

	PROC_LOCK(p);
	knlist_detach(p->p_klist);
	p->p_klist = NULL;
	PROC_UNLOCK(p);

	/*
	 * Removal from allproc list and process group list paired with
	 * PROC_LOCK which was executed during that time should guarantee
	 * nothing can reach this process anymore. As such further locking
	 * is unnecessary.
	 */
	p->p_xexit = p->p_xsig = 0;		/* XXX: why? */

	PROC_LOCK(q);
	ruadd(&q->p_stats->p_cru, &q->p_crux, &p->p_ru, &p->p_rux);
	PROC_UNLOCK(q);

	/*
	 * Decrement the count of procs running with this uid.
	 */
	(void)chgproccnt(p->p_ucred->cr_ruidinfo, -1, 0);

	/*
	 * Destroy resource accounting information associated with the process.
	 */
#ifdef RACCT
	if (racct_enable) {
		PROC_LOCK(p);
		racct_sub(p, RACCT_NPROC, 1);
		PROC_UNLOCK(p);
	}
#endif
	racct_proc_exit(p);

	/*
	 * Free credentials, arguments, and sigacts.
	 */
	crfree(p->p_ucred);
	proc_set_cred(p, NULL);
	pargs_drop(p->p_args);
	p->p_args = NULL;
	sigacts_free(p->p_sigacts);
	p->p_sigacts = NULL;

	/*
	 * Do any thread-system specific cleanups.
	 */
	thread_wait(p);

	/*
	 * Give vm and machine-dependent layer a chance to free anything that
	 * cpu_exit couldn't release while still running in process context.
	 */
	vm_waitproc(p);
#ifdef MAC
	mac_proc_destroy(p);
#endif

	KASSERT(FIRST_THREAD_IN_PROC(p),
	    ("proc_reap: no residual thread!"));
	uma_zfree(proc_zone, p);
	atomic_add_int(&nprocs, -1);
}