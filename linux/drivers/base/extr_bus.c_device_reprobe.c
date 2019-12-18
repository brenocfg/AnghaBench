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
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int bus_rescan_devices_helper (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_driver_detach (struct device*) ; 

int device_reprobe(struct device *dev)
{
	if (dev->driver)
		device_driver_detach(dev);
	return bus_rescan_devices_helper(dev, NULL);
}