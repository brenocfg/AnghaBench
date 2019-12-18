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
struct kobject {int dummy; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  owner; int /*<<< orphan*/  dev_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct edac_device_ctl_info* to_edacdev (struct kobject*) ; 

__attribute__((used)) static void edac_device_ctrl_master_release(struct kobject *kobj)
{
	struct edac_device_ctl_info *edac_dev = to_edacdev(kobj);

	edac_dbg(4, "control index=%d\n", edac_dev->dev_idx);

	/* decrement the EDAC CORE module ref count */
	module_put(edac_dev->owner);

	/* free the control struct containing the 'main' kobj
	 * passed in to this routine
	 */
	kfree(edac_dev);
}