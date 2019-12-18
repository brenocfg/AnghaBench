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
struct TYPE_6__ {int status; } ;
struct TYPE_5__ {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_len; } ;
union ccb {TYPE_3__ ccb_h; TYPE_2__ csio; } ;
struct twa_softc {int /*<<< orphan*/  sim_lock; } ;
struct tw_osli_req_context {scalar_t__ state; scalar_t__ error_code; scalar_t__ deadline; scalar_t__ orig_req; struct twa_softc* ctlr; int /*<<< orphan*/  req_pkt; } ;
struct tw_cl_scsi_req_packet {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_len; } ;
struct TYPE_4__ {struct tw_cl_scsi_req_packet scsi_req; } ;
struct tw_cl_req_packet {int status; TYPE_1__ gen_req_pkt; } ;
struct tw_cl_req_handle {struct tw_osli_req_context* osl_req_ctxt; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
 int CAM_DEV_NOT_THERE ; 
 int CAM_REQUEUE_REQ ; 
 int CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 int CAM_REQ_TOO_BIG ; 
 int CAM_SCSI_BUS_RESET ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_SEL_TIMEOUT ; 
 int CAM_SIM_QUEUED ; 
 scalar_t__ EBUSY ; 
 scalar_t__ EFBIG ; 
 int TW_CL_ERR_REQ_AUTO_SENSE_VALID ; 
 int TW_CL_ERR_REQ_BUS_RESET ; 
 int TW_CL_ERR_REQ_INVALID_LUN ; 
 int TW_CL_ERR_REQ_INVALID_TARGET ; 
 int TW_CL_ERR_REQ_SCSI_ERROR ; 
 int TW_CL_ERR_REQ_SUCCESS ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  TW_OSLI_BUSY_Q ; 
 int /*<<< orphan*/  TW_OSLI_FREE_Q ; 
 scalar_t__ TW_OSLI_REQ_STATE_BUSY ; 
 scalar_t__ TW_OSLI_REQ_STATE_COMPLETE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct tw_osli_req_context*,scalar_t__) ; 
 int /*<<< orphan*/  tw_osli_req_q_insert_tail (struct tw_osli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_req_q_remove_item (struct tw_osli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_unmap_request (struct tw_osli_req_context*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

TW_VOID
tw_osl_complete_io(struct tw_cl_req_handle *req_handle)
{
	struct tw_osli_req_context	*req = req_handle->osl_req_ctxt;
	struct tw_cl_req_packet		*req_pkt =
		(struct tw_cl_req_packet *)(&req->req_pkt);
	struct tw_cl_scsi_req_packet	*scsi_req;
	struct twa_softc		*sc = req->ctlr;
	union ccb			*ccb = (union ccb *)(req->orig_req);

	tw_osli_dbg_dprintf(10, sc, "entering");

	if (req->state != TW_OSLI_REQ_STATE_BUSY)
		tw_osli_printf(sc, "request = %p, status = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x210A,
			"Unposted command completed!!",
			req, req->state);

	/*
	 * Remove request from the busy queue.  Just mark it complete.
	 * There's no need to move it into the complete queue as we are
	 * going to be done with it right now.
	 */
	req->state = TW_OSLI_REQ_STATE_COMPLETE;
	tw_osli_req_q_remove_item(req, TW_OSLI_BUSY_Q);

	tw_osli_unmap_request(req);

	req->deadline = 0;
	if (req->error_code) {
		/* This request never got submitted to the firmware. */
		if (req->error_code == EBUSY) {
			/*
			 * Cmd queue is full, or the Common Layer is out of
			 * resources.  The simq will already have been frozen.
			 * When this ccb gets completed will unfreeze the simq.
			 */
			ccb->ccb_h.status |= CAM_REQUEUE_REQ;
		}
		else if (req->error_code == EFBIG)
			ccb->ccb_h.status = CAM_REQ_TOO_BIG;
		else
			ccb->ccb_h.status = CAM_REQ_CMP_ERR;
	} else {
		scsi_req = &(req_pkt->gen_req_pkt.scsi_req);
		if (req_pkt->status == TW_CL_ERR_REQ_SUCCESS)
			ccb->ccb_h.status = CAM_REQ_CMP;
		else {
			if (req_pkt->status & TW_CL_ERR_REQ_INVALID_TARGET)
				ccb->ccb_h.status |= CAM_SEL_TIMEOUT;
			else if (req_pkt->status & TW_CL_ERR_REQ_INVALID_LUN)
				ccb->ccb_h.status |= CAM_DEV_NOT_THERE;
			else if (req_pkt->status & TW_CL_ERR_REQ_SCSI_ERROR)
				ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
			else if (req_pkt->status & TW_CL_ERR_REQ_BUS_RESET)
				ccb->ccb_h.status |= (CAM_REQUEUE_REQ | CAM_SCSI_BUS_RESET);
			/*
			 * If none of the above errors occurred, simply
			 * mark completion error.
			 */
			if (ccb->ccb_h.status == 0)
				ccb->ccb_h.status = CAM_REQ_CMP_ERR;

			if (req_pkt->status & TW_CL_ERR_REQ_AUTO_SENSE_VALID) {
				ccb->csio.sense_len = scsi_req->sense_len;
				ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
			}
		}

		ccb->csio.scsi_status = scsi_req->scsi_status;
	}

	ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
	mtx_lock(sc->sim_lock);
	xpt_done(ccb);
	mtx_unlock(sc->sim_lock);
	if (! req->error_code)
		 /* twa_action will free the request otherwise */
		tw_osli_req_q_insert_tail(req, TW_OSLI_FREE_Q);
}