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
struct sunxi_rsb_driver {int (* remove ) (int /*<<< orphan*/ ) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_sunxi_rsb_device (struct device*) ; 
 struct sunxi_rsb_driver* to_sunxi_rsb_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_rsb_device_remove(struct device *dev)
{
	const struct sunxi_rsb_driver *drv = to_sunxi_rsb_driver(dev->driver);

	return drv->remove(to_sunxi_rsb_device(dev));
}