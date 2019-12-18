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
struct device {TYPE_1__* p; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

bool kill_device(struct device *dev)
{
	/*
	 * Require the device lock and set the "dead" flag to guarantee that
	 * the update behavior is consistent with the other bitfields near
	 * it and that we cannot have an asynchronous probe routine trying
	 * to run while we are tearing out the bus/class/sysfs from
	 * underneath the device.
	 */
	lockdep_assert_held(&dev->mutex);

	if (dev->p->dead)
		return false;
	dev->p->dead = true;
	return true;
}