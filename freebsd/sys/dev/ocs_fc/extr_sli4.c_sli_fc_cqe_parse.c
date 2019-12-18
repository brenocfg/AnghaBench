#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_queue_t ;
typedef  int /*<<< orphan*/  sli4_qentry_e ;
struct TYPE_12__ {int /*<<< orphan*/  xri; } ;
typedef  TYPE_2__ sli4_fc_xri_aborted_cqe_t ;
struct TYPE_13__ {int /*<<< orphan*/  wq_id; } ;
typedef  TYPE_3__ sli4_fc_wqec_t ;
struct TYPE_14__ {int status; int /*<<< orphan*/  xb; int /*<<< orphan*/  wqe_specific_2; int /*<<< orphan*/  wqe_specific_1; int /*<<< orphan*/  request_tag; int /*<<< orphan*/  hw_status; } ;
typedef  TYPE_4__ sli4_fc_wcqe_t ;
struct TYPE_15__ {int status; int /*<<< orphan*/  xb; int /*<<< orphan*/  total_data_placed; int /*<<< orphan*/  xri; int /*<<< orphan*/  hw_status; } ;
typedef  TYPE_5__ sli4_fc_optimized_write_data_cqe_t ;
struct TYPE_16__ {int status; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_6__ sli4_fc_optimized_write_cmd_cqe_t ;
struct TYPE_17__ {int status; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_7__ sli4_fc_coalescing_rcqe_t ;
struct TYPE_18__ {int status; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_8__ sli4_fc_async_rcqe_v1_t ;
struct TYPE_19__ {int status; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_9__ sli4_fc_async_rcqe_t ;
typedef  int int32_t ;

/* Variables and functions */
 size_t SLI4_CQE_CODE_OFFSET ; 
#define  SLI4_CQE_CODE_OPTIMIZED_WRITE_CMD 135 
#define  SLI4_CQE_CODE_OPTIMIZED_WRITE_DATA 134 
#define  SLI4_CQE_CODE_RELEASE_WQE 133 
#define  SLI4_CQE_CODE_RQ_ASYNC 132 
#define  SLI4_CQE_CODE_RQ_ASYNC_V1 131 
#define  SLI4_CQE_CODE_RQ_COALESCING 130 
#define  SLI4_CQE_CODE_WORK_REQUEST_COMPLETION 129 
#define  SLI4_CQE_CODE_XRI_ABORTED 128 
 int SLI4_FC_WCQE_STATUS_FCP_RSP_FAILURE ; 
 int SLI4_FC_WCQE_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SLI_QENTRY_MAX ; 
 int /*<<< orphan*/  SLI_QENTRY_OPT_WRITE_CMD ; 
 int /*<<< orphan*/  SLI_QENTRY_OPT_WRITE_DATA ; 
 int /*<<< orphan*/  SLI_QENTRY_RQ ; 
 int /*<<< orphan*/  SLI_QENTRY_WQ ; 
 int /*<<< orphan*/  SLI_QENTRY_WQ_RELEASE ; 
 int /*<<< orphan*/  SLI_QENTRY_XABT ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int,...) ; 

int32_t
sli_fc_cqe_parse(sli4_t *sli4, sli4_queue_t *cq, uint8_t *cqe, sli4_qentry_e *etype,
		uint16_t *r_id)
{
	uint8_t		code = cqe[SLI4_CQE_CODE_OFFSET];
	int32_t		rc = -1;

	switch (code) {
	case SLI4_CQE_CODE_WORK_REQUEST_COMPLETION:
	{
		sli4_fc_wcqe_t *wcqe = (void *)cqe;

		*etype = SLI_QENTRY_WQ;
		*r_id = wcqe->request_tag;
		rc = wcqe->status;

		/* Flag errors except for FCP_RSP_FAILURE */
		if (rc && (rc != SLI4_FC_WCQE_STATUS_FCP_RSP_FAILURE)) {

			ocs_log_test(sli4->os, "WCQE: status=%#x hw_status=%#x tag=%#x w1=%#x w2=%#x xb=%d\n",
				wcqe->status, wcqe->hw_status,
				wcqe->request_tag, wcqe->wqe_specific_1,
				wcqe->wqe_specific_2, wcqe->xb);
			ocs_log_test(sli4->os, "      %08X %08X %08X %08X\n", ((uint32_t*) cqe)[0], ((uint32_t*) cqe)[1],
				((uint32_t*) cqe)[2], ((uint32_t*) cqe)[3]);
		}

		/* TODO: need to pass additional status back out of here as well
		 * as status (could overload rc as status/addlstatus are only 8 bits each)
		 */

		break;
	}
	case SLI4_CQE_CODE_RQ_ASYNC:
	{
		sli4_fc_async_rcqe_t *rcqe = (void *)cqe;

		*etype = SLI_QENTRY_RQ;
		*r_id = rcqe->rq_id;
		rc = rcqe->status;
		break;
	}
	case SLI4_CQE_CODE_RQ_ASYNC_V1:
	{
		sli4_fc_async_rcqe_v1_t *rcqe = (void *)cqe;

		*etype = SLI_QENTRY_RQ;
		*r_id = rcqe->rq_id;
		rc = rcqe->status;
		break;
	}
	case SLI4_CQE_CODE_OPTIMIZED_WRITE_CMD:
	{
		sli4_fc_optimized_write_cmd_cqe_t *optcqe = (void *)cqe;

		*etype = SLI_QENTRY_OPT_WRITE_CMD;
		*r_id = optcqe->rq_id;
		rc = optcqe->status;
		break;
	}
	case SLI4_CQE_CODE_OPTIMIZED_WRITE_DATA:
	{
		sli4_fc_optimized_write_data_cqe_t *dcqe = (void *)cqe;

		*etype = SLI_QENTRY_OPT_WRITE_DATA;
		*r_id = dcqe->xri;
		rc = dcqe->status;

		/* Flag errors */
		if (rc != SLI4_FC_WCQE_STATUS_SUCCESS) {
			ocs_log_test(sli4->os, "Optimized DATA CQE: status=%#x hw_status=%#x xri=%#x dpl=%#x w3=%#x xb=%d\n",
				dcqe->status, dcqe->hw_status,
				dcqe->xri, dcqe->total_data_placed,
				((uint32_t*) cqe)[3], dcqe->xb);
		}
		break;
	}
	case SLI4_CQE_CODE_RQ_COALESCING:
	{
		sli4_fc_coalescing_rcqe_t *rcqe = (void *)cqe;

		*etype = SLI_QENTRY_RQ;
		*r_id = rcqe->rq_id;
		rc = rcqe->status;
		break;
	}
	case SLI4_CQE_CODE_XRI_ABORTED:
	{
		sli4_fc_xri_aborted_cqe_t *xa = (void *)cqe;

		*etype = SLI_QENTRY_XABT;
		*r_id = xa->xri;
		rc = 0;
		break;
	}
	case SLI4_CQE_CODE_RELEASE_WQE: {
		sli4_fc_wqec_t *wqec = (void*) cqe;

		*etype = SLI_QENTRY_WQ_RELEASE;
		*r_id = wqec->wq_id;
		rc = 0;
		break;
	}
	default:
		ocs_log_test(sli4->os, "CQE completion code %d not handled\n", code);
		*etype = SLI_QENTRY_MAX;
		*r_id = UINT16_MAX;
	}

	return rc;
}