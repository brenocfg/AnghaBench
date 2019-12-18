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
struct ttm_lock {scalar_t__ rw; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_VT_LOCK ; 
 int /*<<< orphan*/  TTM_VT_LOCK_PENDING ; 

__attribute__((used)) static bool __ttm_vt_lock(struct ttm_lock *lock)
{
	bool locked = false;

	if (lock->rw == 0) {
		lock->flags &= ~TTM_VT_LOCK_PENDING;
		lock->flags |= TTM_VT_LOCK;
		locked = true;
	} else {
		lock->flags |= TTM_VT_LOCK_PENDING;
	}
	return locked;
}