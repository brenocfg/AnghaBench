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
struct mpr_softc {int dummy; } ;
struct mpr_command {TYPE_3__* cm_ccb; TYPE_2__* cm_targ; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
struct TYPE_6__ {TYPE_1__ ccb_h; } ;
struct TYPE_5__ {int tid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPRSAS_TARGET_INRESET ; 
 int /*<<< orphan*/  MPR_FUNCTRACE (struct mpr_softc*) ; 
 int /*<<< orphan*/  MPR_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mpr_free_high_priority_command (struct mpr_softc*,struct mpr_command*) ; 
 int /*<<< orphan*/  xpt_free_ccb (TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_devq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
mprsas_free_tm(struct mpr_softc *sc, struct mpr_command *tm)
{
	int target_id = 0xFFFFFFFF;

	MPR_FUNCTRACE(sc);
	if (tm == NULL)
		return;

	/*
	 * For TM's the devq is frozen for the device.  Unfreeze it here and
	 * free the resources used for freezing the devq.  Must clear the
	 * INRESET flag as well or scsi I/O will not work.
	 */
	if (tm->cm_targ != NULL) {
		tm->cm_targ->flags &= ~MPRSAS_TARGET_INRESET;
		target_id = tm->cm_targ->tid;
	}
	if (tm->cm_ccb) {
		mpr_dprint(sc, MPR_INFO, "Unfreezing devq for target ID %d\n",
		    target_id);
		xpt_release_devq(tm->cm_ccb->ccb_h.path, 1, TRUE);
		xpt_free_path(tm->cm_ccb->ccb_h.path);
		xpt_free_ccb(tm->cm_ccb);
	}

	mpr_free_high_priority_command(sc, tm);
}