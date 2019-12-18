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
struct TYPE_2__ {int target_id; size_t target_lun; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int u_int ;
struct cam_sim {int dummy; } ;
struct ahc_tmode_tstate {struct ahc_tmode_lstate** enabled_luns; } ;
struct ahc_tmode_lstate {int dummy; } ;
struct ahc_softc {int features; struct ahc_tmode_tstate** enabled_targets; struct ahc_tmode_lstate* black_hole; } ;
typedef  int /*<<< orphan*/  cam_status ;

/* Variables and functions */
 size_t AHC_NUM_LUNS ; 
 int AHC_TARGETMODE ; 
 int AHC_WIDE ; 
 int /*<<< orphan*/  CAM_LUN_INVALID ; 
 size_t CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_PATH_INVALID ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CAM_TID_INVALID ; 

cam_status
ahc_find_tmode_devs(struct ahc_softc *ahc, struct cam_sim *sim, union ccb *ccb,
		    struct ahc_tmode_tstate **tstate,
		    struct ahc_tmode_lstate **lstate,
		    int notfound_failure)
{

	if ((ahc->features & AHC_TARGETMODE) == 0)
		return (CAM_REQ_INVALID);

	/*
	 * Handle the 'black hole' device that sucks up
	 * requests to unattached luns on enabled targets.
	 */
	if (ccb->ccb_h.target_id == CAM_TARGET_WILDCARD
	 && ccb->ccb_h.target_lun == CAM_LUN_WILDCARD) {
		*tstate = NULL;
		*lstate = ahc->black_hole;
	} else {
		u_int max_id;

		max_id = (ahc->features & AHC_WIDE) ? 15 : 7;
		if (ccb->ccb_h.target_id > max_id)
			return (CAM_TID_INVALID);

		if (ccb->ccb_h.target_lun >= AHC_NUM_LUNS)
			return (CAM_LUN_INVALID);

		*tstate = ahc->enabled_targets[ccb->ccb_h.target_id];
		*lstate = NULL;
		if (*tstate != NULL)
			*lstate =
			    (*tstate)->enabled_luns[ccb->ccb_h.target_lun];
	}

	if (notfound_failure != 0 && *lstate == NULL)
		return (CAM_PATH_INVALID);

	return (CAM_REQ_CMP);
}