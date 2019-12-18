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
struct TYPE_2__ {int /*<<< orphan*/  func_code; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int target_id_t ;
struct storvsc_softc {int /*<<< orphan*/  hs_sim; } ;
typedef  int path_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  XPT_SCAN_BUS ; 
 int /*<<< orphan*/  XPT_SCAN_TGT ; 
 int cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

__attribute__((used)) static void
hv_storvsc_rescan_target(struct storvsc_softc *sc)
{
	path_id_t pathid;
	target_id_t targetid;
	union ccb *ccb;

	pathid = cam_sim_path(sc->hs_sim);
	targetid = CAM_TARGET_WILDCARD;

	/*
	 * Allocate a CCB and schedule a rescan.
	 */
	ccb = xpt_alloc_ccb_nowait();
	if (ccb == NULL) {
		printf("unable to alloc CCB for rescan\n");
		return;
	}

	if (xpt_create_path(&ccb->ccb_h.path, NULL, pathid, targetid,
	    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		printf("unable to create path for rescan, pathid: %u,"
		    "targetid: %u\n", pathid, targetid);
		xpt_free_ccb(ccb);
		return;
	}

	if (targetid == CAM_TARGET_WILDCARD)
		ccb->ccb_h.func_code = XPT_SCAN_BUS;
	else
		ccb->ccb_h.func_code = XPT_SCAN_TGT;

	xpt_rescan(ccb);
}