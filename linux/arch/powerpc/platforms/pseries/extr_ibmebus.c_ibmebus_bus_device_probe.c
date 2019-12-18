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
struct platform_driver {int (* probe ) (struct platform_device*) ;} ;
struct platform_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  of_dev_get (struct platform_device*) ; 
 int /*<<< orphan*/  of_dev_put (struct platform_device*) ; 
 scalar_t__ of_driver_match_device (struct device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct platform_driver* to_platform_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmebus_bus_device_probe(struct device *dev)
{
	int error = -ENODEV;
	struct platform_driver *drv;
	struct platform_device *of_dev;

	drv = to_platform_driver(dev->driver);
	of_dev = to_platform_device(dev);

	if (!drv->probe)
		return error;

	of_dev_get(of_dev);

	if (of_driver_match_device(dev, dev->driver))
		error = drv->probe(of_dev);
	if (error)
		of_dev_put(of_dev);

	return error;
}