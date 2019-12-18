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
struct sunxi_rsb_device {int dummy; } ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  sunxi_rsb_bus ; 
 int /*<<< orphan*/  sunxi_rsb_device_unregister (struct sunxi_rsb_device*) ; 
 struct sunxi_rsb_device* to_sunxi_rsb_device (struct device*) ; 

__attribute__((used)) static int sunxi_rsb_remove_devices(struct device *dev, void *data)
{
	struct sunxi_rsb_device *rdev = to_sunxi_rsb_device(dev);

	if (dev->bus == &sunxi_rsb_bus)
		sunxi_rsb_device_unregister(rdev);

	return 0;
}