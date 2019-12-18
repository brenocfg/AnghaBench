#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int lo_flags; } ;
struct rmlock {int /*<<< orphan*/  rm_lock_mtx; int /*<<< orphan*/  rm_lock_sx; TYPE_1__ lock_object; } ;

/* Variables and functions */
 int LO_SLEEPABLE ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
_rm_wunlock(struct rmlock *rm)
{

	if (rm->lock_object.lo_flags & LO_SLEEPABLE)
		sx_xunlock(&rm->rm_lock_sx);
	else
		mtx_unlock(&rm->rm_lock_mtx);
}