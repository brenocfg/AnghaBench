#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
struct TYPE_8__ {scalar_t__ status; int /*<<< orphan*/  rpi; int /*<<< orphan*/  xri; int /*<<< orphan*/  agxr; int /*<<< orphan*/  oox; int /*<<< orphan*/  header_data_placement_length; int /*<<< orphan*/  payload_data_placement_length; int /*<<< orphan*/  rq_element_index; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_2__ sli4_fc_optimized_write_cmd_cqe_t ;
struct TYPE_9__ {scalar_t__ status; int /*<<< orphan*/  sequence_reporting_placement_length; int /*<<< orphan*/  rq_id; int /*<<< orphan*/  rq_element_index; } ;
typedef  TYPE_3__ sli4_fc_coalescing_rcqe_t ;
struct TYPE_10__ {scalar_t__ status; int /*<<< orphan*/  header_data_placement_length; int /*<<< orphan*/  eof_byte; int /*<<< orphan*/  sof_byte; int /*<<< orphan*/  payload_data_placement_length; int /*<<< orphan*/  rq_element_index; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_4__ sli4_fc_async_rcqe_v1_t ;
struct TYPE_11__ {scalar_t__ status; int /*<<< orphan*/  header_data_placement_length; int /*<<< orphan*/  eof_byte; int /*<<< orphan*/  sof_byte; int /*<<< orphan*/  payload_data_placement_length; int /*<<< orphan*/  rq_element_index; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_5__ sli4_fc_async_rcqe_t ;
typedef  int int32_t ;

/* Variables and functions */
 size_t SLI4_CQE_CODE_OFFSET ; 
 scalar_t__ SLI4_CQE_CODE_OPTIMIZED_WRITE_CMD ; 
 scalar_t__ SLI4_CQE_CODE_RQ_ASYNC ; 
 scalar_t__ SLI4_CQE_CODE_RQ_ASYNC_V1 ; 
 scalar_t__ SLI4_CQE_CODE_RQ_COALESCING ; 
 scalar_t__ SLI4_FC_ASYNC_RQ_SUCCESS ; 
 scalar_t__ SLI4_FC_COALESCE_RQ_SUCCESS ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sli_fc_get_status_string (int) ; 

int32_t
sli_fc_rqe_rqid_and_index(sli4_t *sli4, uint8_t *cqe, uint16_t *rq_id, uint32_t *index)
{
	sli4_fc_async_rcqe_t	*rcqe = (void *)cqe;
	sli4_fc_async_rcqe_v1_t	*rcqe_v1 = (void *)cqe;
	int32_t	rc = -1;
	uint8_t	code = 0;

	*rq_id = 0;
	*index = UINT32_MAX;

	code = cqe[SLI4_CQE_CODE_OFFSET];

	if (code == SLI4_CQE_CODE_RQ_ASYNC) {
		*rq_id = rcqe->rq_id;
		if (SLI4_FC_ASYNC_RQ_SUCCESS == rcqe->status) {
			*index = rcqe->rq_element_index;
			rc = 0;
		} else {
			*index = rcqe->rq_element_index;
			rc = rcqe->status;
			ocs_log_test(sli4->os, "status=%02x (%s) rq_id=%d, index=%x pdpl=%x sof=%02x eof=%02x hdpl=%x\n",
				rcqe->status, sli_fc_get_status_string(rcqe->status), rcqe->rq_id,
				rcqe->rq_element_index, rcqe->payload_data_placement_length, rcqe->sof_byte,
				rcqe->eof_byte, rcqe->header_data_placement_length);
		}
	} else if (code == SLI4_CQE_CODE_RQ_ASYNC_V1) {
		*rq_id = rcqe_v1->rq_id;
		if (SLI4_FC_ASYNC_RQ_SUCCESS == rcqe_v1->status) {
			*index = rcqe_v1->rq_element_index;
			rc = 0;
		} else {
			*index = rcqe_v1->rq_element_index;
			rc = rcqe_v1->status;
			ocs_log_test(sli4->os, "status=%02x (%s) rq_id=%d, index=%x pdpl=%x sof=%02x eof=%02x hdpl=%x\n",
				rcqe_v1->status, sli_fc_get_status_string(rcqe_v1->status),
				rcqe_v1->rq_id, rcqe_v1->rq_element_index,
				rcqe_v1->payload_data_placement_length, rcqe_v1->sof_byte,
				rcqe_v1->eof_byte, rcqe_v1->header_data_placement_length);
		}
	} else if (code == SLI4_CQE_CODE_OPTIMIZED_WRITE_CMD) {
		sli4_fc_optimized_write_cmd_cqe_t *optcqe = (void *)cqe;

		*rq_id = optcqe->rq_id;
		if (SLI4_FC_ASYNC_RQ_SUCCESS == optcqe->status) {
			*index = optcqe->rq_element_index;
			rc = 0;
		} else {
			*index = optcqe->rq_element_index;
			rc = optcqe->status;
			ocs_log_test(sli4->os, "status=%02x (%s) rq_id=%d, index=%x pdpl=%x hdpl=%x oox=%d agxr=%d xri=0x%x rpi=0x%x\n",
				optcqe->status, sli_fc_get_status_string(optcqe->status), optcqe->rq_id,
				optcqe->rq_element_index, optcqe->payload_data_placement_length,
				optcqe->header_data_placement_length, optcqe->oox, optcqe->agxr, optcqe->xri,
				optcqe->rpi);
		}
	} else if (code == SLI4_CQE_CODE_RQ_COALESCING) {
		sli4_fc_coalescing_rcqe_t	*rcqe = (void *)cqe;

		*rq_id = rcqe->rq_id;
		if (SLI4_FC_COALESCE_RQ_SUCCESS == rcqe->status) {
			*index = rcqe->rq_element_index;
			rc = 0;
		} else {
			*index = UINT32_MAX;
			rc = rcqe->status;

			ocs_log_test(sli4->os, "status=%02x (%s) rq_id=%d, index=%x rq_id=%#x sdpl=%x\n",
				rcqe->status, sli_fc_get_status_string(rcqe->status), rcqe->rq_id,
				rcqe->rq_element_index, rcqe->rq_id, rcqe->sequence_reporting_placement_length);
		}
	} else {
		*index = UINT32_MAX;

		rc = rcqe->status;

		ocs_log_debug(sli4->os, "status=%02x rq_id=%d, index=%x pdpl=%x sof=%02x eof=%02x hdpl=%x\n",
			rcqe->status, rcqe->rq_id, rcqe->rq_element_index, rcqe->payload_data_placement_length,
			rcqe->sof_byte, rcqe->eof_byte, rcqe->header_data_placement_length);
	}

	return rc;
}