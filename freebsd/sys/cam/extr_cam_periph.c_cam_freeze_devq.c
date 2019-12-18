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
typedef  union ccb {int dummy; } ccb ;
struct ccb_hdr {int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_DEV_QFREEZE ; 
 int /*<<< orphan*/  XPT_NOOP ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (struct ccb_hdr*,struct cam_path*,int) ; 

void
cam_freeze_devq(struct cam_path *path)
{
	struct ccb_hdr ccb_h;

	CAM_DEBUG(path, CAM_DEBUG_TRACE, ("cam_freeze_devq\n"));
	xpt_setup_ccb(&ccb_h, path, /*priority*/1);
	ccb_h.func_code = XPT_NOOP;
	ccb_h.flags = CAM_DEV_QFREEZE;
	xpt_action((union ccb *)&ccb_h);
}