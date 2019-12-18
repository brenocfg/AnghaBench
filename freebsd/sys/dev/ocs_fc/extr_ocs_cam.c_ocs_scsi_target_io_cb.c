#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ flags; int /*<<< orphan*/  status; } ;
struct TYPE_11__ {struct ocs_softc* ccb_ocs_ptr; } ;
struct ccb_scsiio {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; TYPE_1__ ccb_h; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_scsiio csio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ocs_softc {int /*<<< orphan*/  buf_dmat; } ;
typedef  int ocs_scsi_io_status_e ;
struct TYPE_14__ {int scsi_status; scalar_t__ residual; int /*<<< orphan*/  sense_data_length; int /*<<< orphan*/ * sense_data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ ocs_scsi_cmd_resp_t ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  state; scalar_t__ sendresp; int /*<<< orphan*/  dmap; } ;
struct TYPE_15__ {TYPE_3__ tgt_io; scalar_t__ transferred; scalar_t__ exp_xfer_len; } ;
typedef  TYPE_5__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ CAM_DIR_IN ; 
 scalar_t__ CAM_DIR_MASK ; 
 scalar_t__ CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int CAM_SEND_SENSE ; 
 int CAM_SEND_STATUS ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  OCS_CAM_IO_DATA_DONE ; 
 int OCS_CAM_IO_F_ABORT_NOTIFY ; 
 int OCS_CAM_IO_F_DMAPPED ; 
 int /*<<< orphan*/  OCS_CAM_IO_RESP ; 
#define  OCS_SCSI_STATUS_ABORTED 129 
#define  OCS_SCSI_STATUS_GOOD 128 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_scsi_send_resp (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/  (*) (TYPE_5__*,int,scalar_t__,void*),union ccb*) ; 
 int /*<<< orphan*/  ocs_set_ccb_status (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_target_io_free (TYPE_5__*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static int32_t ocs_scsi_target_io_cb(ocs_io_t *io, 
				ocs_scsi_io_status_e scsi_status,
				uint32_t flags, void *arg)
{
	union ccb *ccb = arg;
	struct ccb_scsiio *csio = &ccb->csio;
	struct ocs_softc *ocs = csio->ccb_h.ccb_ocs_ptr;
	uint32_t cam_dir = ccb->ccb_h.flags & CAM_DIR_MASK;
	uint32_t io_is_done = 
		(ccb->ccb_h.flags & CAM_SEND_STATUS) == CAM_SEND_STATUS;

	ccb->ccb_h.status &= ~CAM_SIM_QUEUED;

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

	if (io->tgt_io.sendresp) {
		io->tgt_io.sendresp = 0;
		ocs_scsi_cmd_resp_t  resp = { 0 };
		io->tgt_io.state = OCS_CAM_IO_RESP;
		resp.scsi_status = scsi_status;
		if (ccb->ccb_h.flags & CAM_SEND_SENSE) {
			resp.sense_data = (uint8_t *)&csio->sense_data;
			resp.sense_data_length = csio->sense_len;
		}
		resp.residual = io->exp_xfer_len - io->transferred;

		return ocs_scsi_send_resp(io, 0, &resp, ocs_scsi_target_io_cb, ccb);
	}

	switch (scsi_status) {
	case OCS_SCSI_STATUS_GOOD:
		ocs_set_ccb_status(ccb, CAM_REQ_CMP);
		break;
	case OCS_SCSI_STATUS_ABORTED:
		ocs_set_ccb_status(ccb, CAM_REQ_ABORTED);
		break;
	default:
		ocs_set_ccb_status(ccb, CAM_REQ_CMP_ERR);
	}

	if (io_is_done) {
		if ((io->tgt_io.flags & OCS_CAM_IO_F_ABORT_NOTIFY) == 0) {
			ocs_target_io_free(io);
		}
	} else {
		io->tgt_io.state = OCS_CAM_IO_DATA_DONE;
		/*device_printf(ocs->dev, "%s: CTIO state=%d tag=%#x\n",
				__func__, io->tgt_io.state, io->tag);*/
	}

	xpt_done(ccb);

	return 0;
}