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
struct mem_ctl_info {int tot_dimms; struct dimm_info** dimms; int /*<<< orphan*/  debugfs; } ;
struct dimm_info {scalar_t__ nr_pages; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,...) ; 
 int /*<<< orphan*/  edac_debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_delete_csrow_objects (struct mem_ctl_info*) ; 

void edac_remove_sysfs_mci_device(struct mem_ctl_info *mci)
{
	int i;

	edac_dbg(0, "\n");

#ifdef CONFIG_EDAC_DEBUG
	edac_debugfs_remove_recursive(mci->debugfs);
#endif
#ifdef CONFIG_EDAC_LEGACY_SYSFS
	edac_delete_csrow_objects(mci);
#endif

	for (i = 0; i < mci->tot_dimms; i++) {
		struct dimm_info *dimm = mci->dimms[i];
		if (dimm->nr_pages == 0)
			continue;
		edac_dbg(1, "unregistering device %s\n", dev_name(&dimm->dev));
		device_unregister(&dimm->dev);
	}
}