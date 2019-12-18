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
struct device_driver {int dummy; } ;
struct device {struct device_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  __device_driver_lock (struct device*,struct device*) ; 
 int /*<<< orphan*/  __device_driver_unlock (struct device*,struct device*) ; 
 int /*<<< orphan*/  __device_release_driver (struct device*,struct device*) ; 

void device_release_driver_internal(struct device *dev,
				    struct device_driver *drv,
				    struct device *parent)
{
	__device_driver_lock(dev, parent);

	if (!drv || drv == dev->driver)
		__device_release_driver(dev, parent);

	__device_driver_unlock(dev, parent);
}