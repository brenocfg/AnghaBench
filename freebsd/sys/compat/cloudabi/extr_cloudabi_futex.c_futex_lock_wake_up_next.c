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
struct futex_lock {int fl_owner; int /*<<< orphan*/  fl_readers; int /*<<< orphan*/  fl_writers; } ;
typedef  int cloudabi_tid_t ;
typedef  int /*<<< orphan*/  cloudabi_lock_t ;

/* Variables and functions */
 int CLOUDABI_LOCK_KERNEL_MANAGED ; 
 int CLOUDABI_LOCK_WRLOCKED ; 
 void* LOCK_UNMANAGED ; 
 int futex_queue_count (int /*<<< orphan*/ *) ; 
 int futex_queue_tid_best (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_queue_wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  futex_queue_wake_up_best (int /*<<< orphan*/ *) ; 
 int futex_user_store (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
futex_lock_wake_up_next(struct futex_lock *fl, cloudabi_lock_t *lock)
{
	cloudabi_tid_t tid;
	int error;

	/*
	 * Determine which thread(s) to wake up. Prefer waking up
	 * writers over readers to prevent write starvation.
	 */
	if (futex_queue_count(&fl->fl_writers) > 0) {
		/* Transfer ownership to a single write-locker. */
		if (futex_queue_count(&fl->fl_writers) > 1 ||
		    futex_queue_count(&fl->fl_readers) > 0) {
			/* Lock should remain managed afterwards. */
			tid = futex_queue_tid_best(&fl->fl_writers);
			error = futex_user_store(lock,
			    tid | CLOUDABI_LOCK_WRLOCKED |
			    CLOUDABI_LOCK_KERNEL_MANAGED);
			if (error != 0)
				return (error);

			futex_queue_wake_up_best(&fl->fl_writers);
			fl->fl_owner = tid;
		} else {
			/* Lock can become unmanaged afterwards. */
			error = futex_user_store(lock,
			    futex_queue_tid_best(&fl->fl_writers) |
			    CLOUDABI_LOCK_WRLOCKED);
			if (error != 0)
				return (error);

			futex_queue_wake_up_best(&fl->fl_writers);
			fl->fl_owner = LOCK_UNMANAGED;
		}
	} else {
		/* Transfer ownership to all read-lockers (if any). */
		error = futex_user_store(lock,
		    futex_queue_count(&fl->fl_readers));
		if (error != 0)
			return (error);

		/* Wake up all threads. */
		futex_queue_wake_up_all(&fl->fl_readers);
		fl->fl_owner = LOCK_UNMANAGED;
	}
	return (0);
}