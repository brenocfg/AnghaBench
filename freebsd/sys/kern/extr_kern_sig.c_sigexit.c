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
struct thread {TYPE_3__* td_ucred; struct proc* td_proc; } ;
struct proc {int p_sig; TYPE_2__* p_ucred; int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_acflag; } ;
struct TYPE_6__ {int /*<<< orphan*/  cr_uid; } ;
struct TYPE_5__ {TYPE_1__* cr_prison; } ;
struct TYPE_4__ {int /*<<< orphan*/  pr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXSIG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int SIGPROP_CORE ; 
 int /*<<< orphan*/  SINGLE_NO_EXIT ; 
 int WCOREFLAG ; 
 scalar_t__ coredump (struct thread*) ; 
 int /*<<< orphan*/  exit1 (struct thread*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kern_logsigexit ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int sigprop (int) ; 
 scalar_t__ thread_single (struct proc*,int /*<<< orphan*/ ) ; 

void
sigexit(struct thread *td, int sig)
{
	struct proc *p = td->td_proc;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	p->p_acflag |= AXSIG;
	/*
	 * We must be single-threading to generate a core dump.  This
	 * ensures that the registers in the core file are up-to-date.
	 * Also, the ELF dump handler assumes that the thread list doesn't
	 * change out from under it.
	 *
	 * XXX If another thread attempts to single-thread before us
	 *     (e.g. via fork()), we won't get a dump at all.
	 */
	if ((sigprop(sig) & SIGPROP_CORE) &&
	    thread_single(p, SINGLE_NO_EXIT) == 0) {
		p->p_sig = sig;
		/*
		 * Log signals which would cause core dumps
		 * (Log as LOG_INFO to appease those who don't want
		 * these messages.)
		 * XXX : Todo, as well as euid, write out ruid too
		 * Note that coredump() drops proc lock.
		 */
		if (coredump(td) == 0)
			sig |= WCOREFLAG;
		if (kern_logsigexit)
			log(LOG_INFO,
			    "pid %d (%s), jid %d, uid %d: exited on "
			    "signal %d%s\n", p->p_pid, p->p_comm,
			    p->p_ucred->cr_prison->pr_id,
			    td->td_ucred->cr_uid,
			    sig &~ WCOREFLAG,
			    sig & WCOREFLAG ? " (core dumped)" : "");
	} else
		PROC_UNLOCK(p);
	exit1(td, 0, sig);
	/* NOTREACHED */
}