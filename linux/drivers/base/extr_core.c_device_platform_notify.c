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
struct device {int dummy; } ;
typedef  enum kobject_action { ____Placeholder_kobject_action } kobject_action ;

/* Variables and functions */
 int KOBJ_ADD ; 
 int KOBJ_REMOVE ; 
 int acpi_platform_notify (struct device*,int) ; 
 int /*<<< orphan*/  platform_notify (struct device*) ; 
 int /*<<< orphan*/  platform_notify_remove (struct device*) ; 
 int software_node_notify (struct device*,int) ; 

__attribute__((used)) static int
device_platform_notify(struct device *dev, enum kobject_action action)
{
	int ret;

	ret = acpi_platform_notify(dev, action);
	if (ret)
		return ret;

	ret = software_node_notify(dev, action);
	if (ret)
		return ret;

	if (platform_notify && action == KOBJ_ADD)
		platform_notify(dev);
	else if (platform_notify_remove && action == KOBJ_REMOVE)
		platform_notify_remove(dev);
	return 0;
}