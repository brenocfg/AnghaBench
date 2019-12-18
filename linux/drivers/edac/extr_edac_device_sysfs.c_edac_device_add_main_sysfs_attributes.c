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
 int sysfs_create_file (int /*<<< orphan*/ *,struct attribute*) ; 

__attribute__((used)) static int edac_device_add_main_sysfs_attributes(
			struct edac_device_ctl_info *edac_dev)
{
	struct edac_dev_sysfs_attribute *sysfs_attrib;
	int err = 0;

	sysfs_attrib = edac_dev->sysfs_attributes;
	if (sysfs_attrib) {
		/* iterate over the array and create an attribute for each
		 * entry in the list
		 */
		while (sysfs_attrib->attr.name != NULL) {
			err = sysfs_create_file(&edac_dev->kobj,
				(struct attribute*) sysfs_attrib);
			if (err)
				goto err_out;

			sysfs_attrib++;
		}
	}

err_out:
	return err;
}