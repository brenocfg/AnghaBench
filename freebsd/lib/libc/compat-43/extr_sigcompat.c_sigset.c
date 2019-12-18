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
struct sigaction {void (* sa_handler ) (int) ;} ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  void (* __sighandler_t ) (int) ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 void SIG_ERR (int) ; 
 void SIG_HOLD (int) ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int __libc_sigaction (int,struct sigaction*,struct sigaction*) ; 
 int __libc_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 
 int sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 

void
(*sigset(int sig, void (*disp)(int)))(int)
{
	sigset_t set, pset;
	struct sigaction sa, psa;

	sigemptyset(&set);
	if (sigaddset(&set, sig) == -1)
		return (SIG_ERR);
	if (__libc_sigprocmask(SIG_BLOCK, NULL, &pset) == -1)
		return (SIG_ERR);
	if ((__sighandler_t *)disp == SIG_HOLD) {
		if (__libc_sigprocmask(SIG_BLOCK, &set, &pset) == -1)
			return (SIG_ERR);
		if (sigismember(&pset, sig))
			return (SIG_HOLD);
		else {
			if (__libc_sigaction(sig, NULL, &psa) == -1)
				return (SIG_ERR);
			return (psa.sa_handler);
		}
	} else {
		if (__libc_sigprocmask(SIG_UNBLOCK, &set, &pset) == -1)
			return (SIG_ERR);
	}

	bzero(&sa, sizeof(sa));
	sa.sa_handler = disp;
	if (__libc_sigaction(sig, &sa, &psa) == -1)
		return (SIG_ERR);
	if (sigismember(&pset, sig))
		return (SIG_HOLD);
	else
		return (psa.sa_handler);
}