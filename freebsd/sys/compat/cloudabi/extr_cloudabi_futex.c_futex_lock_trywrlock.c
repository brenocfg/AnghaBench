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
struct futex_lock {int fl_owner; } ;
typedef  int cloudabi_tid_t ;
typedef  int cloudabi_lock_t ;

/* Variables and functions */
 int CLOUDABI_LOCK_KERNEL_MANAGED ; 
 int CLOUDABI_LOCK_UNLOCKED ; 
 int CLOUDABI_LOCK_WRLOCKED ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EINVAL ; 
 int LOCK_UNMANAGED ; 
 int /*<<< orphan*/  futex_lock_set_owner (struct futex_lock*,int) ; 
 int futex_user_cmpxchg (int*,int,int*,int) ; 

__attribute__((used)) static int
futex_lock_trywrlock(struct futex_lock *fl, cloudabi_lock_t *address,
    cloudabi_tid_t tid, bool force_kernel_managed)
{
	cloudabi_lock_t old, new, cmp;
	int error;

	if (fl->fl_owner == tid) {
		/* Attempted to acquire lock recursively. */
		return (EDEADLK);
	}
	if (fl->fl_owner != LOCK_UNMANAGED) {
		/* Lock is already acquired. */
		return (EBUSY);
	}

	old = CLOUDABI_LOCK_UNLOCKED;
	for (;;) {
		if ((old & CLOUDABI_LOCK_KERNEL_MANAGED) != 0) {
			/*
			 * Userspace lock is kernel-managed, even though
			 * the kernel disagrees.
			 */
			return (EINVAL);
		}
		if (old == (tid | CLOUDABI_LOCK_WRLOCKED)) {
			/* Attempted to acquire lock recursively. */
			return (EDEADLK);
		}

		if (old == CLOUDABI_LOCK_UNLOCKED) {
			/* Lock is unlocked. Attempt to acquire it. */
			new = tid | CLOUDABI_LOCK_WRLOCKED;
			if (force_kernel_managed)
				new |= CLOUDABI_LOCK_KERNEL_MANAGED;
			error = futex_user_cmpxchg(address,
			    CLOUDABI_LOCK_UNLOCKED, &old, new);
			if (error != 0)
				return (error);
			if (old == CLOUDABI_LOCK_UNLOCKED) {
				/* Success. */
				if (force_kernel_managed)
					fl->fl_owner = tid;
				return (0);
			}
		} else {
			/* Lock is still locked. Make it kernel-managed. */
			cmp = old;
			error = futex_user_cmpxchg(address, cmp, &old,
			    cmp | CLOUDABI_LOCK_KERNEL_MANAGED);
			if (error != 0)
				return (error);
			if (old == cmp) {
				/* Success. */
				futex_lock_set_owner(fl, cmp);
				return (EBUSY);
			}
		}
	}
}