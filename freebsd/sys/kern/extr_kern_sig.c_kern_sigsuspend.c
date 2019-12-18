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
struct thread {int /*<<< orphan*/  td_pflags; int /*<<< orphan*/  td_errno; int /*<<< orphan*/  td_oldsigmask; struct proc* td_proc; } ;
struct proc {TYPE_2__* p_sigacts; int /*<<< orphan*/  p_mtx; TYPE_1__* p_sysent; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {int /*<<< orphan*/  ps_mtx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sv_set_syscall_retval ) (struct thread*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCATCH ; 
 int PPAUSE ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGPROCMASK_PROC_LOCKED ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TDP_NERRNO ; 
 int /*<<< orphan*/  TDP_OLDMASK ; 
 int cursig (struct thread*) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ msleep (TYPE_2__**,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ postsig (int) ; 
 int /*<<< orphan*/  stub1 (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_suspend_check (int /*<<< orphan*/ ) ; 

int
kern_sigsuspend(struct thread *td, sigset_t mask)
{
	struct proc *p = td->td_proc;
	int has_sig, sig;

	/*
	 * When returning from sigsuspend, we want
	 * the old mask to be restored after the
	 * signal handler has finished.  Thus, we
	 * save it here and mark the sigacts structure
	 * to indicate this.
	 */
	PROC_LOCK(p);
	kern_sigprocmask(td, SIG_SETMASK, &mask, &td->td_oldsigmask,
	    SIGPROCMASK_PROC_LOCKED);
	td->td_pflags |= TDP_OLDMASK;

	/*
	 * Process signals now. Otherwise, we can get spurious wakeup
	 * due to signal entered process queue, but delivered to other
	 * thread. But sigsuspend should return only on signal
	 * delivery.
	 */
	(p->p_sysent->sv_set_syscall_retval)(td, EINTR);
	for (has_sig = 0; !has_sig;) {
		while (msleep(&p->p_sigacts, &p->p_mtx, PPAUSE|PCATCH, "pause",
			0) == 0)
			/* void */;
		thread_suspend_check(0);
		mtx_lock(&p->p_sigacts->ps_mtx);
		while ((sig = cursig(td)) != 0) {
			KASSERT(sig >= 0, ("sig %d", sig));
			has_sig += postsig(sig);
		}
		mtx_unlock(&p->p_sigacts->ps_mtx);
	}
	PROC_UNLOCK(p);
	td->td_errno = EINTR;
	td->td_pflags |= TDP_NERRNO;
	return (EJUSTRETURN);
}