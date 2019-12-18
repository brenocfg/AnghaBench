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
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _single_thread ; 
 int /*<<< orphan*/  _suspend_all_cycle ; 
 int /*<<< orphan*/  _suspend_all_lock ; 
 scalar_t__ _suspend_all_waiters ; 
 int /*<<< orphan*/  _thr_umtx_wake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
_thr_suspend_all_unlock(struct pthread *curthread)
{

	THR_LOCK_ACQUIRE(curthread, &_suspend_all_lock);
	_single_thread = NULL;
	if (_suspend_all_waiters != 0) {
		_suspend_all_cycle++;
		_thr_umtx_wake(&_suspend_all_cycle, INT_MAX, 0);
	}
	THR_LOCK_RELEASE(curthread, &_suspend_all_lock);
}