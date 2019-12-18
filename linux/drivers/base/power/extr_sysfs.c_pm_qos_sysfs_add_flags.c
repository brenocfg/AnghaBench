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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_qos_flags_attr_group ; 
 int sysfs_merge_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pm_qos_sysfs_add_flags(struct device *dev)
{
	return sysfs_merge_group(&dev->kobj, &pm_qos_flags_attr_group);
}