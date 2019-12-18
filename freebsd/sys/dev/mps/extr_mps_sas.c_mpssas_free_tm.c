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
struct mps_softc {int dummy; } ;
struct mps_command {TYPE_3__* cm_ccb; TYPE_2__* cm_targ; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
struct TYPE_6__ {TYPE_1__ ccb_h; } ;
struct TYPE_5__ {int tid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPSSAS_TARGET_INRESET ; 
 int /*<<< orphan*/  MPS_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mps_free_high_priority_command (struct mps_softc*,struct mps_command*) ; 
 int /*<<< orphan*/  xpt_free_ccb (TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_devq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
mpssas_free_tm(struct mps_softc *sc, struct mps_command *tm)
{
	int target_id = 0xFFFFFFFF;
 
	if (tm == NULL)
		return;

	/*
	 * For TM's the devq is frozen for the device.  Unfreeze it here and
	 * free the resources used for freezing the devq.  Must clear the
	 * INRESET flag as well or scsi I/O will not work.
	 */
	if (tm->cm_targ != NULL) {
		tm->cm_targ->flags &= ~MPSSAS_TARGET_INRESET;
		target_id = tm->cm_targ->tid;
	}
	if (tm->cm_ccb) {
		mps_dprint(sc, MPS_INFO, "Unfreezing devq for target ID %d\n",
		    target_id);
		xpt_release_devq(tm->cm_ccb->ccb_h.path, 1, TRUE);
		xpt_free_path(tm->cm_ccb->ccb_h.path);
		xpt_free_ccb(tm->cm_ccb);
	}

	mps_free_high_priority_command(sc, tm);
}