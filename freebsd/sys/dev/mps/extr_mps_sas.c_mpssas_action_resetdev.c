#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t target_id; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct mpssas_target {int /*<<< orphan*/  handle; } ;
struct mpssas_softc {size_t maxtargets; struct mpssas_target* targets; struct mps_softc* sc; } ;
struct mps_softc {int /*<<< orphan*/  mps_mtx; } ;
struct mps_command {struct mpssas_target* cm_targ; union ccb* cm_complete_data; int /*<<< orphan*/  cm_complete; int /*<<< orphan*/ * cm_data; scalar_t__ cm_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  MsgFlags; int /*<<< orphan*/  TaskType; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_2__ MPI2_SCSI_TASK_MANAGE_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPI2_SCSITASKMGMT_MSGFLAGS_LINK_RESET ; 
 int /*<<< orphan*/  MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET ; 
 int /*<<< orphan*/  MPS_ERROR ; 
 int /*<<< orphan*/  MPS_FUNCTRACE (struct mps_softc*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mps_map_command (struct mps_softc*,struct mps_command*) ; 
 struct mps_command* mpssas_alloc_tm (struct mps_softc*) ; 
 int /*<<< orphan*/  mpssas_prepare_for_tm (struct mps_softc*,struct mps_command*,struct mpssas_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpssas_resetdev_complete ; 
 int /*<<< orphan*/  mpssas_set_ccbstatus (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
mpssas_action_resetdev(struct mpssas_softc *sassc, union ccb *ccb)
{
	MPI2_SCSI_TASK_MANAGE_REQUEST *req;
	struct mps_softc *sc;
	struct mps_command *tm;
	struct mpssas_target *targ;

	MPS_FUNCTRACE(sassc->sc);
	mtx_assert(&sassc->sc->mps_mtx, MA_OWNED);

	KASSERT(ccb->ccb_h.target_id < sassc->maxtargets,
	    ("Target %d out of bounds in XPT_RESET_DEV\n",
	     ccb->ccb_h.target_id));
	sc = sassc->sc;
	tm = mpssas_alloc_tm(sc);
	if (tm == NULL) {
		mps_dprint(sc, MPS_ERROR,
		    "command alloc failure in mpssas_action_resetdev\n");
		mpssas_set_ccbstatus(ccb, CAM_RESRC_UNAVAIL);
		xpt_done(ccb);
		return;
	}

	targ = &sassc->targets[ccb->ccb_h.target_id];
	req = (MPI2_SCSI_TASK_MANAGE_REQUEST *)tm->cm_req;
	req->DevHandle = htole16(targ->handle);
	req->TaskType = MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET;

	/* SAS Hard Link Reset / SATA Link Reset */
	req->MsgFlags = MPI2_SCSITASKMGMT_MSGFLAGS_LINK_RESET;

	tm->cm_data = NULL;
	tm->cm_complete = mpssas_resetdev_complete;
	tm->cm_complete_data = ccb;
	tm->cm_targ = targ;

	mpssas_prepare_for_tm(sc, tm, targ, CAM_LUN_WILDCARD);
	mps_map_command(sc, tm);
}