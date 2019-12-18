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
struct platform_driver {int /*<<< orphan*/  (* shutdown ) (struct platform_device*) ;} ;
struct platform_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct platform_driver* to_platform_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void platform_drv_shutdown(struct device *_dev)
{
	struct platform_driver *drv = to_platform_driver(_dev->driver);
	struct platform_device *dev = to_platform_device(_dev);

	if (drv->shutdown)
		drv->shutdown(dev);
}