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
typedef  int u32 ;
struct fsl_mc_obj_desc {int state; } ;
struct TYPE_2__ {int state; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; TYPE_1__ obj_desc; } ;

/* Variables and functions */
 int FSL_MC_OBJ_STATE_PLUGGED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_plugged_state_change(struct fsl_mc_device *mc_dev,
				       struct fsl_mc_obj_desc *obj_desc)
{
	int error;
	u32 plugged_flag_at_mc =
			obj_desc->state & FSL_MC_OBJ_STATE_PLUGGED;

	if (plugged_flag_at_mc !=
	    (mc_dev->obj_desc.state & FSL_MC_OBJ_STATE_PLUGGED)) {
		if (plugged_flag_at_mc) {
			mc_dev->obj_desc.state |= FSL_MC_OBJ_STATE_PLUGGED;
			error = device_attach(&mc_dev->dev);
			if (error < 0) {
				dev_err(&mc_dev->dev,
					"device_attach() failed: %d\n",
					error);
			}
		} else {
			mc_dev->obj_desc.state &= ~FSL_MC_OBJ_STATE_PLUGGED;
			device_release_driver(&mc_dev->dev);
		}
	}
}