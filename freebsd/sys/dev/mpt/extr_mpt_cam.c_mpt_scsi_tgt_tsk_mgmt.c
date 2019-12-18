#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_8__ {int /*<<< orphan*/  inots; } ;
typedef  TYPE_2__ tgt_resource_t ;
struct mpt_softc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; scalar_t__ target_lun; } ;
struct ccb_immediate_notify {int initiator_id; TYPE_1__ ccb_h; int /*<<< orphan*/  arg; scalar_t__ seq_id; int /*<<< orphan*/  tag_id; } ;
typedef  int /*<<< orphan*/  request_t ;
struct TYPE_9__ {union ccb* ccb; int /*<<< orphan*/  tag_id; } ;
typedef  TYPE_3__ mpt_tgt_state_t ;
typedef  int mpt_task_mgmt_t ;
struct TYPE_10__ {int /*<<< orphan*/  stqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_MESSAGE_RECV ; 
#define  MPT_ABORT_TASK_SET 134 
#define  MPT_CLEAR_ACA 133 
#define  MPT_CLEAR_TASK_SET 132 
#define  MPT_LOGICAL_UNIT_RESET 131 
 int /*<<< orphan*/  MPT_PRT_DEBUG1 ; 
 int /*<<< orphan*/  MPT_PRT_WARN ; 
#define  MPT_QUERY_ASYNC_EVENT 130 
#define  MPT_QUERY_TASK_SET 129 
#define  MPT_TARGET_RESET 128 
 TYPE_3__* MPT_TGT_STATE (struct mpt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ABORT_TASK_SET ; 
 int /*<<< orphan*/  MSG_CLEAR_ACA ; 
 int /*<<< orphan*/  MSG_CLEAR_TASK_SET ; 
 int /*<<< orphan*/  MSG_LOGICAL_UNIT_RESET ; 
 int /*<<< orphan*/  MSG_NOOP ; 
 int /*<<< orphan*/  MSG_QUERY_ASYNC_EVENT ; 
 int /*<<< orphan*/  MSG_QUERY_TASK_SET ; 
 int /*<<< orphan*/  MSG_TARGET_RESET ; 
 int /*<<< orphan*/  SCSI_STATUS_BUSY ; 
 scalar_t__ STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpt_scsi_tgt_status (struct mpt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ sim_links ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
mpt_scsi_tgt_tsk_mgmt(struct mpt_softc *mpt, request_t *req, mpt_task_mgmt_t fc,
    tgt_resource_t *trtp, int init_id)
{
	struct ccb_immediate_notify *inot;
	mpt_tgt_state_t *tgt;

	tgt = MPT_TGT_STATE(mpt, req);
	inot = (struct ccb_immediate_notify *) STAILQ_FIRST(&trtp->inots);
	if (inot == NULL) {
		mpt_lprt(mpt, MPT_PRT_WARN, "no INOTSs- sending back BSY\n");
		mpt_scsi_tgt_status(mpt, NULL, req, SCSI_STATUS_BUSY, NULL, 0);
		return;
	}
	STAILQ_REMOVE_HEAD(&trtp->inots, sim_links.stqe);
	mpt_lprt(mpt, MPT_PRT_DEBUG1,
	    "Get FREE INOT %p lun %jx\n", inot,
	    (uintmax_t)inot->ccb_h.target_lun);

	inot->initiator_id = init_id;	/* XXX */
	inot->tag_id = tgt->tag_id;
	inot->seq_id = 0;
	/*
	 * This is a somewhat grotesque attempt to map from task management
	 * to old style SCSI messages. God help us all.
	 */
	switch (fc) {
	case MPT_QUERY_TASK_SET:
		inot->arg = MSG_QUERY_TASK_SET;
		break;
	case MPT_ABORT_TASK_SET:
		inot->arg = MSG_ABORT_TASK_SET;
		break;
	case MPT_CLEAR_TASK_SET:
		inot->arg = MSG_CLEAR_TASK_SET;
		break;
	case MPT_QUERY_ASYNC_EVENT:
		inot->arg = MSG_QUERY_ASYNC_EVENT;
		break;
	case MPT_LOGICAL_UNIT_RESET:
		inot->arg = MSG_LOGICAL_UNIT_RESET;
		break;
	case MPT_TARGET_RESET:
		inot->arg = MSG_TARGET_RESET;
		break;
	case MPT_CLEAR_ACA:
		inot->arg = MSG_CLEAR_ACA;
		break;
	default:
		inot->arg = MSG_NOOP;
		break;
	}
	tgt->ccb = (union ccb *) inot;
	inot->ccb_h.status = CAM_MESSAGE_RECV;
	xpt_done((union ccb *)inot);
}