#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rtld_lock_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* lock_release ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int lockstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  mask; } ;
typedef  TYPE_2__ RtldLockState ;

/* Variables and functions */
#define  RTLD_LOCK_RLOCKED 130 
#define  RTLD_LOCK_UNLOCKED 129 
#define  RTLD_LOCK_WLOCKED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ lockinfo ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_mask_clear (int /*<<< orphan*/ ) ; 

void
lock_release(rtld_lock_t lock, RtldLockState *lockstate)
{

	if (lockstate == NULL)
		return;

	switch (lockstate->lockstate) {
	case RTLD_LOCK_UNLOCKED:
		break;
	case RTLD_LOCK_RLOCKED:
	case RTLD_LOCK_WLOCKED:
		thread_mask_clear(lock->mask);
		lockinfo.lock_release(lock->handle);
		break;
	default:
		assert(0);
	}
}