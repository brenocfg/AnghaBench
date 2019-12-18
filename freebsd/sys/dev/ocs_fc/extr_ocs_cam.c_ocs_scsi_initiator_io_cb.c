#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ flags; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {struct ocs_softc* ccb_ocs_ptr; int /*<<< orphan*/ * ccb_io_ptr; int /*<<< orphan*/  path; int /*<<< orphan*/  status; } ;
struct ccb_scsiio {scalar_t__ scsi_status; scalar_t__ resid; scalar_t__ dxfer_len; scalar_t__ sense_len; scalar_t__ sense_resid; TYPE_2__ ccb_h; int /*<<< orphan*/  sense_data; } ;
union ccb {TYPE_3__ ccb_h; struct ccb_scsiio csio; } ;
typedef  scalar_t__ uint32_t ;
struct ocs_softc {int /*<<< orphan*/  buf_dmat; } ;
typedef  scalar_t__ ocs_scsi_io_status_e ;
struct TYPE_12__ {scalar_t__ scsi_status; scalar_t__ residual; scalar_t__ response_wire_length; scalar_t__ sense_data_length; int /*<<< orphan*/  sense_data; } ;
typedef  TYPE_4__ ocs_scsi_cmd_resp_t ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  dmap; } ;
struct TYPE_13__ {TYPE_1__ tgt_io; } ;
typedef  TYPE_5__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  cam_status ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_DATA_RUN_ERR ; 
 int /*<<< orphan*/  CAM_DEV_QFRZN ; 
 scalar_t__ CAM_DIR_IN ; 
 scalar_t__ CAM_DIR_MASK ; 
 scalar_t__ CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
 int CAM_SENSE_PHYS ; 
 int CAM_SENSE_PTR ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int OCS_CAM_IO_F_DMAPPED ; 
 scalar_t__ OCS_SCSI_STATUS_CHECK_RESPONSE ; 
 scalar_t__ OCS_SCSI_STATUS_GOOD ; 
 scalar_t__ SCSI_STATUS_OK ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_scsi_io_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_set_ccb_status (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int32_t ocs_scsi_initiator_io_cb(ocs_io_t *io,
					ocs_scsi_io_status_e scsi_status,
					ocs_scsi_cmd_resp_t *rsp,
					uint32_t flags, void *arg)
{
	union ccb *ccb = arg;
	struct ccb_scsiio *csio = &ccb->csio;
	struct ocs_softc *ocs = csio->ccb_h.ccb_ocs_ptr;
	uint32_t cam_dir = ccb->ccb_h.flags & CAM_DIR_MASK;
	cam_status ccb_status= CAM_REQ_CMP_ERR;

	if (CAM_DIR_NONE != cam_dir) {
		bus_dmasync_op_t op;

		if (CAM_DIR_IN == cam_dir) {
			op = BUS_DMASYNC_POSTREAD;
		} else {
			op = BUS_DMASYNC_POSTWRITE;
		}
		/* Synchronize the DMA memory with the CPU and free the mapping */
		bus_dmamap_sync(ocs->buf_dmat, io->tgt_io.dmap, op);
		if (io->tgt_io.flags & OCS_CAM_IO_F_DMAPPED) {
			bus_dmamap_unload(ocs->buf_dmat, io->tgt_io.dmap);
		}
	}

	if (scsi_status == OCS_SCSI_STATUS_CHECK_RESPONSE) {
		csio->scsi_status = rsp->scsi_status;
		if (SCSI_STATUS_OK != rsp->scsi_status) {
			ccb_status = CAM_SCSI_STATUS_ERROR;
		}

		csio->resid = rsp->residual;
		if (rsp->residual > 0) {
			uint32_t length = rsp->response_wire_length;
			/* underflow */
			if (csio->dxfer_len == (length + csio->resid)) {
				ccb_status = CAM_REQ_CMP;
			}
		} else if (rsp->residual < 0) {
			ccb_status = CAM_DATA_RUN_ERR;
		}

		if ((rsp->sense_data_length) &&
			!(ccb->ccb_h.flags & (CAM_SENSE_PHYS | CAM_SENSE_PTR))) {
			uint32_t	sense_len = 0;

			ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
			if (rsp->sense_data_length < csio->sense_len) {
				csio->sense_resid = 
					csio->sense_len - rsp->sense_data_length;
				sense_len = rsp->sense_data_length;
			} else {
				csio->sense_resid = 0;
				sense_len = csio->sense_len;
			}
			ocs_memcpy(&csio->sense_data, rsp->sense_data, sense_len);
		}
	} else if (scsi_status != OCS_SCSI_STATUS_GOOD) {
		ccb_status = CAM_REQ_CMP_ERR;
		ocs_set_ccb_status(ccb, ccb_status);
		csio->ccb_h.status |= CAM_DEV_QFRZN;
		xpt_freeze_devq(csio->ccb_h.path, 1);

	} else {
		ccb_status = CAM_REQ_CMP;
	}

	ocs_set_ccb_status(ccb, ccb_status);

	ocs_scsi_io_free(io);

	csio->ccb_h.ccb_io_ptr = NULL;
	csio->ccb_h.ccb_ocs_ptr = NULL;
	ccb->ccb_h.status &= ~CAM_SIM_QUEUED;

	xpt_done(ccb);

	return 0;
}