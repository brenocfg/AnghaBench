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
struct thread {int /*<<< orphan*/  td_tid; } ;
struct futex_queue {int dummy; } ;
struct futex_waiter {int fw_locked; struct futex_queue fw_donated; } ;
struct futex_lock {scalar_t__ fl_owner; int /*<<< orphan*/  fl_writers; } ;
typedef  int /*<<< orphan*/  cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  cloudabi_lock_t ;
typedef  int /*<<< orphan*/  cloudabi_clockid_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LOCK_UNMANAGED ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int futex_lock_trywrlock (struct futex_lock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  futex_lock_unmanage (struct futex_lock*,int /*<<< orphan*/ *) ; 
 scalar_t__ futex_queue_count (struct futex_queue*) ; 
 int /*<<< orphan*/  futex_queue_requeue (struct futex_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int futex_queue_sleep (int /*<<< orphan*/ *,struct futex_lock*,struct futex_waiter*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  futex_queue_wake_up_donate (struct futex_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
futex_lock_wrlock(struct futex_lock *fl, struct thread *td,
    cloudabi_lock_t *lock, cloudabi_clockid_t clock_id,
    cloudabi_timestamp_t timeout, cloudabi_timestamp_t precision, bool abstime,
    struct futex_queue *donated)
{
	struct futex_waiter fw;
	int error;

	error = futex_lock_trywrlock(fl, lock, td->td_tid,
	    futex_queue_count(donated) > 0);

	if (error == 0 || error == EBUSY) {
		/* Put donated threads in queue before suspending. */
		KASSERT(futex_queue_count(donated) == 0 ||
		    fl->fl_owner != LOCK_UNMANAGED,
		    ("Lock should be managed if we are going to donate"));
		futex_queue_requeue(donated, &fl->fl_writers, UINT_MAX);
	} else {
		/*
		 * This thread cannot deal with the donated threads.
		 * Wake up the next thread and let it try it by itself.
		 */
		futex_queue_wake_up_donate(donated, UINT_MAX);
	}

	if (error == EBUSY) {
		/* Suspend execution if the lock was busy. */
		KASSERT(fl->fl_owner != LOCK_UNMANAGED,
		    ("Attempted to sleep on an unmanaged lock"));
		error = futex_queue_sleep(&fl->fl_writers, fl, &fw, td,
		    clock_id, timeout, precision, abstime);
		KASSERT((error == 0) == fw.fw_locked,
		    ("Should have locked write lock on success"));
		KASSERT(futex_queue_count(&fw.fw_donated) == 0,
		    ("Lock functions cannot receive threads"));
	}
	if (error != 0)
		futex_lock_unmanage(fl, lock);
	return (error);
}