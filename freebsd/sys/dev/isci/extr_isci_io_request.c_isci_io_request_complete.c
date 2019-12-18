#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  path; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; int /*<<< orphan*/  func_code; } ;
struct ccb_scsiio {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_data; scalar_t__ sense_len; scalar_t__ sense_resid; scalar_t__ dxfer_len; scalar_t__ resid; } ;
struct TYPE_9__ {scalar_t__ smp_response_len; int /*<<< orphan*/ * smp_response; } ;
union ccb {TYPE_6__ ccb_h; struct ccb_scsiio csio; TYPE_2__ smpio; } ;
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
struct ccb_relsim {int /*<<< orphan*/  openings; int /*<<< orphan*/  release_flags; TYPE_4__ ccb_h; } ;
struct cam_path {int dummy; } ;
struct ISCI_REQUEST {int dummy; } ;
struct ISCI_REMOTE_DEVICE {scalar_t__ frozen_lun_mask; int /*<<< orphan*/  queued_ccbs; union ccb* queued_ccb_in_progress; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  timer; } ;
struct ISCI_IO_REQUEST {union ccb* ccb; TYPE_1__ parent; int /*<<< orphan*/  sci_object; } ;
struct ISCI_CONTROLLER {scalar_t__ is_frozen; int /*<<< orphan*/  sim; int /*<<< orphan*/  request_pool; } ;
struct TYPE_12__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_10__ {void* data; int /*<<< orphan*/  status; int /*<<< orphan*/  sense_data_length; } ;
typedef  TYPE_3__ SCI_SSP_RESPONSE_IU_T ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int SCI_IO_STATUS ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  void* BOOL ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int CAM_AUTOSNS_VALID ; 
 int CAM_DEV_NOT_THERE ; 
 int /*<<< orphan*/  CAM_DEV_QFREEZE ; 
 int CAM_DEV_QFRZN ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_REQ_TERMIO ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_SIM_QUEUED ; 
 int CAM_STATUS_MASK ; 
 void* FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RELSIM_ADJUST_OPENINGS ; 
#define  SCI_IO_FAILURE 143 
#define  SCI_IO_FAILURE_CONTROLLER_SPECIFIC_ERR 142 
#define  SCI_IO_FAILURE_INSUFFICIENT_RESOURCES 141 
#define  SCI_IO_FAILURE_INVALID_PARAMETER_VALUE 140 
#define  SCI_IO_FAILURE_INVALID_REMOTE_DEVICE 139 
#define  SCI_IO_FAILURE_INVALID_STATE 138 
#define  SCI_IO_FAILURE_NO_NCQ_TAG_AVAILABLE 137 
#define  SCI_IO_FAILURE_PROTOCOL_VIOLATION 136 
#define  SCI_IO_FAILURE_REMOTE_DEVICE_RESET_REQUIRED 135 
#define  SCI_IO_FAILURE_REQUIRES_SCSI_ABORT 134 
#define  SCI_IO_FAILURE_RESPONSE_VALID 133 
#define  SCI_IO_FAILURE_TERMINATED 132 
#define  SCI_IO_FAILURE_UNSUPPORTED_PROTOCOL 131 
#define  SCI_IO_SUCCESS 130 
#define  SCI_IO_SUCCESS_COMPLETE_BEFORE_START 129 
#define  SCI_IO_SUCCESS_IO_DONE_EARLY 128 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  XPT_REL_SIMQ ; 
 int /*<<< orphan*/  XPT_SMP_IO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_log_message (int,char*,char*,union ccb*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  isci_remote_device_freeze_lun_queue (struct ISCI_REMOTE_DEVICE*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_remote_device_release_device_queue (struct ISCI_REMOTE_DEVICE*) ; 
 int /*<<< orphan*/  isci_remote_device_reset (struct ISCI_REMOTE_DEVICE*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,struct ISCI_REQUEST*) ; 
 scalar_t__ sci_ssp_get_sense_data_length (int /*<<< orphan*/ ) ; 
 scalar_t__ scif_io_request_get_number_of_bytes_transferred (int /*<<< orphan*/ ) ; 
 void* scif_io_request_get_response_iu_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_remote_device_get_max_queue_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_extract_sense (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  scsiio_cdb_ptr (struct ccb_scsiio*) ; 
 TYPE_5__ sim_links ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_4__*,struct cam_path*,int) ; 

void
isci_io_request_complete(SCI_CONTROLLER_HANDLE_T scif_controller,
    SCI_REMOTE_DEVICE_HANDLE_T remote_device,
    struct ISCI_IO_REQUEST *isci_request, SCI_IO_STATUS completion_status)
{
	struct ISCI_CONTROLLER *isci_controller;
	struct ISCI_REMOTE_DEVICE *isci_remote_device;
	union ccb *ccb;
	BOOL complete_ccb;
	struct ccb_scsiio *csio;

	complete_ccb = TRUE;
	isci_controller = (struct ISCI_CONTROLLER *) sci_object_get_association(scif_controller);
	isci_remote_device =
		(struct ISCI_REMOTE_DEVICE *) sci_object_get_association(remote_device);

	ccb = isci_request->ccb;
	csio = &ccb->csio;
	ccb->ccb_h.status &= ~CAM_STATUS_MASK;

	switch (completion_status) {
	case SCI_IO_SUCCESS:
	case SCI_IO_SUCCESS_COMPLETE_BEFORE_START:
#if __FreeBSD_version >= 900026
		if (ccb->ccb_h.func_code == XPT_SMP_IO) {
			void *smp_response =
			    scif_io_request_get_response_iu_address(
			        isci_request->sci_object);

			memcpy(ccb->smpio.smp_response, smp_response,
			    ccb->smpio.smp_response_len);
		}
#endif
		ccb->ccb_h.status |= CAM_REQ_CMP;
		break;

	case SCI_IO_SUCCESS_IO_DONE_EARLY:
		ccb->ccb_h.status |= CAM_REQ_CMP;
		ccb->csio.resid = ccb->csio.dxfer_len -
		    scif_io_request_get_number_of_bytes_transferred(
		        isci_request->sci_object);
		break;

	case SCI_IO_FAILURE_RESPONSE_VALID:
	{
		SCI_SSP_RESPONSE_IU_T * response_buffer;
		uint32_t sense_length;
		int error_code, sense_key, asc, ascq;

		response_buffer = (SCI_SSP_RESPONSE_IU_T *)
		    scif_io_request_get_response_iu_address(
		        isci_request->sci_object);

		sense_length = sci_ssp_get_sense_data_length(
		    response_buffer->sense_data_length);

		sense_length = MIN(csio->sense_len, sense_length);

		memcpy(&csio->sense_data, response_buffer->data, sense_length);

		csio->sense_resid = csio->sense_len - sense_length;
		csio->scsi_status = response_buffer->status;
		ccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
		ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
		scsi_extract_sense( &csio->sense_data, &error_code, &sense_key,
		    &asc, &ascq );
		isci_log_message(1, "ISCI",
		    "isci: bus=%x target=%x lun=%x cdb[0]=%x status=%x key=%x asc=%x ascq=%x\n",
		    ccb->ccb_h.path_id, ccb->ccb_h.target_id,
		    ccb->ccb_h.target_lun, scsiio_cdb_ptr(csio),
		    csio->scsi_status, sense_key, asc, ascq);
		break;
	}

	case SCI_IO_FAILURE_REMOTE_DEVICE_RESET_REQUIRED:
		isci_remote_device_reset(isci_remote_device, NULL);
		ccb->ccb_h.status |= CAM_REQ_TERMIO;
		isci_log_message(0, "ISCI",
		    "isci: bus=%x target=%x lun=%x cdb[0]=%x remote device reset required\n",
		    ccb->ccb_h.path_id, ccb->ccb_h.target_id,
		    ccb->ccb_h.target_lun, scsiio_cdb_ptr(csio));
		break;

	case SCI_IO_FAILURE_TERMINATED:
		ccb->ccb_h.status |= CAM_REQ_TERMIO;
		isci_log_message(0, "ISCI",
		    "isci: bus=%x target=%x lun=%x cdb[0]=%x terminated\n",
		    ccb->ccb_h.path_id, ccb->ccb_h.target_id,
		    ccb->ccb_h.target_lun, scsiio_cdb_ptr(csio));
		break;

	case SCI_IO_FAILURE_INVALID_STATE:
	case SCI_IO_FAILURE_INSUFFICIENT_RESOURCES:
		complete_ccb = FALSE;
		break;

	case SCI_IO_FAILURE_INVALID_REMOTE_DEVICE:
		ccb->ccb_h.status |= CAM_DEV_NOT_THERE;
		break;

	case SCI_IO_FAILURE_NO_NCQ_TAG_AVAILABLE:
		{
			struct ccb_relsim ccb_relsim;
			struct cam_path *path;

			xpt_create_path(&path, NULL,
			    cam_sim_path(isci_controller->sim),
			    isci_remote_device->index, 0);

			xpt_setup_ccb(&ccb_relsim.ccb_h, path, 5);
			ccb_relsim.ccb_h.func_code = XPT_REL_SIMQ;
			ccb_relsim.ccb_h.flags = CAM_DEV_QFREEZE;
			ccb_relsim.release_flags = RELSIM_ADJUST_OPENINGS;
			ccb_relsim.openings =
			    scif_remote_device_get_max_queue_depth(remote_device);
			xpt_action((union ccb *)&ccb_relsim);
			xpt_free_path(path);
			complete_ccb = FALSE;
		}
		break;

	case SCI_IO_FAILURE:
	case SCI_IO_FAILURE_REQUIRES_SCSI_ABORT:
	case SCI_IO_FAILURE_UNSUPPORTED_PROTOCOL:
	case SCI_IO_FAILURE_PROTOCOL_VIOLATION:
	case SCI_IO_FAILURE_INVALID_PARAMETER_VALUE:
	case SCI_IO_FAILURE_CONTROLLER_SPECIFIC_ERR:
	default:
		isci_log_message(1, "ISCI",
		    "isci: bus=%x target=%x lun=%x cdb[0]=%x completion status=%x\n",
		    ccb->ccb_h.path_id, ccb->ccb_h.target_id,
		    ccb->ccb_h.target_lun, scsiio_cdb_ptr(csio),
		    completion_status);
		ccb->ccb_h.status |= CAM_REQ_CMP_ERR;
		break;
	}

	callout_stop(&isci_request->parent.timer);
	bus_dmamap_sync(isci_request->parent.dma_tag,
	    isci_request->parent.dma_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	bus_dmamap_unload(isci_request->parent.dma_tag,
	    isci_request->parent.dma_map);

	isci_request->ccb = NULL;

	sci_pool_put(isci_controller->request_pool,
	    (struct ISCI_REQUEST *)isci_request);

	if (complete_ccb) {
		if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
			/* ccb will be completed with some type of non-success
			 *  status.  So temporarily freeze the queue until the
			 *  upper layers can act on the status.  The
			 *  CAM_DEV_QFRZN flag will then release the queue
			 *  after the status is acted upon.
			 */
			ccb->ccb_h.status |= CAM_DEV_QFRZN;
			xpt_freeze_devq(ccb->ccb_h.path, 1);
		}

		if (ccb->ccb_h.status & CAM_SIM_QUEUED) {

			KASSERT(ccb == isci_remote_device->queued_ccb_in_progress,
			    ("multiple internally queued ccbs in flight"));

			TAILQ_REMOVE(&isci_remote_device->queued_ccbs,
			    &ccb->ccb_h, sim_links.tqe);
			ccb->ccb_h.status &= ~CAM_SIM_QUEUED;

			/*
			 * This CCB that was in the queue was completed, so
			 *  set the in_progress pointer to NULL denoting that
			 *  we can retry another CCB from the queue.  We only
			 *  allow one CCB at a time from the queue to be
			 *  in progress so that we can effectively maintain
			 *  ordering.
			 */
			isci_remote_device->queued_ccb_in_progress = NULL;
		}

		if (isci_remote_device->frozen_lun_mask != 0) {
			isci_remote_device_release_device_queue(isci_remote_device);
		}

		xpt_done(ccb);

		if (isci_controller->is_frozen == TRUE) {
			isci_controller->is_frozen = FALSE;
			xpt_release_simq(isci_controller->sim, TRUE);
		}
	} else {
		isci_remote_device_freeze_lun_queue(isci_remote_device,
		    ccb->ccb_h.target_lun);

		if (ccb->ccb_h.status & CAM_SIM_QUEUED) {

			KASSERT(ccb == isci_remote_device->queued_ccb_in_progress,
			    ("multiple internally queued ccbs in flight"));

			/*
			 *  Do nothing, CCB is already on the device's queue.
			 *   We leave it on the queue, to be retried again
			 *   next time a CCB on this device completes, or we
			 *   get a ready notification for this device.
			 */
			isci_log_message(1, "ISCI", "already queued %p %x\n",
			    ccb, scsiio_cdb_ptr(csio));

			isci_remote_device->queued_ccb_in_progress = NULL;

		} else {
			isci_log_message(1, "ISCI", "queue %p %x\n", ccb,
			    scsiio_cdb_ptr(csio));
			ccb->ccb_h.status |= CAM_SIM_QUEUED;

			TAILQ_INSERT_TAIL(&isci_remote_device->queued_ccbs,
			    &ccb->ccb_h, sim_links.tqe);
		}
	}
}