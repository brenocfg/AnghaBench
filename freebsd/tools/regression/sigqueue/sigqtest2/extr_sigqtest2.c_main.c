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
union sigval {int sival_int; } ;
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGRTMIN ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  job_control_test () ; 
 int /*<<< orphan*/  rtsig_handler ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sigval) ; 

int
main()
{
	struct sigaction sa;
	sigset_t set;
	union sigval val;

	/* test job control with empty signal queue */
	job_control_test();

	/* now full fill signal queue in kernel */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = rtsig_handler;
	sigaction(SIGRTMIN, &sa, NULL);
	sigemptyset(&set);
	sigaddset(&set, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &set, NULL);
	val.sival_int = 1;
	while (sigqueue(getpid(), SIGRTMIN, val))
		;

	/* signal queue is fully filled, test the job control again. */
	job_control_test();
	return (0);
}