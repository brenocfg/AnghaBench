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
struct TYPE_10__ {int flags; int status; } ;
struct TYPE_9__ {scalar_t__ dxfer_len; scalar_t__ sense_len; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_data; scalar_t__ sense_resid; scalar_t__ resid; } ;
union ccb {TYPE_2__ ccb_h; TYPE_1__ csio; } ;
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct mpt_softc {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  sense_vbuf; union ccb* ccb; } ;
typedef  TYPE_3__ request_t ;
struct TYPE_13__ {scalar_t__ Function; int MsgFlags; } ;
struct TYPE_12__ {int SCSIState; int /*<<< orphan*/  SCSIStatus; int /*<<< orphan*/  TransferCount; int /*<<< orphan*/  SenseCount; int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_4__ MSG_SCSI_IO_REPLY ;
typedef  TYPE_5__ MSG_DEFAULT_REPLY ;

/* Variables and functions */
 int CAM_AUTOSENSE_FAIL ; 
 int CAM_AUTOSNS_VALID ; 
 int CAM_BUSY ; 
 int CAM_DATA_RUN_ERR ; 
 int CAM_PATH_INVALID ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_REQ_INPROG ; 
 int CAM_REQ_TERMIO ; 
 int CAM_RESRC_UNAVAIL ; 
 int CAM_SCSI_BUS_RESET ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_SEL_TIMEOUT ; 
 int CAM_SENSE_PHYS ; 
 int CAM_SENSE_PTR ; 
 int CAM_SEQUENCE_FAIL ; 
 int CAM_STATUS_MASK ; 
 int CAM_TID_INVALID ; 
 int CAM_UA_TERMIO ; 
 int CAM_UNCOR_PARITY ; 
 int CAM_UNEXP_BUSFREE ; 
 int CAM_UNREC_HBA_ERROR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH ; 
 scalar_t__ MPI_FUNCTION_SCSI_IO_REQUEST ; 
#define  MPI_IOCSTATUS_BUSY 148 
#define  MPI_IOCSTATUS_INSUFFICIENT_RESOURCES 147 
#define  MPI_IOCSTATUS_INTERNAL_ERROR 146 
#define  MPI_IOCSTATUS_INVALID_FIELD 145 
#define  MPI_IOCSTATUS_INVALID_FUNCTION 144 
#define  MPI_IOCSTATUS_INVALID_SGL 143 
#define  MPI_IOCSTATUS_INVALID_STATE 142 
 int MPI_IOCSTATUS_MASK ; 
#define  MPI_IOCSTATUS_SCSI_DATA_OVERRUN 141 
#define  MPI_IOCSTATUS_SCSI_DATA_UNDERRUN 140 
#define  MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE 139 
#define  MPI_IOCSTATUS_SCSI_EXT_TERMINATED 138 
#define  MPI_IOCSTATUS_SCSI_INVALID_BUS 137 
#define  MPI_IOCSTATUS_SCSI_INVALID_TARGETID 136 
#define  MPI_IOCSTATUS_SCSI_IOC_TERMINATED 135 
#define  MPI_IOCSTATUS_SCSI_IO_DATA_ERROR 134 
#define  MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR 133 
#define  MPI_IOCSTATUS_SCSI_RECOVERED_ERROR 132 
#define  MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH 131 
#define  MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED 130 
#define  MPI_IOCSTATUS_SCSI_TASK_TERMINATED 129 
#define  MPI_IOCSTATUS_SUCCESS 128 
 int MPI_MSGFLAGS_CONTINUATION_REPLY ; 
 int MPI_SCSI_STATE_AUTOSENSE_FAILED ; 
 int MPI_SCSI_STATE_AUTOSENSE_VALID ; 
 int MPI_SCSI_STATE_NO_SCSI_STATUS ; 
 int MPI_SCSI_STATE_QUEUE_TAG_REJECTED ; 
 int MPI_SCSI_STATE_RESPONSE_INFO_VALID ; 
 int /*<<< orphan*/  MPT_DUMP_REPLY_FRAME (struct mpt_softc*,TYPE_5__*) ; 
 int /*<<< orphan*/  SCSI_STATUS_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpt_freeze_ccb (union ccb*) ; 
 int /*<<< orphan*/  mpt_set_ccb_status (union ccb*,int) ; 

__attribute__((used)) static int
mpt_scsi_reply_frame_handler(struct mpt_softc *mpt, request_t *req,
			     MSG_DEFAULT_REPLY *reply_frame)
{
	union ccb *ccb;
	MSG_SCSI_IO_REPLY *scsi_io_reply;
	u_int ioc_status;
	u_int sstate;

	MPT_DUMP_REPLY_FRAME(mpt, reply_frame);
	KASSERT(reply_frame->Function == MPI_FUNCTION_SCSI_IO_REQUEST
	     || reply_frame->Function == MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH,
		("MPT SCSI I/O Handler called with incorrect reply type"));
	KASSERT((reply_frame->MsgFlags & MPI_MSGFLAGS_CONTINUATION_REPLY) == 0,
		("MPT SCSI I/O Handler called with continuation reply"));

	scsi_io_reply = (MSG_SCSI_IO_REPLY *)reply_frame;
	ioc_status = le16toh(scsi_io_reply->IOCStatus);
	ioc_status &= MPI_IOCSTATUS_MASK;
	sstate = scsi_io_reply->SCSIState;

	ccb = req->ccb;
	ccb->csio.resid =
	    ccb->csio.dxfer_len - le32toh(scsi_io_reply->TransferCount);

	if ((sstate & MPI_SCSI_STATE_AUTOSENSE_VALID) != 0
	 && (ccb->ccb_h.flags & (CAM_SENSE_PHYS | CAM_SENSE_PTR)) == 0) {
		uint32_t sense_returned;

		ccb->ccb_h.status |= CAM_AUTOSNS_VALID;
		
		sense_returned = le32toh(scsi_io_reply->SenseCount);
		if (sense_returned < ccb->csio.sense_len)
			ccb->csio.sense_resid = ccb->csio.sense_len -
						sense_returned;
		else
			ccb->csio.sense_resid = 0;

		bzero(&ccb->csio.sense_data, sizeof(ccb->csio.sense_data));
		bcopy(req->sense_vbuf, &ccb->csio.sense_data,
		    min(ccb->csio.sense_len, sense_returned));
	}

	if ((sstate & MPI_SCSI_STATE_QUEUE_TAG_REJECTED) != 0) {
		/*
		 * Tag messages rejected, but non-tagged retry
		 * was successful.
XXXX
		mpt_set_tags(mpt, devinfo, MPT_QUEUE_NONE);
		 */
	}

	switch(ioc_status) {
	case MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
		/*
		 * XXX
		 * Linux driver indicates that a zero
		 * transfer length with this error code
		 * indicates a CRC error.
		 *
		 * No need to swap the bytes for checking
		 * against zero.
		 */
		if (scsi_io_reply->TransferCount == 0) {
			mpt_set_ccb_status(ccb, CAM_UNCOR_PARITY);
			break;
		}
		/* FALLTHROUGH */
	case MPI_IOCSTATUS_SCSI_DATA_UNDERRUN:
	case MPI_IOCSTATUS_SUCCESS:
	case MPI_IOCSTATUS_SCSI_RECOVERED_ERROR:
		if ((sstate & MPI_SCSI_STATE_NO_SCSI_STATUS) != 0) {
			/*
			 * Status was never returned for this transaction.
			 */
			mpt_set_ccb_status(ccb, CAM_UNEXP_BUSFREE);
		} else if (scsi_io_reply->SCSIStatus != SCSI_STATUS_OK) {
			ccb->csio.scsi_status = scsi_io_reply->SCSIStatus;
			mpt_set_ccb_status(ccb, CAM_SCSI_STATUS_ERROR);
			if ((sstate & MPI_SCSI_STATE_AUTOSENSE_FAILED) != 0)
				mpt_set_ccb_status(ccb, CAM_AUTOSENSE_FAIL);
		} else if ((sstate & MPI_SCSI_STATE_RESPONSE_INFO_VALID) != 0) {

			/* XXX Handle SPI-Packet and FCP-2 response info. */
			mpt_set_ccb_status(ccb, CAM_REQ_CMP_ERR);
		} else
			mpt_set_ccb_status(ccb, CAM_REQ_CMP);
		break;
	case MPI_IOCSTATUS_SCSI_DATA_OVERRUN:
		mpt_set_ccb_status(ccb, CAM_DATA_RUN_ERR);
		break;
	case MPI_IOCSTATUS_SCSI_IO_DATA_ERROR:
		mpt_set_ccb_status(ccb, CAM_UNCOR_PARITY);
		break;
	case MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
		/*
		 * Since selection timeouts and "device really not
		 * there" are grouped into this error code, report
		 * selection timeout.  Selection timeouts are
		 * typically retried before giving up on the device
		 * whereas "device not there" errors are considered
		 * unretryable.
		 */
		mpt_set_ccb_status(ccb, CAM_SEL_TIMEOUT);
		break;
	case MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR:
		mpt_set_ccb_status(ccb, CAM_SEQUENCE_FAIL);
		break;
	case MPI_IOCSTATUS_SCSI_INVALID_BUS:
		mpt_set_ccb_status(ccb, CAM_PATH_INVALID);
		break;
	case MPI_IOCSTATUS_SCSI_INVALID_TARGETID:
		mpt_set_ccb_status(ccb, CAM_TID_INVALID);
		break;
	case MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
		ccb->ccb_h.status = CAM_UA_TERMIO;
		break;
	case MPI_IOCSTATUS_INVALID_STATE:
		/*
		 * The IOC has been reset.  Emulate a bus reset.
		 */
		/* FALLTHROUGH */
	case MPI_IOCSTATUS_SCSI_EXT_TERMINATED:
		ccb->ccb_h.status = CAM_SCSI_BUS_RESET; 
		break;
	case MPI_IOCSTATUS_SCSI_TASK_TERMINATED:
	case MPI_IOCSTATUS_SCSI_IOC_TERMINATED:
		/*
		 * Don't clobber any timeout status that has
		 * already been set for this transaction.  We
		 * want the SCSI layer to be able to differentiate
		 * between the command we aborted due to timeout
		 * and any innocent bystanders.
		 */
		if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_INPROG)
			break;
		mpt_set_ccb_status(ccb, CAM_REQ_TERMIO);
		break;

	case MPI_IOCSTATUS_INSUFFICIENT_RESOURCES:
		mpt_set_ccb_status(ccb, CAM_RESRC_UNAVAIL);
		break;
	case MPI_IOCSTATUS_BUSY:
		mpt_set_ccb_status(ccb, CAM_BUSY);
		break;
	case MPI_IOCSTATUS_INVALID_FUNCTION:
	case MPI_IOCSTATUS_INVALID_SGL:
	case MPI_IOCSTATUS_INTERNAL_ERROR:
	case MPI_IOCSTATUS_INVALID_FIELD:
	default:
		/* XXX
		 * Some of the above may need to kick
		 * of a recovery action!!!!
		 */
		ccb->ccb_h.status = CAM_UNREC_HBA_ERROR;
		break;
	}

	if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		mpt_freeze_ccb(ccb);
	}

	return (TRUE);
}