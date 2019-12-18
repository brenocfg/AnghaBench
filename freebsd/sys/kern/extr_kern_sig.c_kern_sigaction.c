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
struct thread {struct proc* td_proc; } ;
struct sigacts {int ps_flag; int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_osigset; int /*<<< orphan*/ ** ps_sigact; int /*<<< orphan*/  ps_freebsd4; int /*<<< orphan*/  ps_sigcatch; int /*<<< orphan*/  ps_sigignore; int /*<<< orphan*/  ps_signodefer; int /*<<< orphan*/  ps_sigreset; int /*<<< orphan*/  ps_sigonstack; int /*<<< orphan*/  ps_sigintr; int /*<<< orphan*/  ps_siginfo; int /*<<< orphan*/ * ps_catchmask; } ;
struct sigaction {int sa_flags; int /*<<< orphan*/ * sa_handler; int /*<<< orphan*/ * sa_sigaction; int /*<<< orphan*/  sa_mask; } ;
struct proc {int p_pid; struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  __siginfohandler_t ;
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */
 int EINVAL ; 
 int KSA_FREEBSD4 ; 
 int KSA_OSIGSET ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int PS_CLDSIGIGN ; 
 int PS_NOCLDSTOP ; 
 int PS_NOCLDWAIT ; 
 int SA_NOCLDSTOP ; 
 int SA_NOCLDWAIT ; 
 int SA_NODEFER ; 
 int SA_ONSTACK ; 
 int SA_RESETHAND ; 
 int SA_RESTART ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int SIGCHLD ; 
 int SIGCONT ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int SIGKILL ; 
 int SIGPROP_IGNORE ; 
 int SIGSTOP ; 
 int /*<<< orphan*/  SIG_CANTMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SIG_DFL ; 
 int /*<<< orphan*/ * SIG_IGN ; 
 size_t _SIG_IDX (int) ; 
 int /*<<< orphan*/  _SIG_VALID (int) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sigact_flag_test (struct sigaction const*,int) ; 
 int sigprop (int) ; 
 int /*<<< orphan*/  sigqueue_delete_proc (struct proc*,int) ; 

int
kern_sigaction(struct thread *td, int sig, const struct sigaction *act,
    struct sigaction *oact, int flags)
{
	struct sigacts *ps;
	struct proc *p = td->td_proc;

	if (!_SIG_VALID(sig))
		return (EINVAL);
	if (act != NULL && act->sa_handler != SIG_DFL &&
	    act->sa_handler != SIG_IGN && (act->sa_flags & ~(SA_ONSTACK |
	    SA_RESTART | SA_RESETHAND | SA_NOCLDSTOP | SA_NODEFER |
	    SA_NOCLDWAIT | SA_SIGINFO)) != 0)
		return (EINVAL);

	PROC_LOCK(p);
	ps = p->p_sigacts;
	mtx_lock(&ps->ps_mtx);
	if (oact) {
		memset(oact, 0, sizeof(*oact));
		oact->sa_mask = ps->ps_catchmask[_SIG_IDX(sig)];
		if (SIGISMEMBER(ps->ps_sigonstack, sig))
			oact->sa_flags |= SA_ONSTACK;
		if (!SIGISMEMBER(ps->ps_sigintr, sig))
			oact->sa_flags |= SA_RESTART;
		if (SIGISMEMBER(ps->ps_sigreset, sig))
			oact->sa_flags |= SA_RESETHAND;
		if (SIGISMEMBER(ps->ps_signodefer, sig))
			oact->sa_flags |= SA_NODEFER;
		if (SIGISMEMBER(ps->ps_siginfo, sig)) {
			oact->sa_flags |= SA_SIGINFO;
			oact->sa_sigaction =
			    (__siginfohandler_t *)ps->ps_sigact[_SIG_IDX(sig)];
		} else
			oact->sa_handler = ps->ps_sigact[_SIG_IDX(sig)];
		if (sig == SIGCHLD && ps->ps_flag & PS_NOCLDSTOP)
			oact->sa_flags |= SA_NOCLDSTOP;
		if (sig == SIGCHLD && ps->ps_flag & PS_NOCLDWAIT)
			oact->sa_flags |= SA_NOCLDWAIT;
	}
	if (act) {
		if ((sig == SIGKILL || sig == SIGSTOP) &&
		    act->sa_handler != SIG_DFL) {
			mtx_unlock(&ps->ps_mtx);
			PROC_UNLOCK(p);
			return (EINVAL);
		}

		/*
		 * Change setting atomically.
		 */

		ps->ps_catchmask[_SIG_IDX(sig)] = act->sa_mask;
		SIG_CANTMASK(ps->ps_catchmask[_SIG_IDX(sig)]);
		if (sigact_flag_test(act, SA_SIGINFO)) {
			ps->ps_sigact[_SIG_IDX(sig)] =
			    (__sighandler_t *)act->sa_sigaction;
			SIGADDSET(ps->ps_siginfo, sig);
		} else {
			ps->ps_sigact[_SIG_IDX(sig)] = act->sa_handler;
			SIGDELSET(ps->ps_siginfo, sig);
		}
		if (!sigact_flag_test(act, SA_RESTART))
			SIGADDSET(ps->ps_sigintr, sig);
		else
			SIGDELSET(ps->ps_sigintr, sig);
		if (sigact_flag_test(act, SA_ONSTACK))
			SIGADDSET(ps->ps_sigonstack, sig);
		else
			SIGDELSET(ps->ps_sigonstack, sig);
		if (sigact_flag_test(act, SA_RESETHAND))
			SIGADDSET(ps->ps_sigreset, sig);
		else
			SIGDELSET(ps->ps_sigreset, sig);
		if (sigact_flag_test(act, SA_NODEFER))
			SIGADDSET(ps->ps_signodefer, sig);
		else
			SIGDELSET(ps->ps_signodefer, sig);
		if (sig == SIGCHLD) {
			if (act->sa_flags & SA_NOCLDSTOP)
				ps->ps_flag |= PS_NOCLDSTOP;
			else
				ps->ps_flag &= ~PS_NOCLDSTOP;
			if (act->sa_flags & SA_NOCLDWAIT) {
				/*
				 * Paranoia: since SA_NOCLDWAIT is implemented
				 * by reparenting the dying child to PID 1 (and
				 * trust it to reap the zombie), PID 1 itself
				 * is forbidden to set SA_NOCLDWAIT.
				 */
				if (p->p_pid == 1)
					ps->ps_flag &= ~PS_NOCLDWAIT;
				else
					ps->ps_flag |= PS_NOCLDWAIT;
			} else
				ps->ps_flag &= ~PS_NOCLDWAIT;
			if (ps->ps_sigact[_SIG_IDX(SIGCHLD)] == SIG_IGN)
				ps->ps_flag |= PS_CLDSIGIGN;
			else
				ps->ps_flag &= ~PS_CLDSIGIGN;
		}
		/*
		 * Set bit in ps_sigignore for signals that are set to SIG_IGN,
		 * and for signals set to SIG_DFL where the default is to
		 * ignore. However, don't put SIGCONT in ps_sigignore, as we
		 * have to restart the process.
		 */
		if (ps->ps_sigact[_SIG_IDX(sig)] == SIG_IGN ||
		    (sigprop(sig) & SIGPROP_IGNORE &&
		     ps->ps_sigact[_SIG_IDX(sig)] == SIG_DFL)) {
			/* never to be seen again */
			sigqueue_delete_proc(p, sig);
			if (sig != SIGCONT)
				/* easier in psignal */
				SIGADDSET(ps->ps_sigignore, sig);
			SIGDELSET(ps->ps_sigcatch, sig);
		} else {
			SIGDELSET(ps->ps_sigignore, sig);
			if (ps->ps_sigact[_SIG_IDX(sig)] == SIG_DFL)
				SIGDELSET(ps->ps_sigcatch, sig);
			else
				SIGADDSET(ps->ps_sigcatch, sig);
		}
#ifdef COMPAT_FREEBSD4
		if (ps->ps_sigact[_SIG_IDX(sig)] == SIG_IGN ||
		    ps->ps_sigact[_SIG_IDX(sig)] == SIG_DFL ||
		    (flags & KSA_FREEBSD4) == 0)
			SIGDELSET(ps->ps_freebsd4, sig);
		else
			SIGADDSET(ps->ps_freebsd4, sig);
#endif
#ifdef COMPAT_43
		if (ps->ps_sigact[_SIG_IDX(sig)] == SIG_IGN ||
		    ps->ps_sigact[_SIG_IDX(sig)] == SIG_DFL ||
		    (flags & KSA_OSIGSET) == 0)
			SIGDELSET(ps->ps_osigset, sig);
		else
			SIGADDSET(ps->ps_osigset, sig);
#endif
	}
	mtx_unlock(&ps->ps_mtx);
	PROC_UNLOCK(p);
	return (0);
}