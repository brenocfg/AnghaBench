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
struct TYPE_2__ {int /*<<< orphan*/  sx; } ;
struct ww_mutex {int /*<<< orphan*/  condvar; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_ww_lock () ; 
 int /*<<< orphan*/  linux_ww_unlock () ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
linux_ww_mutex_unlock_sub(struct ww_mutex *lock)
{
	/* protect ww_mutex ownership change */
	linux_ww_lock();
	sx_xunlock(&lock->base.sx);
	/* wakeup a lock waiter, if any */
	cv_signal(&lock->condvar);
	linux_ww_unlock();
}