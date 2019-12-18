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
struct thread {int /*<<< orphan*/  td_sigmask; } ;
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigintr; int /*<<< orphan*/  ps_sigcatch; } ;
struct proc {int p_flag; int /*<<< orphan*/  p_siglist; struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ERESTART ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int P_TRACED ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGISEMPTY (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int SIGPROCMASK_PS_LOCKED ; 
 int /*<<< orphan*/  SIGSETAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_CATCH ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int sig_ffs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signotify (struct thread*) ; 
 struct thread* sigtd (struct proc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdsigwakeup (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reschedule_signals(struct proc *p, sigset_t block, int flags)
{
	struct sigacts *ps;
	struct thread *td;
	int sig;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	ps = p->p_sigacts;
	mtx_assert(&ps->ps_mtx, (flags & SIGPROCMASK_PS_LOCKED) != 0 ?
	    MA_OWNED : MA_NOTOWNED);
	if (SIGISEMPTY(p->p_siglist))
		return;
	SIGSETAND(block, p->p_siglist);
	while ((sig = sig_ffs(&block)) != 0) {
		SIGDELSET(block, sig);
		td = sigtd(p, sig, 0);
		signotify(td);
		if (!(flags & SIGPROCMASK_PS_LOCKED))
			mtx_lock(&ps->ps_mtx);
		if (p->p_flag & P_TRACED ||
		    (SIGISMEMBER(ps->ps_sigcatch, sig) &&
		    !SIGISMEMBER(td->td_sigmask, sig)))
			tdsigwakeup(td, sig, SIG_CATCH,
			    (SIGISMEMBER(ps->ps_sigintr, sig) ? EINTR :
			     ERESTART));
		if (!(flags & SIGPROCMASK_PS_LOCKED))
			mtx_unlock(&ps->ps_mtx);
	}
}