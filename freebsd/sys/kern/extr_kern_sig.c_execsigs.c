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
struct TYPE_2__ {scalar_t__ ss_sp; scalar_t__ ss_size; int /*<<< orphan*/  ss_flags; } ;
struct thread {int /*<<< orphan*/  td_pflags; TYPE_1__ td_sigstk; struct proc* td_proc; } ;
struct sigacts {int ps_flag; scalar_t__* ps_sigact; int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigignore; } ;
struct proc {struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int PS_CLDSIGIGN ; 
 int PS_NOCLDWAIT ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGNOTEMPTY (int /*<<< orphan*/ ) ; 
 int SIGPIPE ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  SS_DISABLE ; 
 scalar_t__ SV_ABI_CLOUDABI ; 
 scalar_t__ SV_PROC_ABI (struct proc*) ; 
 int /*<<< orphan*/  TDP_ALTSTACK ; 
 size_t _SIG_IDX (int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sig_drop_caught (struct proc*) ; 
 int sig_ffs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdflt (struct sigacts*,int) ; 

void
execsigs(struct proc *p)
{
	sigset_t osigignore;
	struct sigacts *ps;
	int sig;
	struct thread *td;

	/*
	 * Reset caught signals.  Held signals remain held
	 * through td_sigmask (unless they were caught,
	 * and are now ignored by default).
	 */
	PROC_LOCK_ASSERT(p, MA_OWNED);
	ps = p->p_sigacts;
	mtx_lock(&ps->ps_mtx);
	sig_drop_caught(p);

	/*
	 * As CloudABI processes cannot modify signal handlers, fully
	 * reset all signals to their default behavior. Do ignore
	 * SIGPIPE, as it would otherwise be impossible to recover from
	 * writes to broken pipes and sockets.
	 */
	if (SV_PROC_ABI(p) == SV_ABI_CLOUDABI) {
		osigignore = ps->ps_sigignore;
		while (SIGNOTEMPTY(osigignore)) {
			sig = sig_ffs(&osigignore);
			SIGDELSET(osigignore, sig);
			if (sig != SIGPIPE)
				sigdflt(ps, sig);
		}
		SIGADDSET(ps->ps_sigignore, SIGPIPE);
	}

	/*
	 * Reset stack state to the user stack.
	 * Clear set of signals caught on the signal stack.
	 */
	td = curthread;
	MPASS(td->td_proc == p);
	td->td_sigstk.ss_flags = SS_DISABLE;
	td->td_sigstk.ss_size = 0;
	td->td_sigstk.ss_sp = 0;
	td->td_pflags &= ~TDP_ALTSTACK;
	/*
	 * Reset no zombies if child dies flag as Solaris does.
	 */
	ps->ps_flag &= ~(PS_NOCLDWAIT | PS_CLDSIGIGN);
	if (ps->ps_sigact[_SIG_IDX(SIGCHLD)] == SIG_IGN)
		ps->ps_sigact[_SIG_IDX(SIGCHLD)] = SIG_DFL;
	mtx_unlock(&ps->ps_mtx);
}