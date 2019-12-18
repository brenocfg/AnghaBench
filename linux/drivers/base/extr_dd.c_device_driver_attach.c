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
struct device_driver {int dummy; } ;
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/  driver; TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  __device_driver_lock (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __device_driver_unlock (struct device*,int /*<<< orphan*/ ) ; 
 int driver_probe_device (struct device_driver*,struct device*) ; 

int device_driver_attach(struct device_driver *drv, struct device *dev)
{
	int ret = 0;

	__device_driver_lock(dev, dev->parent);

	/*
	 * If device has been removed or someone has already successfully
	 * bound a driver before us just skip the driver probe call.
	 */
	if (!dev->p->dead && !dev->driver)
		ret = driver_probe_device(drv, dev);

	__device_driver_unlock(dev, dev->parent);

	return ret;
}