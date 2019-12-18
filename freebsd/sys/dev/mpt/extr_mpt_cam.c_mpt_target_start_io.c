#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int status; int flags; TYPE_3__* ccb_req_ptr; } ;
struct TYPE_16__ {int /*<<< orphan*/  target_lun; int /*<<< orphan*/  flags; } ;
struct ccb_scsiio {scalar_t__ dxfer_len; scalar_t__ resid; scalar_t__ scsi_status; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; int /*<<< orphan*/  tag_id; TYPE_1__ ccb_h; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_scsiio csio; } ;
struct mpt_softc {int outofbeer; int scsi_tgt_handler_id; int /*<<< orphan*/  sim; int /*<<< orphan*/  buffer_dmat; scalar_t__ is_spi; scalar_t__ is_sas; } ;
struct TYPE_18__ {int index; int /*<<< orphan*/  dmap; int /*<<< orphan*/  serno; TYPE_5__* req_vbuf; union ccb* ccb; } ;
typedef  TYPE_3__ request_t ;
struct TYPE_19__ {int state; int reply_desc; scalar_t__ resid; int /*<<< orphan*/  bytes_xfered; TYPE_3__* req; union ccb* ccb; } ;
typedef  TYPE_4__ mpt_tgt_state_t ;
typedef  int /*<<< orphan*/  bus_dmamap_callback_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_20__ {scalar_t__ DataLength; int /*<<< orphan*/  TargetAssistFlags; int /*<<< orphan*/  RelativeOffset; int /*<<< orphan*/  LUN; void* ReplyWord; void* MsgContext; int /*<<< orphan*/  Function; int /*<<< orphan*/  Tag; int /*<<< orphan*/  QueueTag; int /*<<< orphan*/  InitiatorTag; } ;
typedef  TYPE_5__* PTR_MSG_TARGET_ASSIST_REQUEST ;
typedef  TYPE_5__* PTR_MPI_TARGET_SSP_CMD_BUFFER ;
typedef  TYPE_5__* PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER ;

/* Variables and functions */
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_EXTLUN_BYTE_SWIZZLE (int /*<<< orphan*/ ) ; 
 int CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int CAM_REQ_INPROG ; 
 int CAM_SEND_SENSE ; 
 int CAM_SEND_STATUS ; 
 int CAM_SIM_QUEUED ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPI_FUNCTION_TARGET_ASSIST ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  MPT_RQSL (struct mpt_softc*) ; 
 TYPE_3__* MPT_TAG_2_REQ (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 TYPE_4__* MPT_TGT_STATE (struct mpt_softc*,TYPE_3__*) ; 
 scalar_t__ SCSI_STATUS_OK ; 
 int /*<<< orphan*/  TARGET_ASSIST_FLAGS_AUTO_STATUS ; 
 int /*<<< orphan*/  TARGET_ASSIST_FLAGS_DATA_DIRECTION ; 
#define  TGT_STATE_IN_CAM 129 
#define  TGT_STATE_MOVING_DATA 128 
 int TGT_STATE_SETTING_UP_FOR_DATA ; 
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpt_execute_req ; 
 int /*<<< orphan*/ * mpt_execute_req_a64 ; 
 TYPE_3__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_scsi_tgt_status (struct mpt_softc*,union ccb*,TYPE_3__*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_set_ccb_status (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_tgt_dump_req_state (struct mpt_softc*,TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_target_start_io(struct mpt_softc *mpt, union ccb *ccb)
{
	struct ccb_scsiio *csio = &ccb->csio;
	request_t *cmd_req = MPT_TAG_2_REQ(mpt, csio->tag_id);
	mpt_tgt_state_t *tgt = MPT_TGT_STATE(mpt, cmd_req);

	switch (tgt->state) {
	case TGT_STATE_IN_CAM:
		break;
	case TGT_STATE_MOVING_DATA:
		mpt_set_ccb_status(ccb, CAM_REQUEUE_REQ);
		xpt_freeze_simq(mpt->sim, 1);
		ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
		tgt->ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		xpt_done(ccb);
		return;
	default:
		mpt_prt(mpt, "ccb %p flags 0x%x tag 0x%08x had bad request "
		    "starting I/O\n", ccb, csio->ccb_h.flags, csio->tag_id);
		mpt_tgt_dump_req_state(mpt, cmd_req);
		mpt_set_ccb_status(ccb, CAM_REQ_CMP_ERR);
		xpt_done(ccb);
		return;
	}

	if (csio->dxfer_len) {
		bus_dmamap_callback_t *cb;
		PTR_MSG_TARGET_ASSIST_REQUEST ta;
		request_t *req;
		int error;

		KASSERT((ccb->ccb_h.flags & CAM_DIR_MASK) != CAM_DIR_NONE,
		    ("dxfer_len %u but direction is NONE", csio->dxfer_len));

		if ((req = mpt_get_request(mpt, FALSE)) == NULL) {
			if (mpt->outofbeer == 0) {
				mpt->outofbeer = 1;
				xpt_freeze_simq(mpt->sim, 1);
				mpt_lprt(mpt, MPT_PRT_DEBUG, "FREEZEQ\n");
			}
			ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
			mpt_set_ccb_status(ccb, CAM_REQUEUE_REQ);
			xpt_done(ccb);
			return;
		}
		ccb->ccb_h.status = CAM_SIM_QUEUED | CAM_REQ_INPROG;
		if (sizeof (bus_addr_t) > 4) {
			cb = mpt_execute_req_a64;
		} else {
			cb = mpt_execute_req;
		}

		req->ccb = ccb;
		ccb->ccb_h.ccb_req_ptr = req;

		/*
		 * Record the currently active ccb and the
		 * request for it in our target state area.
		 */
		tgt->ccb = ccb;
		tgt->req = req;

		memset(req->req_vbuf, 0, MPT_RQSL(mpt));
		ta = req->req_vbuf;

		if (mpt->is_sas) {
			PTR_MPI_TARGET_SSP_CMD_BUFFER ssp =
			     cmd_req->req_vbuf;
			ta->QueueTag = ssp->InitiatorTag;
		} else if (mpt->is_spi) {
			PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER sp =
			     cmd_req->req_vbuf;
			ta->QueueTag = sp->Tag;
		}
		ta->Function = MPI_FUNCTION_TARGET_ASSIST;
		ta->MsgContext = htole32(req->index | mpt->scsi_tgt_handler_id);
		ta->ReplyWord = htole32(tgt->reply_desc);
		be64enc(ta->LUN, CAM_EXTLUN_BYTE_SWIZZLE(csio->ccb_h.target_lun));

		ta->RelativeOffset = tgt->bytes_xfered;
		ta->DataLength = ccb->csio.dxfer_len;
		if (ta->DataLength > tgt->resid) {
			ta->DataLength = tgt->resid;
		}

		/*
		 * XXX Should be done after data transfer completes?
		 */
		csio->resid = csio->dxfer_len - ta->DataLength;
		tgt->resid -= csio->dxfer_len;
		tgt->bytes_xfered += csio->dxfer_len;

		if ((ccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
			ta->TargetAssistFlags |=
			    TARGET_ASSIST_FLAGS_DATA_DIRECTION;
		}

#ifdef	WE_TRUST_AUTO_GOOD_STATUS
		if ((ccb->ccb_h.flags & CAM_SEND_STATUS) &&
		    csio->scsi_status == SCSI_STATUS_OK && tgt->resid == 0) {
			ta->TargetAssistFlags |=
			    TARGET_ASSIST_FLAGS_AUTO_STATUS;
		}
#endif
		tgt->state = TGT_STATE_SETTING_UP_FOR_DATA;

		mpt_lprt(mpt, MPT_PRT_DEBUG, 
		    "DATA_CCB %p tag %x %u bytes %u resid flg %x req %p:%u "
		    "nxtstate=%d\n", csio, csio->tag_id, csio->dxfer_len,
		    tgt->resid, ccb->ccb_h.flags, req, req->serno, tgt->state);

		error = bus_dmamap_load_ccb(mpt->buffer_dmat, req->dmap, ccb,
		    cb, req, 0);
		if (error == EINPROGRESS) {
			xpt_freeze_simq(mpt->sim, 1);
			ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
		}
	} else {
		/*
		 * XXX: I don't know why this seems to happen, but
		 * XXX: completing the CCB seems to make things happy.
		 * XXX: This seems to happen if the initiator requests
		 * XXX: enough data that we have to do multiple CTIOs.
		 */
		if ((ccb->ccb_h.flags & CAM_SEND_STATUS) == 0) {
			mpt_lprt(mpt, MPT_PRT_DEBUG,
			    "Meaningless STATUS CCB (%p): flags %x status %x "
			    "resid %d bytes_xfered %u\n", ccb, ccb->ccb_h.flags,
			    ccb->ccb_h.status, tgt->resid, tgt->bytes_xfered);
			mpt_set_ccb_status(ccb, CAM_REQ_CMP);
			ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
			xpt_done(ccb);
			return;
		}
		mpt_scsi_tgt_status(mpt, ccb, cmd_req, csio->scsi_status,
		    (void *)&csio->sense_data,
		    (ccb->ccb_h.flags & CAM_SEND_SENSE) ?
		     csio->sense_len : 0);
	}
}