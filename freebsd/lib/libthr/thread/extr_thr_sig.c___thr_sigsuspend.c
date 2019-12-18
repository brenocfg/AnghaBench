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
struct pthread {int in_sigsuspend; scalar_t__ unblock_sigcancel; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  __sys_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int __sys_sigsuspend (int /*<<< orphan*/ ) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 
 int /*<<< orphan*/  thr_remove_thr_signals (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
__thr_sigsuspend(const sigset_t * set)
{
	struct pthread *curthread;
	sigset_t newset;
	int ret, old;

	curthread = _get_curthread();

	old = curthread->in_sigsuspend;
	curthread->in_sigsuspend = 1;
	_thr_cancel_enter(curthread);
	ret = __sys_sigsuspend(thr_remove_thr_signals(set, &newset));
	_thr_cancel_leave(curthread, 1);
	curthread->in_sigsuspend = old;
	if (curthread->unblock_sigcancel) {
		curthread->unblock_sigcancel = 0;
		SIGEMPTYSET(newset);
		SIGADDSET(newset, SIGCANCEL);
		__sys_sigprocmask(SIG_UNBLOCK, &newset, NULL);
	}

	return (ret);
}