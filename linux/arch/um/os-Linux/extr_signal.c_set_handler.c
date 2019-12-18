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
struct sigaction {int sa_flags; int /*<<< orphan*/ * sa_restorer; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int SA_NODEFER ; 
 int SA_ONSTACK ; 
 int SA_RESTART ; 
 int SA_SIGINFO ; 
 int SIGALRM ; 
 int SIGIO ; 
 int SIGSEGV ; 
 int SIGWINCH ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hard_handler ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void set_handler(int sig)
{
	struct sigaction action;
	int flags = SA_SIGINFO | SA_ONSTACK;
	sigset_t sig_mask;

	action.sa_sigaction = hard_handler;

	/* block irq ones */
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGIO);
	sigaddset(&action.sa_mask, SIGWINCH);
	sigaddset(&action.sa_mask, SIGALRM);

	if (sig == SIGSEGV)
		flags |= SA_NODEFER;

	if (sigismember(&action.sa_mask, sig))
		flags |= SA_RESTART; /* if it's an irq signal */

	action.sa_flags = flags;
	action.sa_restorer = NULL;
	if (sigaction(sig, &action, NULL) < 0)
		panic("sigaction failed - errno = %d\n", errno);

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, sig);
	if (sigprocmask(SIG_UNBLOCK, &sig_mask, NULL) < 0)
		panic("sigprocmask failed - errno = %d\n", errno);
}