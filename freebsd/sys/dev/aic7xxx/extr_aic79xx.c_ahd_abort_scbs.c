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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct scb {int flags; } ;
struct ahd_softc {int /*<<< orphan*/  flags; int /*<<< orphan*/  pending_scbs; } ;
typedef  int /*<<< orphan*/  role_t ;
typedef  scalar_t__ cam_status ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int AHD_NUM_LUNS_NONPKT ; 
 int /*<<< orphan*/  AHD_UPDATE_PEND_CMDS ; 
 int BUILD_TCL_RAW (int,char,int) ; 
 int CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_REQ_INPROG ; 
 int CAM_TARGET_WILDCARD ; 
 struct scb* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct scb* LIST_NEXT (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROLE_TARGET ; 
 int SCB_ACTIVE ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SEARCH_COMPLETE ; 
 int /*<<< orphan*/  ahd_done (struct ahd_softc*,struct scb*) ; 
 int ahd_find_busy_tcl (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_flush_qoutfifo (struct ahd_softc*) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,int) ; 
 scalar_t__ ahd_match_scb (struct ahd_softc*,struct scb*,int,char,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_platform_abort_scbs (struct ahd_softc*,int,char,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int ahd_search_qinfifo (struct ahd_softc*,int,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unbusy_tcl (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  aic_freeze_scb (struct scb*) ; 
 scalar_t__ aic_get_transaction_status (struct scb*) ; 
 int /*<<< orphan*/  aic_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pending_links ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ahd_abort_scbs(struct ahd_softc *ahd, int target, char channel,
	       int lun, u_int tag, role_t role, uint32_t status)
{
	struct		scb *scbp;
	struct		scb *scbp_next;
	u_int		i, j;
	u_int		maxtarget;
	u_int		minlun;
	u_int		maxlun;
	int		found;
	ahd_mode_state	saved_modes;

	/* restore this when we're done */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	found = ahd_search_qinfifo(ahd, target, channel, lun, SCB_LIST_NULL,
				   role, CAM_REQUEUE_REQ, SEARCH_COMPLETE);

	/*
	 * Clean out the busy target table for any untagged commands.
	 */
	i = 0;
	maxtarget = 16;
	if (target != CAM_TARGET_WILDCARD) {
		i = target;
		if (channel == 'B')
			i += 8;
		maxtarget = i + 1;
	}

	if (lun == CAM_LUN_WILDCARD) {
		minlun = 0;
		maxlun = AHD_NUM_LUNS_NONPKT;
	} else if (lun >= AHD_NUM_LUNS_NONPKT) {
		minlun = maxlun = 0;
	} else {
		minlun = lun;
		maxlun = lun + 1;
	}

	if (role != ROLE_TARGET) {
		for (;i < maxtarget; i++) {
			for (j = minlun;j < maxlun; j++) {
				u_int scbid;
				u_int tcl;

				tcl = BUILD_TCL_RAW(i, 'A', j);
				scbid = ahd_find_busy_tcl(ahd, tcl);
				scbp = ahd_lookup_scb(ahd, scbid);
				if (scbp == NULL
				 || ahd_match_scb(ahd, scbp, target, channel,
						  lun, tag, role) == 0)
					continue;
				ahd_unbusy_tcl(ahd, BUILD_TCL_RAW(i, 'A', j));
			}
		}
	}

	/*
	 * Don't abort commands that have already completed,
	 * but haven't quite made it up to the host yet.
	 */
	ahd_flush_qoutfifo(ahd);

	/*
	 * Go through the pending CCB list and look for
	 * commands for this target that are still active.
	 * These are other tagged commands that were
	 * disconnected when the reset occurred.
	 */
	scbp_next = LIST_FIRST(&ahd->pending_scbs);
	while (scbp_next != NULL) {
		scbp = scbp_next;
		scbp_next = LIST_NEXT(scbp, pending_links);
		if (ahd_match_scb(ahd, scbp, target, channel, lun, tag, role)) {
			cam_status ostat;

			ostat = aic_get_transaction_status(scbp);
			if (ostat == CAM_REQ_INPROG)
				aic_set_transaction_status(scbp, status);
			if (aic_get_transaction_status(scbp) != CAM_REQ_CMP)
				aic_freeze_scb(scbp);
			if ((scbp->flags & SCB_ACTIVE) == 0)
				printf("Inactive SCB on pending list\n");
			ahd_done(ahd, scbp);
			found++;
		}
	}
	ahd_restore_modes(ahd, saved_modes);
	ahd_platform_abort_scbs(ahd, target, channel, lun, tag, role, status);
	ahd->flags |= AHD_UPDATE_PEND_CMDS;
	return found;
}