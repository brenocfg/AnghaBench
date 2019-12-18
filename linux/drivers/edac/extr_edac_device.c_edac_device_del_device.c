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
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  dev_idx; int /*<<< orphan*/  op_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OP_OFFLINE ; 
 int /*<<< orphan*/  del_edac_device_from_global_list (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  device_ctls_mutex ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_dev_name (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  edac_device_remove_sysfs (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  edac_device_workq_teardown (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct edac_device_ctl_info* find_edac_device_by_dev (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct edac_device_ctl_info *edac_device_del_device(struct device *dev)
{
	struct edac_device_ctl_info *edac_dev;

	edac_dbg(0, "\n");

	mutex_lock(&device_ctls_mutex);

	/* Find the structure on the list, if not there, then leave */
	edac_dev = find_edac_device_by_dev(dev);
	if (edac_dev == NULL) {
		mutex_unlock(&device_ctls_mutex);
		return NULL;
	}

	/* mark this instance as OFFLINE */
	edac_dev->op_state = OP_OFFLINE;

	/* deregister from global list */
	del_edac_device_from_global_list(edac_dev);

	mutex_unlock(&device_ctls_mutex);

	/* clear workq processing on this instance */
	edac_device_workq_teardown(edac_dev);

	/* Tear down the sysfs entries for this instance */
	edac_device_remove_sysfs(edac_dev);

	edac_printk(KERN_INFO, EDAC_MC,
		"Removed device %d for %s %s: DEV %s\n",
		edac_dev->dev_idx,
		edac_dev->mod_name, edac_dev->ctl_name, edac_dev_name(edac_dev));

	return edac_dev;
}