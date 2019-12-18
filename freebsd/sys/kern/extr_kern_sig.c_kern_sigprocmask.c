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
struct thread {int /*<<< orphan*/  td_sigmask; struct proc* td_proc; } ;
struct proc {int p_numthreads; TYPE_1__* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  ps_mtx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int SIGPROCMASK_OLD ; 
 int SIGPROCMASK_PROC_LOCKED ; 
 int SIGPROCMASK_PS_LOCKED ; 
 int /*<<< orphan*/  SIGSETLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSETNAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSETOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SIG_BLOCK 130 
 int /*<<< orphan*/  SIG_CANTMASK (int /*<<< orphan*/ ) ; 
#define  SIG_SETMASK 129 
#define  SIG_UNBLOCK 128 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_signals (struct proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signotify (struct thread*) ; 

int
kern_sigprocmask(struct thread *td, int how, sigset_t *set, sigset_t *oset,
    int flags)
{
	sigset_t new_block, oset1;
	struct proc *p;
	int error;

	p = td->td_proc;
	if ((flags & SIGPROCMASK_PROC_LOCKED) != 0)
		PROC_LOCK_ASSERT(p, MA_OWNED);
	else
		PROC_LOCK(p);
	mtx_assert(&p->p_sigacts->ps_mtx, (flags & SIGPROCMASK_PS_LOCKED) != 0
	    ? MA_OWNED : MA_NOTOWNED);
	if (oset != NULL)
		*oset = td->td_sigmask;

	error = 0;
	if (set != NULL) {
		switch (how) {
		case SIG_BLOCK:
			SIG_CANTMASK(*set);
			oset1 = td->td_sigmask;
			SIGSETOR(td->td_sigmask, *set);
			new_block = td->td_sigmask;
			SIGSETNAND(new_block, oset1);
			break;
		case SIG_UNBLOCK:
			SIGSETNAND(td->td_sigmask, *set);
			signotify(td);
			goto out;
		case SIG_SETMASK:
			SIG_CANTMASK(*set);
			oset1 = td->td_sigmask;
			if (flags & SIGPROCMASK_OLD)
				SIGSETLO(td->td_sigmask, *set);
			else
				td->td_sigmask = *set;
			new_block = td->td_sigmask;
			SIGSETNAND(new_block, oset1);
			signotify(td);
			break;
		default:
			error = EINVAL;
			goto out;
		}

		/*
		 * The new_block set contains signals that were not previously
		 * blocked, but are blocked now.
		 *
		 * In case we block any signal that was not previously blocked
		 * for td, and process has the signal pending, try to schedule
		 * signal delivery to some thread that does not block the
		 * signal, possibly waking it up.
		 */
		if (p->p_numthreads != 1)
			reschedule_signals(p, new_block, flags);
	}

out:
	if (!(flags & SIGPROCMASK_PROC_LOCKED))
		PROC_UNLOCK(p);
	return (error);
}