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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int ACCT_EXITREQ ; 
 int ACCT_RUNNING ; 
 int /*<<< orphan*/  PRI_MAX_KERN ; 
 int acct_state ; 
 int /*<<< orphan*/  acct_sx ; 
 int acctchkfreq ; 
 int /*<<< orphan*/  acctwatch () ; 
 int /*<<< orphan*/  curthread ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_sleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acct_thread(void *dummy)
{
	u_char pri;

	/* This is a low-priority kernel thread. */
	pri = PRI_MAX_KERN;
	thread_lock(curthread);
	sched_prio(curthread, pri);
	thread_unlock(curthread);

	/* If another accounting kthread is already running, just die. */
	sx_xlock(&acct_sx);
	if (acct_state & ACCT_RUNNING) {
		sx_xunlock(&acct_sx);
		kproc_exit(0);
	}
	acct_state |= ACCT_RUNNING;

	/* Loop until we are asked to exit. */
	while (!(acct_state & ACCT_EXITREQ)) {

		/* Perform our periodic checks. */
		acctwatch();

		/*
		 * We check this flag again before sleeping since the
		 * acctwatch() might have shut down accounting and asked us
		 * to exit.
		 */
		if (!(acct_state & ACCT_EXITREQ)) {
			sx_sleep(&acct_state, &acct_sx, 0, "-",
			    acctchkfreq * hz);
		}
	}

	/*
	 * Acknowledge the exit request and shutdown.  We clear both the
	 * exit request and running flags.
	 */
	acct_state = 0;
	sx_xunlock(&acct_sx);
	kproc_exit(0);
}