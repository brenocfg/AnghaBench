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
struct pthread {int unblock_sigcancel; scalar_t__ cancel_async; int /*<<< orphan*/  tid; scalar_t__ in_sigsuspend; scalar_t__ cancel_point; scalar_t__ no_cancel; int /*<<< orphan*/  cancel_enable; int /*<<< orphan*/  cancel_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CANCELED ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  _pthread_exit_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_send_sig (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_wake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_cancel(struct pthread *curthread, ucontext_t *ucp)
{

	if (__predict_true(!curthread->cancel_pending ||
	    !curthread->cancel_enable || curthread->no_cancel))
		return;

	/*
 	 * Otherwise, we are in defer mode, and we are at
	 * cancel point, tell kernel to not block the current
	 * thread on next cancelable system call.
	 * 
	 * There are three cases we should call thr_wake() to
	 * turn on TDP_WAKEUP or send SIGCANCEL in kernel:
	 * 1) we are going to call a cancelable system call,
	 *    non-zero cancel_point means we are already in
	 *    cancelable state, next system call is cancelable.
	 * 2) because _thr_ast() may be called by
	 *    THR_CRITICAL_LEAVE() which is used by rtld rwlock
	 *    and any libthr internal locks, when rtld rwlock
	 *    is used, it is mostly caused by an unresolved PLT.
	 *    Those routines may clear the TDP_WAKEUP flag by
	 *    invoking some system calls, in those cases, we
	 *    also should reenable the flag.
	 * 3) thread is in sigsuspend(), and the syscall insists
	 *    on getting a signal before it agrees to return.
 	 */
	if (curthread->cancel_point) {
		if (curthread->in_sigsuspend && ucp) {
			SIGADDSET(ucp->uc_sigmask, SIGCANCEL);
			curthread->unblock_sigcancel = 1;
			_thr_send_sig(curthread, SIGCANCEL);
		} else
			thr_wake(curthread->tid);
	} else if (curthread->cancel_async) {
		/*
		 * asynchronous cancellation mode, act upon
		 * immediately.
		 */
		_pthread_exit_mask(PTHREAD_CANCELED,
		    ucp? &ucp->uc_sigmask : NULL);
	}
}