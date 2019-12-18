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
struct thread {int /*<<< orphan*/  td_sigmask; int /*<<< orphan*/  td_sigqueue; struct proc* td_proc; } ;
struct proc {int p_numthreads; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGFILLSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSETNAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_signals (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigqueue_flush (int /*<<< orphan*/ *) ; 

void
tdsigcleanup(struct thread *td)
{
	struct proc *p;
	sigset_t unblocked;

	p = td->td_proc;
	PROC_LOCK_ASSERT(p, MA_OWNED);

	sigqueue_flush(&td->td_sigqueue);
	if (p->p_numthreads == 1)
		return;

	/*
	 * Since we cannot handle signals, notify signal post code
	 * about this by filling the sigmask.
	 *
	 * Also, if needed, wake up thread(s) that do not block the
	 * same signals as the exiting thread, since the thread might
	 * have been selected for delivery and woken up.
	 */
	SIGFILLSET(unblocked);
	SIGSETNAND(unblocked, td->td_sigmask);
	SIGFILLSET(td->td_sigmask);
	reschedule_signals(p, unblocked, 0);

}