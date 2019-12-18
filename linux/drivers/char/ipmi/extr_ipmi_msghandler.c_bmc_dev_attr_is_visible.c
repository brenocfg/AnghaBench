#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct ipmi_device_id {scalar_t__ aux_firmware_revision_set; } ;
struct device {int dummy; } ;
struct bmc_device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {struct attribute attr; } ;
struct TYPE_3__ {struct attribute attr; } ;

/* Variables and functions */
 int bmc_get_device_id (int /*<<< orphan*/ *,struct bmc_device*,struct ipmi_device_id*,int*,int /*<<< orphan*/ *) ; 
 TYPE_2__ dev_attr_aux_firmware_revision ; 
 TYPE_1__ dev_attr_guid ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static umode_t bmc_dev_attr_is_visible(struct kobject *kobj,
				       struct attribute *attr, int idx)
{
	struct device *dev = kobj_to_dev(kobj);
	struct bmc_device *bmc = to_bmc_device(dev);
	umode_t mode = attr->mode;
	int rv;

	if (attr == &dev_attr_aux_firmware_revision.attr) {
		struct ipmi_device_id id;

		rv = bmc_get_device_id(NULL, bmc, &id, NULL, NULL);
		return (!rv && id.aux_firmware_revision_set) ? mode : 0;
	}
	if (attr == &dev_attr_guid.attr) {
		bool guid_set;

		rv = bmc_get_device_id(NULL, bmc, NULL, &guid_set, NULL);
		return (!rv && guid_set) ? mode : 0;
	}
	return mode;
}