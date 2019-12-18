#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct mpt_softc {TYPE_4__* tmf_req; int /*<<< orphan*/  request_pending_list; int /*<<< orphan*/  request_timeout_list; } ;
struct TYPE_9__ {int index; int /*<<< orphan*/  serno; union ccb* ccb; TYPE_3__* req_vbuf; } ;
typedef  TYPE_2__ request_t ;
struct TYPE_11__ {int /*<<< orphan*/  state; int /*<<< orphan*/  ResponseCode; int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_10__ {int Function; } ;
typedef  TYPE_3__ MSG_REQUEST_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_CMD_TIMEOUT ; 
#define  MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH 129 
#define  MPI_FUNCTION_SCSI_IO_REQUEST 128 
 int MPI_IOCSTATUS_MASK ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  MPI_SCSITASKMGMT_RSP_TM_COMPLETE ; 
 int /*<<< orphan*/  MPI_SCSITASKMGMT_RSP_TM_SUCCEEDED ; 
 int /*<<< orphan*/  MPI_SCSITASKMGMT_TASKTYPE_ABORT_TASK ; 
 int /*<<< orphan*/  REQ_STATE_DONE ; 
 int /*<<< orphan*/  REQ_STATE_FREE ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mpt_enable_ints (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_intr (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int /*<<< orphan*/  mpt_reset (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_scsi_send_tmf (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_set_ccb_status (union ccb*,int /*<<< orphan*/ ) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int scsi_io_handler_id ; 

__attribute__((used)) static void
mpt_recover_commands(struct mpt_softc *mpt)
{
	request_t	   *req;
	union ccb	   *ccb;
	int		    error;

	if (TAILQ_EMPTY(&mpt->request_timeout_list) != 0) {
		/*
		 * No work to do- leave.
		 */
		mpt_prt(mpt, "mpt_recover_commands: no requests.\n");
		return;
	}

	/*
	 * Flush any commands whose completion coincides with their timeout.
	 */
	mpt_intr(mpt);

	if (TAILQ_EMPTY(&mpt->request_timeout_list) != 0) {
		/*
		 * The timedout commands have already
		 * completed.  This typically means
		 * that either the timeout value was on
		 * the hairy edge of what the device
		 * requires or - more likely - interrupts
		 * are not happening.
		 */
		mpt_prt(mpt, "Timedout requests already complete. "
		    "Interrupts may not be functioning.\n");
		mpt_enable_ints(mpt);
		return;
	}

	/*
	 * We have no visibility into the current state of the
	 * controller, so attempt to abort the commands in the
	 * order they timed-out. For initiator commands, we
	 * depend on the reply handler pulling requests off
	 * the timeout list.
	 */
	while ((req = TAILQ_FIRST(&mpt->request_timeout_list)) != NULL) {
		uint16_t status;
		uint8_t response;
		MSG_REQUEST_HEADER *hdrp = req->req_vbuf;

		mpt_prt(mpt, "attempting to abort req %p:%u function %x\n",
		    req, req->serno, hdrp->Function);
		ccb = req->ccb;
		if (ccb == NULL) {
			mpt_prt(mpt, "null ccb in timed out request. "
			    "Resetting Controller.\n");
			mpt_reset(mpt, TRUE);
			continue;
		}
		mpt_set_ccb_status(ccb, CAM_CMD_TIMEOUT);

		/*
		 * Check to see if this is not an initiator command and
		 * deal with it differently if it is.
		 */
		switch (hdrp->Function) {
		case MPI_FUNCTION_SCSI_IO_REQUEST:
		case MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH:
			break;
		default:
			/*
			 * XXX: FIX ME: need to abort target assists...
			 */
			mpt_prt(mpt, "just putting it back on the pend q\n");
			TAILQ_REMOVE(&mpt->request_timeout_list, req, links);
			TAILQ_INSERT_HEAD(&mpt->request_pending_list, req,
			    links);
			continue;
		}

		error = mpt_scsi_send_tmf(mpt,
		    MPI_SCSITASKMGMT_TASKTYPE_ABORT_TASK,
		    0, 0, ccb->ccb_h.target_id, ccb->ccb_h.target_lun,
		    htole32(req->index | scsi_io_handler_id), TRUE);

		if (error != 0) {
			/*
			 * mpt_scsi_send_tmf hard resets on failure, so no
			 * need to do so here.  Our queue should be emptied
			 * by the hard reset.
			 */
			continue;
		}

		error = mpt_wait_req(mpt, mpt->tmf_req, REQ_STATE_DONE,
		    REQ_STATE_DONE, TRUE, 500);

		status = le16toh(mpt->tmf_req->IOCStatus);
		response = mpt->tmf_req->ResponseCode;
		mpt->tmf_req->state = REQ_STATE_FREE;

		if (error != 0) {
			/*
			 * If we've errored out,, reset the controller.
			 */
			mpt_prt(mpt, "mpt_recover_commands: abort timed-out. "
			    "Resetting controller\n");
			mpt_reset(mpt, TRUE);
			continue;
		}

		if ((status & MPI_IOCSTATUS_MASK) != MPI_IOCSTATUS_SUCCESS) {
			mpt_prt(mpt, "mpt_recover_commands: IOC Status 0x%x. "
			    "Resetting controller.\n", status);
			mpt_reset(mpt, TRUE);
			continue;
		}

		if (response != MPI_SCSITASKMGMT_RSP_TM_SUCCEEDED &&
		    response != MPI_SCSITASKMGMT_RSP_TM_COMPLETE) {
			mpt_prt(mpt, "mpt_recover_commands: TMF Response 0x%x. "
			    "Resetting controller.\n", response);
			mpt_reset(mpt, TRUE);
			continue;
		}
		mpt_prt(mpt, "abort of req %p:%u completed\n", req, req->serno);
	}
}