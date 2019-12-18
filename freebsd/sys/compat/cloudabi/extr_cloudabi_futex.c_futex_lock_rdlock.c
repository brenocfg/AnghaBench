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
struct thread {int dummy; } ;
struct futex_waiter {int fw_locked; int /*<<< orphan*/  fw_donated; } ;
struct futex_lock {scalar_t__ fl_owner; int /*<<< orphan*/  fl_readers; } ;
typedef  int /*<<< orphan*/  cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  cloudabi_lock_t ;
typedef  int /*<<< orphan*/  cloudabi_clockid_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LOCK_UNMANAGED ; 
 int futex_lock_tryrdlock (struct futex_lock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_lock_unmanage (struct futex_lock*,int /*<<< orphan*/ *) ; 
 scalar_t__ futex_queue_count (int /*<<< orphan*/ *) ; 
 int futex_queue_sleep (int /*<<< orphan*/ *,struct futex_lock*,struct futex_waiter*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
futex_lock_rdlock(struct futex_lock *fl, struct thread *td,
    cloudabi_lock_t *lock, cloudabi_clockid_t clock_id,
    cloudabi_timestamp_t timeout, cloudabi_timestamp_t precision, bool abstime)
{
	struct futex_waiter fw;
	int error;

	error = futex_lock_tryrdlock(fl, lock);
	if (error == EBUSY) {
		/* Suspend execution. */
		KASSERT(fl->fl_owner != LOCK_UNMANAGED,
		    ("Attempted to sleep on an unmanaged lock"));
		error = futex_queue_sleep(&fl->fl_readers, fl, &fw, td,
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