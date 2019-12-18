#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct attribute_group const** groups; int /*<<< orphan*/  parent; int /*<<< orphan*/ * type; } ;
struct mem_ctl_info {int tot_dimms; TYPE_1__ dev; struct dimm_info** dimms; int /*<<< orphan*/  mc_idx; } ;
struct dimm_info {TYPE_1__ dev; int /*<<< orphan*/  nr_pages; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct mem_ctl_info*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int edac_create_csrow_objects (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_create_debugfs_nodes (struct mem_ctl_info*) ; 
 int edac_create_dimm_object (struct mem_ctl_info*,struct dimm_info*,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_attr_type ; 
 int /*<<< orphan*/  mci_pdev ; 
 int /*<<< orphan*/  pm_runtime_forbid (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

int edac_create_sysfs_mci_device(struct mem_ctl_info *mci,
				 const struct attribute_group **groups)
{
	int i, err;

	/* get the /sys/devices/system/edac subsys reference */
	mci->dev.type = &mci_attr_type;
	device_initialize(&mci->dev);

	mci->dev.parent = mci_pdev;
	mci->dev.groups = groups;
	dev_set_name(&mci->dev, "mc%d", mci->mc_idx);
	dev_set_drvdata(&mci->dev, mci);
	pm_runtime_forbid(&mci->dev);

	err = device_add(&mci->dev);
	if (err < 0) {
		edac_dbg(1, "failure: create device %s\n", dev_name(&mci->dev));
		put_device(&mci->dev);
		return err;
	}

	edac_dbg(0, "device %s created\n", dev_name(&mci->dev));

	/*
	 * Create the dimm/rank devices
	 */
	for (i = 0; i < mci->tot_dimms; i++) {
		struct dimm_info *dimm = mci->dimms[i];
		/* Only expose populated DIMMs */
		if (!dimm->nr_pages)
			continue;

		err = edac_create_dimm_object(mci, dimm, i);
		if (err)
			goto fail_unregister_dimm;
	}

#ifdef CONFIG_EDAC_LEGACY_SYSFS
	err = edac_create_csrow_objects(mci);
	if (err < 0)
		goto fail_unregister_dimm;
#endif

	edac_create_debugfs_nodes(mci);
	return 0;

fail_unregister_dimm:
	for (i--; i >= 0; i--) {
		struct dimm_info *dimm = mci->dimms[i];
		if (!dimm->nr_pages)
			continue;

		device_unregister(&dimm->dev);
	}
	device_unregister(&mci->dev);

	return err;
}