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
struct device {int dummy; } ;
struct coreboot_driver {scalar_t__ tag; } ;
struct TYPE_2__ {scalar_t__ tag; } ;
struct coreboot_device {TYPE_1__ entry; } ;

/* Variables and functions */
 struct coreboot_device* CB_DEV (struct device*) ; 
 struct coreboot_driver* CB_DRV (struct device_driver*) ; 

__attribute__((used)) static int coreboot_bus_match(struct device *dev, struct device_driver *drv)
{
	struct coreboot_device *device = CB_DEV(dev);
	struct coreboot_driver *driver = CB_DRV(drv);

	return device->entry.tag == driver->tag;
}