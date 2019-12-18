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
struct TYPE_4__ {int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  resid; int /*<<< orphan*/  dxfer_len; } ;
struct TYPE_3__ {int status; } ;
union ccb {TYPE_2__ csio; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  camdd_buf_status ;
typedef  int cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAMDD_STATUS_EOF ; 
 int /*<<< orphan*/  CAMDD_STATUS_ERROR ; 
 int /*<<< orphan*/  CAMDD_STATUS_NONE ; 
 int /*<<< orphan*/  CAMDD_STATUS_OK ; 
 int /*<<< orphan*/  CAMDD_STATUS_SHORT_IO ; 
#define  CAM_REQ_CMP 140 
#define  CAM_SCSI_STATUS_ERROR 139 
 int CAM_STATUS_MASK ; 
#define  PROTO_NVME 138 
#define  PROTO_SCSI 137 
#define  SCSI_STATUS_BUSY 136 
#define  SCSI_STATUS_CHECK_COND 135 
#define  SCSI_STATUS_CMD_TERMINATED 134 
#define  SCSI_STATUS_COND_MET 133 
#define  SCSI_STATUS_INTERMED 132 
#define  SCSI_STATUS_INTERMED_COND_MET 131 
#define  SCSI_STATUS_OK 130 
#define  SCSI_STATUS_QUEUE_FULL 129 
#define  SCSI_STATUS_RESERV_CONFLICT 128 

camdd_buf_status
camdd_ccb_status(union ccb *ccb, int protocol)
{
	camdd_buf_status status = CAMDD_STATUS_NONE;
	cam_status ccb_status;

	ccb_status = ccb->ccb_h.status & CAM_STATUS_MASK;

	switch (protocol) {
	case PROTO_SCSI:
		switch (ccb_status) {
		case CAM_REQ_CMP: {
			if (ccb->csio.resid == 0) {
				status = CAMDD_STATUS_OK;
			} else if (ccb->csio.dxfer_len > ccb->csio.resid) {
				status = CAMDD_STATUS_SHORT_IO;
			} else {
				status = CAMDD_STATUS_EOF;
			}
			break;
		}
		case CAM_SCSI_STATUS_ERROR: {
			switch (ccb->csio.scsi_status) {
			case SCSI_STATUS_OK:
			case SCSI_STATUS_COND_MET:
			case SCSI_STATUS_INTERMED:
			case SCSI_STATUS_INTERMED_COND_MET:
				status = CAMDD_STATUS_OK;
				break;
			case SCSI_STATUS_CMD_TERMINATED:
			case SCSI_STATUS_CHECK_COND:
			case SCSI_STATUS_QUEUE_FULL:
			case SCSI_STATUS_BUSY:
			case SCSI_STATUS_RESERV_CONFLICT:
			default:
				status = CAMDD_STATUS_ERROR;
				break;
			}
			break;
		}
		default:
			status = CAMDD_STATUS_ERROR;
			break;
		}
		break;
	case PROTO_NVME:
		switch (ccb_status) {
		case CAM_REQ_CMP:
			status = CAMDD_STATUS_OK;
			break;
		default:
			status = CAMDD_STATUS_ERROR;
			break;
		}
		break;
	default:
		status = CAMDD_STATUS_ERROR;
		break;
	}

	return (status);
}