#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (scalar_t__,int,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {scalar_t__ status; } ;
struct TYPE_14__ {TYPE_1__ hdr; int /*<<< orphan*/  empty_xri_pool_count; int /*<<< orphan*/  dropped_frames_due_to_no_xri_count; int /*<<< orphan*/  empty_rq_timeout_count; int /*<<< orphan*/  dropped_frames_due_to_no_rq_buffer_count; int /*<<< orphan*/  receive_f_bsy_count; int /*<<< orphan*/  receive_p_bsy_count; int /*<<< orphan*/  total_exchanges_responder; int /*<<< orphan*/  total_exchanges_originator; int /*<<< orphan*/  receive_sequence_count; int /*<<< orphan*/  transmit_sequence_count; int /*<<< orphan*/  receive_frame_count; int /*<<< orphan*/  transmit_frame_count; int /*<<< orphan*/  receive_kbyte_count; int /*<<< orphan*/  transmit_kbyte_count; } ;
typedef  TYPE_3__ sli4_cmd_read_status_t ;
struct TYPE_15__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_4__ ocs_hw_t ;
struct TYPE_16__ {int /*<<< orphan*/  counter; } ;
typedef  TYPE_5__ ocs_hw_host_stat_counts_t ;
typedef  TYPE_2__ ocs_hw_host_stat_cb_arg_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 size_t OCS_HW_HOST_STAT_DROP_FRM_DUE_TO_NO_RQ_BUF_COUNT ; 
 size_t OCS_HW_HOST_STAT_DROP_FRM_DUE_TO_NO_XRI_COUNT ; 
 size_t OCS_HW_HOST_STAT_EMPTY_RQ_TIMEOUT_COUNT ; 
 size_t OCS_HW_HOST_STAT_EMPTY_XRI_POOL_COUNT ; 
 int OCS_HW_HOST_STAT_MAX ; 
 size_t OCS_HW_HOST_STAT_RX_FRAME_COUNT ; 
 size_t OCS_HW_HOST_STAT_RX_F_BSY_COUNT ; 
 size_t OCS_HW_HOST_STAT_RX_KBYTE_COUNT ; 
 size_t OCS_HW_HOST_STAT_RX_SEQ_COUNT ; 
 size_t OCS_HW_HOST_STAT_TOTAL_EXCH_ORIG ; 
 size_t OCS_HW_HOST_STAT_TOTAL_EXCH_RESP ; 
 size_t OCS_HW_HOST_STAT_TX_FRAME_COUNT ; 
 size_t OCS_HW_HOST_STAT_TX_KBYTE_COUNT ; 
 size_t OCS_HW_HOST_STAT_TX_SEQ_COUNT ; 
 size_t OCS_HW_HOSY_STAT_RX_P_BSY_COUNT ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_host_stat(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{

	sli4_cmd_read_status_t* mbox_rsp = (sli4_cmd_read_status_t*) mqe;
	ocs_hw_host_stat_cb_arg_t *cb_arg = arg;
	ocs_hw_host_stat_counts_t counts[OCS_HW_HOST_STAT_MAX];
	uint32_t num_counters = OCS_HW_HOST_STAT_MAX;

	ocs_memset(counts, 0, sizeof(ocs_hw_host_stat_counts_t) *
		   OCS_HW_HOST_STAT_MAX);

	counts[OCS_HW_HOST_STAT_TX_KBYTE_COUNT].counter = mbox_rsp->transmit_kbyte_count;
	counts[OCS_HW_HOST_STAT_RX_KBYTE_COUNT].counter = mbox_rsp->receive_kbyte_count;
	counts[OCS_HW_HOST_STAT_TX_FRAME_COUNT].counter = mbox_rsp->transmit_frame_count;
	counts[OCS_HW_HOST_STAT_RX_FRAME_COUNT].counter = mbox_rsp->receive_frame_count;
	counts[OCS_HW_HOST_STAT_TX_SEQ_COUNT].counter = mbox_rsp->transmit_sequence_count;
	counts[OCS_HW_HOST_STAT_RX_SEQ_COUNT].counter = mbox_rsp->receive_sequence_count;
	counts[OCS_HW_HOST_STAT_TOTAL_EXCH_ORIG].counter = mbox_rsp->total_exchanges_originator;
	counts[OCS_HW_HOST_STAT_TOTAL_EXCH_RESP].counter = mbox_rsp->total_exchanges_responder;
	counts[OCS_HW_HOSY_STAT_RX_P_BSY_COUNT].counter = mbox_rsp->receive_p_bsy_count;
	counts[OCS_HW_HOST_STAT_RX_F_BSY_COUNT].counter = mbox_rsp->receive_f_bsy_count;
	counts[OCS_HW_HOST_STAT_DROP_FRM_DUE_TO_NO_RQ_BUF_COUNT].counter = mbox_rsp->dropped_frames_due_to_no_rq_buffer_count;
	counts[OCS_HW_HOST_STAT_EMPTY_RQ_TIMEOUT_COUNT].counter = mbox_rsp->empty_rq_timeout_count;
	counts[OCS_HW_HOST_STAT_DROP_FRM_DUE_TO_NO_XRI_COUNT].counter = mbox_rsp->dropped_frames_due_to_no_xri_count;
	counts[OCS_HW_HOST_STAT_EMPTY_XRI_POOL_COUNT].counter = mbox_rsp->empty_xri_pool_count;


	if (cb_arg) {
		if (cb_arg->cb) {
			if ((status == 0) && mbox_rsp->hdr.status) {
				status = mbox_rsp->hdr.status;
			}
			cb_arg->cb(status,
				   num_counters,
				   counts,
				   cb_arg->arg);
		}

		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_host_stat_cb_arg_t));
	}
	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	return 0;
}