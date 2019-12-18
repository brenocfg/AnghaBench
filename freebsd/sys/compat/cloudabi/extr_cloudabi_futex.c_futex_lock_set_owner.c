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
typedef  int cloudabi_lock_t ;

/* Variables and functions */
 int CLOUDABI_LOCK_KERNEL_MANAGED ; 
 int CLOUDABI_LOCK_WRLOCKED ; 
 void* LOCK_OWNER_UNKNOWN ; 
 int LOCK_UNMANAGED ; 

__attribute__((used)) static void
futex_lock_set_owner(struct futex_lock *fl, cloudabi_lock_t lock)
{

	/* Lock has no explicit owner. */
	if ((lock & ~CLOUDABI_LOCK_WRLOCKED) == 0) {
		fl->fl_owner = LOCK_OWNER_UNKNOWN;
		return;
	}
	lock &= ~(CLOUDABI_LOCK_WRLOCKED | CLOUDABI_LOCK_KERNEL_MANAGED);

	/* Don't allow userspace to silently unlock. */
	if (lock == LOCK_UNMANAGED) {
		fl->fl_owner = LOCK_OWNER_UNKNOWN;
		return;
	}
	fl->fl_owner = lock;
}