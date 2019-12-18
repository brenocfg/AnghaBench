#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {int status; } ;
struct ccb_scsiio {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int CAM_AUTOSNS_VALID ; 
#define  CAM_CMD_TIMEOUT 138 
#define  CAM_DEV_NOT_THERE 137 
#define  CAM_REQ_ABORTED 136 
#define  CAM_REQ_CMP 135 
#define  CAM_REQ_CMP_ERR 134 
#define  CAM_REQ_INVALID 133 
#define  CAM_SCSI_BUSY 132 
#define  CAM_SCSI_BUS_RESET 131 
#define  CAM_SCSI_STATUS_ERROR 130 
#define  CAM_SEL_TIMEOUT 129 
 int CAM_STATUS_MASK ; 
#define  CAM_UNCOR_PARITY 128 
 int /*<<< orphan*/  DID_ABORT ; 
 int /*<<< orphan*/  DID_BAD_TARGET ; 
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  DID_OK ; 
 int /*<<< orphan*/  DID_PARITY ; 
 int /*<<< orphan*/  DID_RESET ; 
 int /*<<< orphan*/  DID_TIME_OUT ; 
 int /*<<< orphan*/  DRIVER_ERROR ; 
 int /*<<< orphan*/  DRIVER_INVALID ; 
 int /*<<< orphan*/  DRIVER_SENSE ; 

__attribute__((used)) static void
sg_scsiio_status(struct ccb_scsiio *csio, u_short *hoststat, u_short *drvstat)
{
	int status;

	status = csio->ccb_h.status;

	switch (status & CAM_STATUS_MASK) {
	case CAM_REQ_CMP:
		*hoststat = DID_OK;
		*drvstat = 0;
		break;
	case CAM_REQ_CMP_ERR:
		*hoststat = DID_ERROR;
		*drvstat = 0;
		break;
	case CAM_REQ_ABORTED:
		*hoststat = DID_ABORT;
		*drvstat = 0;
		break;
	case CAM_REQ_INVALID:
		*hoststat = DID_ERROR;
		*drvstat = DRIVER_INVALID;
		break;
	case CAM_DEV_NOT_THERE:
		*hoststat = DID_BAD_TARGET;
		*drvstat = 0;
		break;
	case CAM_SEL_TIMEOUT:
		*hoststat = DID_NO_CONNECT;
		*drvstat = 0;
		break;
	case CAM_CMD_TIMEOUT:
		*hoststat = DID_TIME_OUT;
		*drvstat = 0;
		break;
	case CAM_SCSI_STATUS_ERROR:
		*hoststat = DID_ERROR;
		*drvstat = 0;
		break;
	case CAM_SCSI_BUS_RESET:
		*hoststat = DID_RESET;
		*drvstat = 0;
		break;
	case CAM_UNCOR_PARITY:
		*hoststat = DID_PARITY;
		*drvstat = 0;
		break;
	case CAM_SCSI_BUSY:
		*hoststat = DID_BUS_BUSY;
		*drvstat = 0;
		break;
	default:
		*hoststat = DID_ERROR;
		*drvstat = DRIVER_ERROR;
	}

	if (status & CAM_AUTOSNS_VALID)
		*drvstat = DRIVER_SENSE;
}