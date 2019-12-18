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
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 struct pthread* _single_thread ; 
 int _suspend_all_cycle ; 
 int /*<<< orphan*/  _suspend_all_lock ; 
 int /*<<< orphan*/  _suspend_all_waiters ; 
 int /*<<< orphan*/  _thr_umtx_wait_uint (int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_thr_suspend_all_lock(struct pthread *curthread)
{
	int old;

	THR_LOCK_ACQUIRE(curthread, &_suspend_all_lock);
	while (_single_thread != NULL) {
		old = _suspend_all_cycle;
		_suspend_all_waiters++;
		THR_LOCK_RELEASE(curthread, &_suspend_all_lock);
		_thr_umtx_wait_uint(&_suspend_all_cycle, old, NULL, 0);
		THR_LOCK_ACQUIRE(curthread, &_suspend_all_lock);
		_suspend_all_waiters--;
	}
	_single_thread = curthread;
	THR_LOCK_RELEASE(curthread, &_suspend_all_lock);
}