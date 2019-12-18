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
struct futex_lock {scalar_t__ fl_owner; int /*<<< orphan*/  fl_writers; } ;
struct futex_condvar {int /*<<< orphan*/  fc_waiters; struct futex_lock* fc_lock; } ;
struct cloudabi_sys_condvar_signal_args {scalar_t__ nwaiters; int /*<<< orphan*/  condvar; int /*<<< orphan*/  scope; } ;
typedef  scalar_t__ cloudabi_nthreads_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ LOCK_UNMANAGED ; 
 int futex_condvar_lookup (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct futex_condvar**) ; 
 int /*<<< orphan*/  futex_condvar_release (struct futex_condvar*) ; 
 int futex_condvar_unmanage (struct futex_condvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_queue_requeue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  futex_queue_wake_up_donate (int /*<<< orphan*/ *,scalar_t__) ; 

int
cloudabi_sys_condvar_signal(struct thread *td,
    struct cloudabi_sys_condvar_signal_args *uap)
{
	struct futex_condvar *fc;
	struct futex_lock *fl;
	cloudabi_nthreads_t nwaiters;
	int error;

	nwaiters = uap->nwaiters;
	if (nwaiters == 0) {
		/* No threads to wake up. */
		return (0);
	}

	/* Look up futex object. */
	error = futex_condvar_lookup(td, uap->condvar, uap->scope, &fc);
	if (error != 0) {
		/* Race condition: condition variable with no waiters. */
		return (error == ENOENT ? 0 : error);
	}
	fl = fc->fc_lock;

	if (fl->fl_owner == LOCK_UNMANAGED) {
		/*
		 * The lock is currently not managed by the kernel,
		 * meaning we must attempt to acquire the userspace lock
		 * first. We cannot requeue threads to an unmanaged lock,
		 * as these threads will then never be scheduled.
		 *
		 * Unfortunately, the memory address of the lock is
		 * unknown from this context, meaning that we cannot
		 * acquire the lock on behalf of the first thread to be
		 * scheduled. The lock may even not be mapped within the
		 * address space of the current thread.
		 *
		 * To solve this, wake up a single waiter that will
		 * attempt to acquire the lock. Donate all of the other
		 * waiters that need to be woken up to this waiter, so
		 * it can requeue them after acquiring the lock.
		 */
		futex_queue_wake_up_donate(&fc->fc_waiters, nwaiters - 1);
	} else {
		/*
		 * Lock is already managed by the kernel. This makes it
		 * easy, as we can requeue the threads from the
		 * condition variable directly to the associated lock.
		 */
		futex_queue_requeue(&fc->fc_waiters, &fl->fl_writers, nwaiters);
	}

	/* Clear userspace condition variable if all waiters are gone. */
	error = futex_condvar_unmanage(fc, uap->condvar);
	futex_condvar_release(fc);
	return (error);
}