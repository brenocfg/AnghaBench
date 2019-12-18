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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int sense_len; int sense_resid; int /*<<< orphan*/  sense_data; } ;
union ccb {TYPE_2__ ccb_h; TYPE_1__ csio; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct scsi_sense_data {int dummy; } ;
struct mpr_command {union ccb* cm_complete_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  MPI2_SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  MPI2_SCSI_STATUS_GOOD ; 
 int /*<<< orphan*/  MPI2_SCSI_STATUS_TASK_ABORTED ; 
#define  NVME_SCT_COMMAND_SPECIFIC 153 
#define  NVME_SCT_GENERIC 152 
#define  NVME_SCT_MEDIA_ERROR 151 
#define  NVME_SC_ABORTED_BY_REQUEST 150 
#define  NVME_SC_ABORTED_FAILED_FUSED 149 
#define  NVME_SC_ABORTED_MISSING_FUSED 148 
#define  NVME_SC_ABORTED_POWER_LOSS 147 
#define  NVME_SC_ABORTED_SQ_DELETION 146 
#define  NVME_SC_ACCESS_DENIED 145 
#define  NVME_SC_APPLICATION_TAG_CHECK_ERROR 144 
#define  NVME_SC_CAPACITY_EXCEEDED 143 
#define  NVME_SC_COMPARE_FAILURE 142 
#define  NVME_SC_CONFLICTING_ATTRIBUTES 141 
#define  NVME_SC_DATA_TRANSFER_ERROR 140 
#define  NVME_SC_GUARD_CHECK_ERROR 139 
#define  NVME_SC_INTERNAL_DEVICE_ERROR 138 
#define  NVME_SC_INVALID_FIELD 137 
#define  NVME_SC_INVALID_FORMAT 136 
#define  NVME_SC_INVALID_NAMESPACE_OR_FORMAT 135 
#define  NVME_SC_INVALID_OPCODE 134 
#define  NVME_SC_LBA_OUT_OF_RANGE 133 
#define  NVME_SC_NAMESPACE_NOT_READY 132 
#define  NVME_SC_REFERENCE_TAG_CHECK_ERROR 131 
#define  NVME_SC_SUCCESS 130 
#define  NVME_SC_UNRECOVERED_READ_ERROR 129 
#define  NVME_SC_WRITE_FAULTS 128 
 int NVME_STATUS_GET_SC (int /*<<< orphan*/ ) ; 
 int NVME_STATUS_GET_SCT (int /*<<< orphan*/ ) ; 
 int SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int SCSI_ASCQ_FORMAT_COMMAND_FAILED ; 
 int SCSI_ASCQ_INVALID_LUN_ID ; 
 int SCSI_ASCQ_LOG_BLOCK_APPTAG_CHECK_FAILED ; 
 int SCSI_ASCQ_LOG_BLOCK_GUARD_CHECK_FAILED ; 
 int SCSI_ASCQ_LOG_BLOCK_REFTAG_CHECK_FAILED ; 
 int SCSI_ASCQ_POWER_LOSS_EXPECTED ; 
 int SCSI_ASC_ACCESS_DENIED_INVALID_LUN_ID ; 
 int SCSI_ASC_FORMAT_COMMAND_FAILED ; 
 int SCSI_ASC_ILLEGAL_BLOCK ; 
 int SCSI_ASC_ILLEGAL_COMMAND ; 
 int SCSI_ASC_INTERNAL_TARGET_FAILURE ; 
 int SCSI_ASC_INVALID_CDB ; 
 int SCSI_ASC_LOG_BLOCK_APPTAG_CHECK_FAILED ; 
 int SCSI_ASC_LOG_BLOCK_GUARD_CHECK_FAILED ; 
 int SCSI_ASC_LOG_BLOCK_REFTAG_CHECK_FAILED ; 
 int SCSI_ASC_LUN_NOT_READY ; 
 int SCSI_ASC_MISCOMPARE_DURING_VERIFY ; 
 int SCSI_ASC_NO_SENSE ; 
 int SCSI_ASC_PERIPHERAL_DEV_WRITE_FAULT ; 
 int SCSI_ASC_UNRECOVERED_READ_ERROR ; 
 int SCSI_ASC_WARNING ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int SSD_KEY_ABORTED_COMMAND ; 
 int SSD_KEY_HARDWARE_ERROR ; 
 int SSD_KEY_ILLEGAL_REQUEST ; 
 int SSD_KEY_MEDIUM_ERROR ; 
 int SSD_KEY_MISCOMPARE ; 
 int SSD_KEY_NOT_READY ; 
 int SSD_KEY_NO_SENSE ; 
 int /*<<< orphan*/  SSD_TYPE_FIXED ; 
 int /*<<< orphan*/  scsi_set_sense_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
mprsas_nvme_trans_status_code(uint16_t nvme_status,
    struct mpr_command *cm)
{
	u8 status = MPI2_SCSI_STATUS_GOOD;
	int skey, asc, ascq;
	union ccb *ccb = cm->cm_complete_data;
	int returned_sense_len;
	uint8_t sct, sc;

	sct = NVME_STATUS_GET_SCT(nvme_status);
	sc = NVME_STATUS_GET_SC(nvme_status);

	status = MPI2_SCSI_STATUS_CHECK_CONDITION;
	skey = SSD_KEY_ILLEGAL_REQUEST;
	asc = SCSI_ASC_NO_SENSE;
	ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;

	switch (sct) {
	case NVME_SCT_GENERIC:
		switch (sc) {
		case NVME_SC_SUCCESS:
			status = MPI2_SCSI_STATUS_GOOD;
			skey = SSD_KEY_NO_SENSE;
			asc = SCSI_ASC_NO_SENSE;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_INVALID_OPCODE:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_ILLEGAL_COMMAND;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_INVALID_FIELD:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_INVALID_CDB;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_DATA_TRANSFER_ERROR:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_NO_SENSE;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_ABORTED_POWER_LOSS:
			status = MPI2_SCSI_STATUS_TASK_ABORTED;
			skey = SSD_KEY_ABORTED_COMMAND;
			asc = SCSI_ASC_WARNING;
			ascq = SCSI_ASCQ_POWER_LOSS_EXPECTED;
			break;
		case NVME_SC_INTERNAL_DEVICE_ERROR:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_HARDWARE_ERROR;
			asc = SCSI_ASC_INTERNAL_TARGET_FAILURE;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_ABORTED_BY_REQUEST:
		case NVME_SC_ABORTED_SQ_DELETION:
		case NVME_SC_ABORTED_FAILED_FUSED:
		case NVME_SC_ABORTED_MISSING_FUSED:
			status = MPI2_SCSI_STATUS_TASK_ABORTED;
			skey = SSD_KEY_ABORTED_COMMAND;
			asc = SCSI_ASC_NO_SENSE;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_INVALID_NAMESPACE_OR_FORMAT:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_ACCESS_DENIED_INVALID_LUN_ID;
			ascq = SCSI_ASCQ_INVALID_LUN_ID;
			break;
		case NVME_SC_LBA_OUT_OF_RANGE:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_ILLEGAL_BLOCK;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_CAPACITY_EXCEEDED:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_NO_SENSE;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_NAMESPACE_NOT_READY:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_NOT_READY; 
			asc = SCSI_ASC_LUN_NOT_READY;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		}
		break;
	case NVME_SCT_COMMAND_SPECIFIC:
		switch (sc) {
		case NVME_SC_INVALID_FORMAT:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_FORMAT_COMMAND_FAILED;
			ascq = SCSI_ASCQ_FORMAT_COMMAND_FAILED;
			break;
		case NVME_SC_CONFLICTING_ATTRIBUTES:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_INVALID_CDB;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		}
		break;
	case NVME_SCT_MEDIA_ERROR:
		switch (sc) {
		case NVME_SC_WRITE_FAULTS:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_PERIPHERAL_DEV_WRITE_FAULT;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_UNRECOVERED_READ_ERROR:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_UNRECOVERED_READ_ERROR;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_GUARD_CHECK_ERROR:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_LOG_BLOCK_GUARD_CHECK_FAILED;
			ascq = SCSI_ASCQ_LOG_BLOCK_GUARD_CHECK_FAILED;
			break;
		case NVME_SC_APPLICATION_TAG_CHECK_ERROR:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_LOG_BLOCK_APPTAG_CHECK_FAILED;
			ascq = SCSI_ASCQ_LOG_BLOCK_APPTAG_CHECK_FAILED;
			break;
		case NVME_SC_REFERENCE_TAG_CHECK_ERROR:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MEDIUM_ERROR;
			asc = SCSI_ASC_LOG_BLOCK_REFTAG_CHECK_FAILED;
			ascq = SCSI_ASCQ_LOG_BLOCK_REFTAG_CHECK_FAILED;
			break;
		case NVME_SC_COMPARE_FAILURE:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_MISCOMPARE;
			asc = SCSI_ASC_MISCOMPARE_DURING_VERIFY;
			ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
			break;
		case NVME_SC_ACCESS_DENIED:
			status = MPI2_SCSI_STATUS_CHECK_CONDITION;
			skey = SSD_KEY_ILLEGAL_REQUEST;
			asc = SCSI_ASC_ACCESS_DENIED_INVALID_LUN_ID;
			ascq = SCSI_ASCQ_INVALID_LUN_ID;
			break;
		}
		break;
	}
	
	returned_sense_len = sizeof(struct scsi_sense_data);
	if (returned_sense_len < ccb->csio.sense_len)
		ccb->csio.sense_resid = ccb->csio.sense_len -
		    returned_sense_len;
	else
		ccb->csio.sense_resid = 0;

	scsi_set_sense_data(&ccb->csio.sense_data, SSD_TYPE_FIXED,
	    1, skey, asc, ascq, SSD_ELEM_NONE);
	ccb->ccb_h.status |= CAM_AUTOSNS_VALID;

	return status;
}