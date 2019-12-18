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
struct mem_ctl_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  edac_unregister_sysfs (struct mem_ctl_info*) ; 

void edac_mc_free(struct mem_ctl_info *mci)
{
	edac_dbg(1, "\n");

	/* If we're not yet registered with sysfs free only what was allocated
	 * in edac_mc_alloc().
	 */
	if (!device_is_registered(&mci->dev)) {
		_edac_mc_free(mci);
		return;
	}

	/* the mci instance is freed here, when the sysfs object is dropped */
	edac_unregister_sysfs(mci);
}