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
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_flags; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGRTMIN ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  handler ; 
 int /*<<< orphan*/  printf (char*) ; 
 int received ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sigqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sigval) ; 

int
main()
{
	struct sigaction sa;
	union sigval val;
	int ret;
	int i;
	sigset_t set;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGRTMIN, &sa, NULL);
	sigemptyset(&set);
	sigaddset(&set, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &set, NULL);
	i = 0;
	for (;;) {
		val.sival_int = i;
		ret = sigqueue(getpid(), SIGRTMIN, val);
		if (ret == -1) {
			if (errno != EAGAIN) {
				errx(1, "errno != EAGAIN");
			}
			break;
		}
		i++;
	}
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	if (received != i)
		errx(1, "error, signal lost");
	printf("OK\n");
}