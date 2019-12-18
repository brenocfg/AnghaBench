#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cam_path {TYPE_3__* device; TYPE_2__* target; TYPE_1__* bus; } ;
struct TYPE_6__ {scalar_t__ lun_id; } ;
struct TYPE_5__ {scalar_t__ target_id; } ;
struct TYPE_4__ {scalar_t__ path_id; } ;

/* Variables and functions */
 scalar_t__ CAM_BUS_WILDCARD ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 

int
xpt_path_comp(struct cam_path *path1, struct cam_path *path2)
{
	int retval = 0;

	if (path1->bus != path2->bus) {
		if (path1->bus->path_id == CAM_BUS_WILDCARD)
			retval = 1;
		else if (path2->bus->path_id == CAM_BUS_WILDCARD)
			retval = 2;
		else
			return (-1);
	}
	if (path1->target != path2->target) {
		if (path1->target->target_id == CAM_TARGET_WILDCARD) {
			if (retval == 0)
				retval = 1;
		} else if (path2->target->target_id == CAM_TARGET_WILDCARD)
			retval = 2;
		else
			return (-1);
	}
	if (path1->device != path2->device) {
		if (path1->device->lun_id == CAM_LUN_WILDCARD) {
			if (retval == 0)
				retval = 1;
		} else if (path2->device->lun_id == CAM_LUN_WILDCARD)
			retval = 2;
		else
			return (-1);
	}
	return (retval);
}