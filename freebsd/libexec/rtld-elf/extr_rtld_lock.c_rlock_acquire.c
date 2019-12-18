#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rtld_lock_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* rlock_acquire ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  lockstate; } ;
struct TYPE_6__ {int mask; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ RtldLockState ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_LOCK_RLOCKED ; 
 int /*<<< orphan*/  RTLD_LOCK_UNLOCKED ; 
 int /*<<< orphan*/  dbg (char*) ; 
 TYPE_5__ lockinfo ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int thread_mask_set (int) ; 

void
rlock_acquire(rtld_lock_t lock, RtldLockState *lockstate)
{

	if (lockstate == NULL)
		return;

	if (thread_mask_set(lock->mask) & lock->mask) {
		dbg("rlock_acquire: recursed");
		lockstate->lockstate = RTLD_LOCK_UNLOCKED;
		return;
	}
	lockinfo.rlock_acquire(lock->handle);
	lockstate->lockstate = RTLD_LOCK_RLOCKED;
}