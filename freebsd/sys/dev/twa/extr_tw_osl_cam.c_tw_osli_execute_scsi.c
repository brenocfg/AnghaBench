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
struct TYPE_4__ {int /*<<< orphan*/ * cdb_bytes; int /*<<< orphan*/ * cdb_ptr; } ;
struct ccb_scsiio {scalar_t__ dxfer_len; int /*<<< orphan*/  data_ptr; int /*<<< orphan*/  cdb_len; TYPE_2__ cdb_io; int /*<<< orphan*/  sense_data; } ;
struct ccb_hdr {scalar_t__ target_id; scalar_t__ target_lun; int flags; int timeout; int /*<<< orphan*/  status; int /*<<< orphan*/  path_id; } ;
union ccb {struct ccb_scsiio csio; struct ccb_hdr ccb_h; } ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct twa_softc {int dummy; } ;
struct tw_cl_scsi_req_packet {scalar_t__ unit; scalar_t__ lun; int sgl_entries; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/ * cdb; scalar_t__ scsi_status; int /*<<< orphan*/ * sense_data; scalar_t__ sense_len; } ;
struct TYPE_3__ {struct tw_cl_scsi_req_packet scsi_req; } ;
struct tw_cl_req_packet {TYPE_1__ gen_req_pkt; int /*<<< orphan*/  tw_osl_callback; scalar_t__ status; } ;
struct tw_osli_req_context {int flags; scalar_t__ length; scalar_t__ deadline; int /*<<< orphan*/  data; struct tw_cl_req_packet req_pkt; struct twa_softc* ctlr; } ;
typedef  int /*<<< orphan*/  TW_UINT8 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int CAM_DATA_MASK ; 
 int CAM_DATA_VADDR ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_LUN_INVALID ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  CAM_REQ_TOO_BIG ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  CAM_TID_INVALID ; 
 scalar_t__ TW_CL_MAX_IO_SIZE ; 
 scalar_t__ TW_CL_MAX_NUM_LUNS ; 
 scalar_t__ TW_CL_MAX_NUM_UNITS ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int TW_OSLI_REQ_FLAGS_CCB ; 
 int TW_OSLI_REQ_FLAGS_DATA_IN ; 
 int TW_OSLI_REQ_FLAGS_DATA_OUT ; 
 int TW_OSLI_REQ_FLAGS_FAILED ; 
 int /*<<< orphan*/  tw_osl_complete_io ; 
 scalar_t__ tw_osl_get_local_time () ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*,int /*<<< orphan*/ ,...) ; 
 int tw_osli_map_request (struct tw_osli_req_context*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

TW_INT32
tw_osli_execute_scsi(struct tw_osli_req_context *req, union ccb *ccb)
{
	struct twa_softc		*sc = req->ctlr;
	struct tw_cl_req_packet		*req_pkt;
	struct tw_cl_scsi_req_packet	*scsi_req;
	struct ccb_hdr			*ccb_h = &(ccb->ccb_h);
	struct ccb_scsiio		*csio = &(ccb->csio);
	TW_INT32			error;

	tw_osli_dbg_dprintf(10, sc, "SCSI I/O request 0x%x",
		csio->cdb_io.cdb_bytes[0]);

	if (ccb_h->target_id >= TW_CL_MAX_NUM_UNITS) {
		tw_osli_dbg_dprintf(3, sc, "Invalid target. PTL = %x %x %jx",
			ccb_h->path_id, ccb_h->target_id,
			(uintmax_t)ccb_h->target_lun);
		ccb_h->status |= CAM_TID_INVALID;
		xpt_done(ccb);
		return(1);
	}
	if (ccb_h->target_lun >= TW_CL_MAX_NUM_LUNS) {
		tw_osli_dbg_dprintf(3, sc, "Invalid lun. PTL = %x %x %jx",
			ccb_h->path_id, ccb_h->target_id,
			(uintmax_t)ccb_h->target_lun);
		ccb_h->status |= CAM_LUN_INVALID;
		xpt_done(ccb);
		return(1);
	}

	if(ccb_h->flags & CAM_CDB_PHYS) {
		tw_osli_printf(sc, "",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2105,
			"Physical CDB address!");
		ccb_h->status = CAM_REQ_INVALID;
		xpt_done(ccb);
		return(1);
	}

	/*
	 * We are going to work on this request.  Mark it as enqueued (though
	 * we don't actually queue it...)
	 */
	ccb_h->status |= CAM_SIM_QUEUED;

	if((ccb_h->flags & CAM_DIR_MASK) != CAM_DIR_NONE) {
		if(ccb_h->flags & CAM_DIR_IN)
			req->flags |= TW_OSLI_REQ_FLAGS_DATA_IN;
		else
			req->flags |= TW_OSLI_REQ_FLAGS_DATA_OUT;
	}

	/* Build the CL understood request packet for SCSI cmds. */
	req_pkt = &req->req_pkt;
	req_pkt->status = 0;
	req_pkt->tw_osl_callback = tw_osl_complete_io;
	scsi_req = &(req_pkt->gen_req_pkt.scsi_req);
	scsi_req->unit = ccb_h->target_id;
	scsi_req->lun = ccb_h->target_lun;
	scsi_req->sense_len = 0;
	scsi_req->sense_data = (TW_UINT8 *)(&csio->sense_data);
	scsi_req->scsi_status = 0;
	if(ccb_h->flags & CAM_CDB_POINTER)
		scsi_req->cdb = csio->cdb_io.cdb_ptr;
	else
		scsi_req->cdb = csio->cdb_io.cdb_bytes;
	scsi_req->cdb_len = csio->cdb_len;

	if (csio->dxfer_len > TW_CL_MAX_IO_SIZE) {
		tw_osli_printf(sc, "size = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2106,
			"I/O size too big",
			csio->dxfer_len);
		ccb_h->status = CAM_REQ_TOO_BIG;
		ccb_h->status &= ~CAM_SIM_QUEUED;
		xpt_done(ccb);
		return(1);
	}
	if ((ccb_h->flags & CAM_DATA_MASK) == CAM_DATA_VADDR) {
		if ((req->length = csio->dxfer_len) != 0) {
			req->data = csio->data_ptr;
			scsi_req->sgl_entries = 1;
		}
	} else
		req->flags |= TW_OSLI_REQ_FLAGS_CCB;
	req->deadline = tw_osl_get_local_time() + (ccb_h->timeout / 1000);

	/*
	 * twa_map_load_data_callback will fill in the SGL,
	 * and submit the I/O.
	 */
	error = tw_osli_map_request(req);
	if ((error) && (req->flags & TW_OSLI_REQ_FLAGS_FAILED)) {
		req->deadline = 0;
		ccb_h->status = CAM_REQ_CMP_ERR;
		ccb_h->status &= ~CAM_SIM_QUEUED;
		xpt_done(ccb);
	}
	return(error);
}