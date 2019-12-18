#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct nvme_completion {int /*<<< orphan*/  status; } ;
typedef  int boolean_t ;

/* Variables and functions */
#define  NVME_SCT_COMMAND_SPECIFIC 148 
#define  NVME_SCT_GENERIC 147 
#define  NVME_SCT_MEDIA_ERROR 146 
#define  NVME_SCT_PATH_RELATED 145 
#define  NVME_SCT_VENDOR_SPECIFIC 144 
#define  NVME_SC_ABORTED_BY_REQUEST 143 
#define  NVME_SC_ABORTED_FAILED_FUSED 142 
#define  NVME_SC_ABORTED_MISSING_FUSED 141 
#define  NVME_SC_ABORTED_POWER_LOSS 140 
#define  NVME_SC_ABORTED_SQ_DELETION 139 
#define  NVME_SC_CAPACITY_EXCEEDED 138 
#define  NVME_SC_COMMAND_ID_CONFLICT 137 
#define  NVME_SC_COMMAND_SEQUENCE_ERROR 136 
#define  NVME_SC_DATA_TRANSFER_ERROR 135 
#define  NVME_SC_INTERNAL_DEVICE_ERROR 134 
#define  NVME_SC_INTERNAL_PATH_ERROR 133 
#define  NVME_SC_INVALID_FIELD 132 
#define  NVME_SC_INVALID_NAMESPACE_OR_FORMAT 131 
#define  NVME_SC_INVALID_OPCODE 130 
#define  NVME_SC_LBA_OUT_OF_RANGE 129 
#define  NVME_SC_NAMESPACE_NOT_READY 128 
 int NVME_STATUS_GET_DNR (int /*<<< orphan*/ ) ; 
 int NVME_STATUS_GET_SC (int /*<<< orphan*/ ) ; 
 int NVME_STATUS_GET_SCT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
nvme_completion_is_retry(const struct nvme_completion *cpl)
{
	uint8_t sct, sc, dnr;

	sct = NVME_STATUS_GET_SCT(cpl->status);
	sc = NVME_STATUS_GET_SC(cpl->status);
	dnr = NVME_STATUS_GET_DNR(cpl->status);	/* Do Not Retry Bit */

	/*
	 * TODO: spec is not clear how commands that are aborted due
	 *  to TLER will be marked.  So for now, it seems
	 *  NAMESPACE_NOT_READY is the only case where we should
	 *  look at the DNR bit. Requests failed with ABORTED_BY_REQUEST
	 *  set the DNR bit correctly since the driver controls that.
	 */
	switch (sct) {
	case NVME_SCT_GENERIC:
		switch (sc) {
		case NVME_SC_ABORTED_BY_REQUEST:
		case NVME_SC_NAMESPACE_NOT_READY:
			if (dnr)
				return (0);
			else
				return (1);
		case NVME_SC_INVALID_OPCODE:
		case NVME_SC_INVALID_FIELD:
		case NVME_SC_COMMAND_ID_CONFLICT:
		case NVME_SC_DATA_TRANSFER_ERROR:
		case NVME_SC_ABORTED_POWER_LOSS:
		case NVME_SC_INTERNAL_DEVICE_ERROR:
		case NVME_SC_ABORTED_SQ_DELETION:
		case NVME_SC_ABORTED_FAILED_FUSED:
		case NVME_SC_ABORTED_MISSING_FUSED:
		case NVME_SC_INVALID_NAMESPACE_OR_FORMAT:
		case NVME_SC_COMMAND_SEQUENCE_ERROR:
		case NVME_SC_LBA_OUT_OF_RANGE:
		case NVME_SC_CAPACITY_EXCEEDED:
		default:
			return (0);
		}
	case NVME_SCT_COMMAND_SPECIFIC:
	case NVME_SCT_MEDIA_ERROR:
		return (0);
	case NVME_SCT_PATH_RELATED:
		switch (sc) {
		case NVME_SC_INTERNAL_PATH_ERROR:
			if (dnr)
				return (0);
			else
				return (1);
		default:
			return (0);
		}
	case NVME_SCT_VENDOR_SPECIFIC:
	default:
		return (0);
	}
}