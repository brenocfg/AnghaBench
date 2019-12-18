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
struct futex_lock {scalar_t__ fl_owner; } ;
typedef  int cloudabi_lock_t ;

/* Variables and functions */
 int CLOUDABI_LOCK_KERNEL_MANAGED ; 
 int CLOUDABI_LOCK_UNLOCKED ; 
 int CLOUDABI_LOCK_WRLOCKED ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ LOCK_UNMANAGED ; 
 int /*<<< orphan*/  futex_lock_set_owner (struct futex_lock*,int) ; 
 int futex_user_cmpxchg (int*,int,int*,int) ; 

__attribute__((used)) static int
futex_lock_tryrdlock(struct futex_lock *fl, cloudabi_lock_t *address)
{
	cloudabi_lock_t old, cmp;
	int error;

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

		if ((old & CLOUDABI_LOCK_WRLOCKED) == 0) {
			/*
			 * Lock is not write-locked. Attempt to acquire
			 * it by increasing the read count.
			 */
			cmp = old;
			error = futex_user_cmpxchg(address, cmp, &old, cmp + 1);
			if (error != 0)
				return (error);
			if (old == cmp) {
				/* Success. */
				return (0);
			}
		} else {
			/* Lock is write-locked. Make it kernel-managed. */
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