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
struct sigaction {int /*<<< orphan*/  sa_mask; void* sa_handler; scalar_t__ sa_flags; void* sa_sigaction; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ SA_SIGINFO ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  alarm (int) ; 
 void* alarm_handler ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
setup(void *dummy)
{
	struct sigaction sa;
	sigset_t ss;
#ifdef SA_SIGINFO
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = alarm_handler;
#else
	sa.sa_flags = 0;
	sa.sa_handler = alarm_handler;
#endif
	sigfillset(&ss);
	sigprocmask(SIG_SETMASK, &ss, NULL);
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);
	alarm(1);

	return NULL;
}