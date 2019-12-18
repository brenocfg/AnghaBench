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
struct edac_device_ctl_info {int /*<<< orphan*/  kobj; struct edac_dev_sysfs_attribute* sysfs_attributes; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
struct edac_dev_sysfs_attribute {TYPE_1__ attr; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,struct attribute*) ; 

__attribute__((used)) static void edac_device_remove_main_sysfs_attributes(
			struct edac_device_ctl_info *edac_dev)
{
	struct edac_dev_sysfs_attribute *sysfs_attrib;

	/* if there are main attributes, defined, remove them. First,
	 * point to the start of the array and iterate over it
	 * removing each attribute listed from this device's instance's kobject
	 */
	sysfs_attrib = edac_dev->sysfs_attributes;
	if (sysfs_attrib) {
		while (sysfs_attrib->attr.name != NULL) {
			sysfs_remove_file(&edac_dev->kobj,
					(struct attribute *) sysfs_attrib);
			sysfs_attrib++;
		}
	}
}