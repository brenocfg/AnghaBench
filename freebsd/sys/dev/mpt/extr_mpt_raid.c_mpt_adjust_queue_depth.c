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
typedef  union ccb {int dummy; } ccb ;
struct mpt_softc {int /*<<< orphan*/  raid_queue_depth; } ;
struct mpt_raid_volume {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
struct ccb_relsim {TYPE_1__ ccb_h; int /*<<< orphan*/  openings; int /*<<< orphan*/  release_flags; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_QFREEZE ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  RELSIM_ADJUST_OPENINGS ; 
 int /*<<< orphan*/  XPT_REL_SIMQ ; 
 int /*<<< orphan*/  mpt_vol_prt (struct mpt_softc*,struct mpt_raid_volume*,char*,scalar_t__) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,struct cam_path*,int) ; 

__attribute__((used)) static void
mpt_adjust_queue_depth(struct mpt_softc *mpt, struct mpt_raid_volume *mpt_vol,
		       struct cam_path *path)
{
	struct ccb_relsim crs;

	xpt_setup_ccb(&crs.ccb_h, path, /*priority*/5);
	crs.ccb_h.func_code = XPT_REL_SIMQ;
	crs.ccb_h.flags = CAM_DEV_QFREEZE;
	crs.release_flags = RELSIM_ADJUST_OPENINGS;
	crs.openings = mpt->raid_queue_depth;
	xpt_action((union ccb *)&crs);
	if (crs.ccb_h.status != CAM_REQ_CMP)
		mpt_vol_prt(mpt, mpt_vol, "mpt_adjust_queue_depth failed "
			    "with CAM status %#x\n", crs.ccb_h.status);
}