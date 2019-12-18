#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cam_path {struct cam_ed* device; TYPE_2__* target; TYPE_1__* bus; } ;
struct cam_ed {scalar_t__ lun_id; TYPE_2__* target; } ;
struct TYPE_4__ {scalar_t__ target_id; TYPE_1__* bus; } ;
struct TYPE_3__ {scalar_t__ path_id; } ;

/* Variables and functions */
 scalar_t__ CAM_BUS_WILDCARD ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 

int
xpt_path_comp_dev(struct cam_path *path, struct cam_ed *dev)
{
	int retval = 0;

	if (path->bus != dev->target->bus) {
		if (path->bus->path_id == CAM_BUS_WILDCARD)
			retval = 1;
		else if (dev->target->bus->path_id == CAM_BUS_WILDCARD)
			retval = 2;
		else
			return (-1);
	}
	if (path->target != dev->target) {
		if (path->target->target_id == CAM_TARGET_WILDCARD) {
			if (retval == 0)
				retval = 1;
		} else if (dev->target->target_id == CAM_TARGET_WILDCARD)
			retval = 2;
		else
			return (-1);
	}
	if (path->device != dev) {
		if (path->device->lun_id == CAM_LUN_WILDCARD) {
			if (retval == 0)
				retval = 1;
		} else if (dev->lun_id == CAM_LUN_WILDCARD)
			retval = 2;
		else
			return (-1);
	}
	return (retval);
}