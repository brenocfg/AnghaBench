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
struct fsl_mc_driver {struct fsl_mc_device_id* match_id_table; } ;
struct fsl_mc_device_id {int vendor; int /*<<< orphan*/  obj_type; } ;
struct TYPE_2__ {int state; int vendor; int /*<<< orphan*/  type; } ;
struct fsl_mc_device {TYPE_1__ obj_desc; int /*<<< orphan*/  dev; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int FSL_MC_OBJ_STATE_PLUGGED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  fsl_mc_is_root_dprc (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 
 struct fsl_mc_driver* to_fsl_mc_driver (struct device_driver*) ; 

__attribute__((used)) static int fsl_mc_bus_match(struct device *dev, struct device_driver *drv)
{
	const struct fsl_mc_device_id *id;
	struct fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	struct fsl_mc_driver *mc_drv = to_fsl_mc_driver(drv);
	bool found = false;

	if (!mc_drv->match_id_table)
		goto out;

	/*
	 * If the object is not 'plugged' don't match.
	 * Only exception is the root DPRC, which is a special case.
	 */
	if ((mc_dev->obj_desc.state & FSL_MC_OBJ_STATE_PLUGGED) == 0 &&
	    !fsl_mc_is_root_dprc(&mc_dev->dev))
		goto out;

	/*
	 * Traverse the match_id table of the given driver, trying to find
	 * a matching for the given device.
	 */
	for (id = mc_drv->match_id_table; id->vendor != 0x0; id++) {
		if (id->vendor == mc_dev->obj_desc.vendor &&
		    strcmp(id->obj_type, mc_dev->obj_desc.type) == 0) {
			found = true;

			break;
		}
	}

out:
	dev_dbg(dev, "%smatched\n", found ? "" : "not ");
	return found;
}