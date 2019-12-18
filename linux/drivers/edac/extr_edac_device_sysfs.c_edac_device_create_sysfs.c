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
struct edac_device_ctl_info {int dev_idx; struct kobject kobj; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_DEVICE_SYMLINK ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 int edac_device_add_main_sysfs_attributes (struct edac_device_ctl_info*) ; 
 int edac_device_create_instances (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  edac_device_remove_main_sysfs_attributes (struct edac_device_ctl_info*) ; 
 int sysfs_create_link (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_link (struct kobject*,int /*<<< orphan*/ ) ; 

int edac_device_create_sysfs(struct edac_device_ctl_info *edac_dev)
{
	int err;
	struct kobject *edac_kobj = &edac_dev->kobj;

	edac_dbg(0, "idx=%d\n", edac_dev->dev_idx);

	/*  go create any main attributes callers wants */
	err = edac_device_add_main_sysfs_attributes(edac_dev);
	if (err) {
		edac_dbg(0, "failed to add sysfs attribs\n");
		goto err_out;
	}

	/* create a symlink from the edac device
	 * to the platform 'device' being used for this
	 */
	err = sysfs_create_link(edac_kobj,
				&edac_dev->dev->kobj, EDAC_DEVICE_SYMLINK);
	if (err) {
		edac_dbg(0, "sysfs_create_link() returned err= %d\n", err);
		goto err_remove_main_attribs;
	}

	/* Create the first level instance directories
	 * In turn, the nested blocks beneath the instances will
	 * be registered as well
	 */
	err = edac_device_create_instances(edac_dev);
	if (err) {
		edac_dbg(0, "edac_device_create_instances() returned err= %d\n",
			 err);
		goto err_remove_link;
	}


	edac_dbg(4, "create-instances done, idx=%d\n", edac_dev->dev_idx);

	return 0;

	/* Error unwind stack */
err_remove_link:
	/* remove the sym link */
	sysfs_remove_link(&edac_dev->kobj, EDAC_DEVICE_SYMLINK);

err_remove_main_attribs:
	edac_device_remove_main_sysfs_attributes(edac_dev);

err_out:
	return err;
}