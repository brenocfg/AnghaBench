#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uc_sigmask; } ;
typedef  TYPE_1__ ucontext_t ;
struct sigaction {int dummy; } ;
struct usigaction {int /*<<< orphan*/  lock; struct sigaction sigact; } ;
struct pthread {int /*<<< orphan*/  deferred_sigmask; int /*<<< orphan*/  deferred_siginfo; int /*<<< orphan*/  deferred_sigact; scalar_t__ deferred_run; } ;
typedef  struct sigaction siginfo_t ;

/* Variables and functions */
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 scalar_t__ THR_IN_CRITICAL (struct pthread*) ; 
 struct usigaction* __libc_sigaction_slot (int) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_deferset ; 
 int /*<<< orphan*/  _thr_rwl_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_rwl_unlock (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  handle_signal (struct sigaction*,int,struct sigaction*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sigaction*,int) ; 

__attribute__((used)) static void
thr_sighandler(int sig, siginfo_t *info, void *_ucp)
{
	struct pthread *curthread;
	ucontext_t *ucp;
	struct sigaction act;
	struct usigaction *usa;
	int err;

	err = errno;
	curthread = _get_curthread();
	ucp = _ucp;
	usa = __libc_sigaction_slot(sig);
	_thr_rwl_rdlock(&usa->lock);
	act = usa->sigact;
	_thr_rwl_unlock(&usa->lock);
	errno = err;
	curthread->deferred_run = 0;

	/*
	 * if a thread is in critical region, for example it holds low level locks,
	 * try to defer the signal processing, however if the signal is synchronous
	 * signal, it means a bad thing has happened, this is a programming error,
	 * resuming fault point can not help anything (normally causes deadloop),
	 * so here we let user code handle it immediately.
	 */
	if (THR_IN_CRITICAL(curthread) && SIGISMEMBER(_thr_deferset, sig)) {
		memcpy(&curthread->deferred_sigact, &act, sizeof(struct sigaction));
		memcpy(&curthread->deferred_siginfo, info, sizeof(siginfo_t));
		curthread->deferred_sigmask = ucp->uc_sigmask;
		/* mask all signals, we will restore it later. */
		ucp->uc_sigmask = _thr_deferset;
		return;
	}

	handle_signal(&act, sig, info, ucp);
}