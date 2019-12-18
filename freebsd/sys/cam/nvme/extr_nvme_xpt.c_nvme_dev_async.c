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
typedef  scalar_t__ u_int32_t ;
struct cam_et {scalar_t__ target_id; } ;
struct cam_ed {scalar_t__ lun_id; int flags; } ;
struct cam_eb {int dummy; } ;

/* Variables and functions */
 scalar_t__ AC_LOST_DEVICE ; 
 int CAM_DEV_UNCONFIGURED ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  xpt_release_device (struct cam_ed*) ; 

__attribute__((used)) static void
nvme_dev_async(u_int32_t async_code, struct cam_eb *bus, struct cam_et *target,
	      struct cam_ed *device, void *async_arg)
{

	/*
	 * We only need to handle events for real devices.
	 */
	if (target->target_id == CAM_TARGET_WILDCARD
	 || device->lun_id == CAM_LUN_WILDCARD)
		return;

	if (async_code == AC_LOST_DEVICE &&
	    (device->flags & CAM_DEV_UNCONFIGURED) == 0) {
		device->flags |= CAM_DEV_UNCONFIGURED;
		xpt_release_device(device);
	}
}