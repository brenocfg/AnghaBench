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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct isp_fc {int /*<<< orphan*/  sim; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
typedef  int /*<<< orphan*/  fcportdb_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 struct isp_fc* ISP_FC_PC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP_LOGWARN ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
isp_make_here(ispsoftc_t *isp, fcportdb_t *fcp, int chan, int tgt)
{
	union ccb *ccb;
	struct isp_fc *fc = ISP_FC_PC(isp, chan);

	/*
	 * Allocate a CCB, create a wildcard path for this target and schedule a rescan.
	 */
	ccb = xpt_alloc_ccb_nowait();
	if (ccb == NULL) {
		isp_prt(isp, ISP_LOGWARN, "Chan %d unable to alloc CCB for rescan", chan);
		return;
	}
	if (xpt_create_path(&ccb->ccb_h.path, NULL, cam_sim_path(fc->sim),
	    tgt, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		isp_prt(isp, ISP_LOGWARN, "unable to create path for rescan");
		xpt_free_ccb(ccb);
		return;
	}
	xpt_rescan(ccb);
}