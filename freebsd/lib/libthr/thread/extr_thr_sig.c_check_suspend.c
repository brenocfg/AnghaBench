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
typedef  scalar_t__ uint32_t ;
struct pthread {int flags; scalar_t__ state; int /*<<< orphan*/  critical_count; int /*<<< orphan*/  lock; scalar_t__ cycle; scalar_t__ force_exit; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ PS_DEAD ; 
 int THR_FLAGS_NEED_SUSPEND ; 
 int THR_FLAGS_SUSPENDED ; 
 int /*<<< orphan*/  THR_UMUTEX_LOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_UMUTEX_UNLOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 scalar_t__ __predict_true (int) ; 
 struct pthread* _single_thread ; 
 int /*<<< orphan*/  _thr_signal_block (struct pthread*) ; 
 int /*<<< orphan*/  _thr_signal_unblock (struct pthread*) ; 
 int /*<<< orphan*/  _thr_umtx_wait_uint (scalar_t__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_umtx_wake (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_suspend(struct pthread *curthread)
{
	uint32_t cycle;

	if (__predict_true((curthread->flags &
		(THR_FLAGS_NEED_SUSPEND | THR_FLAGS_SUSPENDED))
		!= THR_FLAGS_NEED_SUSPEND))
		return;
	if (curthread == _single_thread)
		return;
	if (curthread->force_exit)
		return;

	/* 
	 * Blocks SIGCANCEL which other threads must send.
	 */
	_thr_signal_block(curthread);

	/*
	 * Increase critical_count, here we don't use THR_LOCK/UNLOCK
	 * because we are leaf code, we don't want to recursively call
	 * ourself.
	 */
	curthread->critical_count++;
	THR_UMUTEX_LOCK(curthread, &(curthread)->lock);
	while ((curthread->flags & THR_FLAGS_NEED_SUSPEND) != 0) {
		curthread->cycle++;
		cycle = curthread->cycle;

		/* Wake the thread suspending us. */
		_thr_umtx_wake(&curthread->cycle, INT_MAX, 0);

		/*
		 * if we are from pthread_exit, we don't want to
		 * suspend, just go and die.
		 */
		if (curthread->state == PS_DEAD)
			break;
		curthread->flags |= THR_FLAGS_SUSPENDED;
		THR_UMUTEX_UNLOCK(curthread, &(curthread)->lock);
		_thr_umtx_wait_uint(&curthread->cycle, cycle, NULL, 0);
		THR_UMUTEX_LOCK(curthread, &(curthread)->lock);
	}
	THR_UMUTEX_UNLOCK(curthread, &(curthread)->lock);
	curthread->critical_count--;

	_thr_signal_unblock(curthread);
}