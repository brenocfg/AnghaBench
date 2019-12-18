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
struct kobject {int dummy; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  owner; int /*<<< orphan*/  name; int /*<<< orphan*/  kobj; struct bus_type* edac_subsys; } ;
struct bus_type {TYPE_1__* dev_root; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 struct bus_type* edac_get_sysfs_subsys () ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_device_ctrl ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int edac_device_register_sysfs_main_kobj(struct edac_device_ctl_info *edac_dev)
{
	struct bus_type *edac_subsys;
	int err;

	edac_dbg(1, "\n");

	/* get the /sys/devices/system/edac reference */
	edac_subsys = edac_get_sysfs_subsys();

	/* Point to the 'edac_subsys' this instance 'reports' to */
	edac_dev->edac_subsys = edac_subsys;

	/* Init the devices's kobject */
	memset(&edac_dev->kobj, 0, sizeof(struct kobject));

	/* Record which module 'owns' this control structure
	 * and bump the ref count of the module
	 */
	edac_dev->owner = THIS_MODULE;

	if (!try_module_get(edac_dev->owner)) {
		err = -ENODEV;
		goto err_out;
	}

	/* register */
	err = kobject_init_and_add(&edac_dev->kobj, &ktype_device_ctrl,
				   &edac_subsys->dev_root->kobj,
				   "%s", edac_dev->name);
	if (err) {
		edac_dbg(1, "Failed to register '.../edac/%s'\n",
			 edac_dev->name);
		goto err_kobj_reg;
	}
	kobject_uevent(&edac_dev->kobj, KOBJ_ADD);

	/* At this point, to 'free' the control struct,
	 * edac_device_unregister_sysfs_main_kobj() must be used
	 */

	edac_dbg(4, "Registered '.../edac/%s' kobject\n", edac_dev->name);

	return 0;

	/* Error exit stack */
err_kobj_reg:
	module_put(edac_dev->owner);

err_out:
	return err;
}