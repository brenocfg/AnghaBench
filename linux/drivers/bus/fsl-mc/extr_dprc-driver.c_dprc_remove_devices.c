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
struct fsl_mc_obj_desc {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; } ;
struct fsl_mc_child_objs {int child_count; struct fsl_mc_obj_desc* child_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fsl_mc_device_remove ; 
 int /*<<< orphan*/  __fsl_mc_device_remove_if_not_in_mc ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,struct fsl_mc_child_objs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dprc_remove_devices(struct fsl_mc_device *mc_bus_dev,
				struct fsl_mc_obj_desc *obj_desc_array,
				int num_child_objects_in_mc)
{
	if (num_child_objects_in_mc != 0) {
		/*
		 * Remove child objects that are in the DPRC in Linux,
		 * but not in the MC:
		 */
		struct fsl_mc_child_objs objs;

		objs.child_count = num_child_objects_in_mc;
		objs.child_array = obj_desc_array;
		device_for_each_child(&mc_bus_dev->dev, &objs,
				      __fsl_mc_device_remove_if_not_in_mc);
	} else {
		/*
		 * There are no child objects for this DPRC in the MC.
		 * So, remove all the child devices from Linux:
		 */
		device_for_each_child(&mc_bus_dev->dev, NULL,
				      __fsl_mc_device_remove);
	}
}