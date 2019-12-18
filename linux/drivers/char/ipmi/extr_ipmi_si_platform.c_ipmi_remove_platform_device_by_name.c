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
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdev_match_name ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

void ipmi_remove_platform_device_by_name(char *name)
{
	struct device *dev;

	while ((dev = bus_find_device(&platform_bus_type, NULL, name,
				      pdev_match_name))) {
		struct platform_device *pdev = to_platform_device(dev);

		platform_device_unregister(pdev);
		put_device(dev);
	}
}