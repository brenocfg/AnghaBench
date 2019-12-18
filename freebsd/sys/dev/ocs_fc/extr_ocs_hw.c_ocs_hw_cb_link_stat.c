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
struct TYPE_14__ {TYPE_1__ hdr; int /*<<< orphan*/  received_dropped_no_available_xri_resources_count; int /*<<< orphan*/  received_dropped_no_available_rpi_resources_count; int /*<<< orphan*/  received_dropped_no_aer_count; int /*<<< orphan*/  received_soff_count; int /*<<< orphan*/  received_eofni_count; int /*<<< orphan*/  received_eofdti_count; int /*<<< orphan*/  received_eofa_count; int /*<<< orphan*/  current_transmit_buffer_to_buffer_credit; int /*<<< orphan*/  advertised_transmit_buffer_to_buffer_credit; int /*<<< orphan*/  current_receive_buffer_to_buffer_credit; int /*<<< orphan*/  advertised_receive_bufftor_to_buffer_credit; int /*<<< orphan*/  arbitration_fc_al_timout_count; int /*<<< orphan*/  elastic_buffer_overrun_error_count; int /*<<< orphan*/  primitive_sequence_event_timeout_count; int /*<<< orphan*/  crc_error_count; int /*<<< orphan*/  invalid_transmission_word_error_count; int /*<<< orphan*/  primitive_sequence_error_count; int /*<<< orphan*/  loss_of_signal_error_count; int /*<<< orphan*/  loss_of_sync_error_count; int /*<<< orphan*/  link_failure_error_count; int /*<<< orphan*/  w21of; int /*<<< orphan*/  w20of; int /*<<< orphan*/  w19of; int /*<<< orphan*/  w18of; int /*<<< orphan*/  w17of; int /*<<< orphan*/  w16of; int /*<<< orphan*/  w15of; int /*<<< orphan*/  w14of; int /*<<< orphan*/  w13of; int /*<<< orphan*/  w12of; int /*<<< orphan*/  w11of; int /*<<< orphan*/  w10of; int /*<<< orphan*/  w09of; int /*<<< orphan*/  w08of; int /*<<< orphan*/  w07of; int /*<<< orphan*/  w06of; int /*<<< orphan*/  w05of; int /*<<< orphan*/  w04of; int /*<<< orphan*/  w03of; int /*<<< orphan*/  w02of; scalar_t__ gec; } ;
typedef  TYPE_3__ sli4_cmd_read_link_stats_t ;
struct TYPE_15__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_4__ ocs_hw_t ;
struct TYPE_16__ {int /*<<< orphan*/  counter; int /*<<< orphan*/  overflow; } ;
typedef  TYPE_5__ ocs_hw_link_stat_counts_t ;
typedef  TYPE_2__ ocs_hw_link_stat_cb_arg_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 size_t OCS_HW_LINK_STAT_ADVERTISED_RCV_B2B_CREDIT ; 
 size_t OCS_HW_LINK_STAT_ADVERTISED_XMIT_B2B_CREDIT ; 
 size_t OCS_HW_LINK_STAT_ARB_TIMEOUT_COUNT ; 
 size_t OCS_HW_LINK_STAT_CRC_COUNT ; 
 size_t OCS_HW_LINK_STAT_CURR_RCV_B2B_CREDIT ; 
 size_t OCS_HW_LINK_STAT_CURR_XMIT_B2B_CREDIT ; 
 size_t OCS_HW_LINK_STAT_ELASTIC_BUFFER_OVERRUN_COUNT ; 
 size_t OCS_HW_LINK_STAT_INVALID_XMIT_WORD_COUNT ; 
 size_t OCS_HW_LINK_STAT_LINK_FAILURE_COUNT ; 
 size_t OCS_HW_LINK_STAT_LOSS_OF_SIGNAL_COUNT ; 
 size_t OCS_HW_LINK_STAT_LOSS_OF_SYNC_COUNT ; 
 int OCS_HW_LINK_STAT_MAX ; 
 size_t OCS_HW_LINK_STAT_PRIMITIVE_SEQ_COUNT ; 
 size_t OCS_HW_LINK_STAT_PRIMITIVE_SEQ_TIMEOUT_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_DROPPED_NO_AER_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_DROPPED_NO_RPI_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_DROPPED_NO_XRI_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_EOFA_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_EOFDTI_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_EOFNI_COUNT ; 
 size_t OCS_HW_LINK_STAT_RCV_SOFF_COUNT ; 
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_link_stat(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{

	sli4_cmd_read_link_stats_t* mbox_rsp = (sli4_cmd_read_link_stats_t*) mqe;
	ocs_hw_link_stat_cb_arg_t *cb_arg = arg;
	ocs_hw_link_stat_counts_t counts[OCS_HW_LINK_STAT_MAX];
	uint32_t num_counters = (mbox_rsp->gec ? 20 : 13);

	ocs_memset(counts, 0, sizeof(ocs_hw_link_stat_counts_t) *
		   OCS_HW_LINK_STAT_MAX);

	counts[OCS_HW_LINK_STAT_LINK_FAILURE_COUNT].overflow = mbox_rsp->w02of;
	counts[OCS_HW_LINK_STAT_LOSS_OF_SYNC_COUNT].overflow = mbox_rsp->w03of;
	counts[OCS_HW_LINK_STAT_LOSS_OF_SIGNAL_COUNT].overflow = mbox_rsp->w04of;
	counts[OCS_HW_LINK_STAT_PRIMITIVE_SEQ_COUNT].overflow = mbox_rsp->w05of;
	counts[OCS_HW_LINK_STAT_INVALID_XMIT_WORD_COUNT].overflow = mbox_rsp->w06of;
	counts[OCS_HW_LINK_STAT_CRC_COUNT].overflow = mbox_rsp->w07of;
	counts[OCS_HW_LINK_STAT_PRIMITIVE_SEQ_TIMEOUT_COUNT].overflow = mbox_rsp->w08of;
	counts[OCS_HW_LINK_STAT_ELASTIC_BUFFER_OVERRUN_COUNT].overflow = mbox_rsp->w09of;
	counts[OCS_HW_LINK_STAT_ARB_TIMEOUT_COUNT].overflow = mbox_rsp->w10of;
	counts[OCS_HW_LINK_STAT_ADVERTISED_RCV_B2B_CREDIT].overflow = mbox_rsp->w11of;
	counts[OCS_HW_LINK_STAT_CURR_RCV_B2B_CREDIT].overflow = mbox_rsp->w12of;
	counts[OCS_HW_LINK_STAT_ADVERTISED_XMIT_B2B_CREDIT].overflow = mbox_rsp->w13of;
	counts[OCS_HW_LINK_STAT_CURR_XMIT_B2B_CREDIT].overflow = mbox_rsp->w14of;
	counts[OCS_HW_LINK_STAT_RCV_EOFA_COUNT].overflow = mbox_rsp->w15of;
	counts[OCS_HW_LINK_STAT_RCV_EOFDTI_COUNT].overflow = mbox_rsp->w16of;
	counts[OCS_HW_LINK_STAT_RCV_EOFNI_COUNT].overflow = mbox_rsp->w17of;
	counts[OCS_HW_LINK_STAT_RCV_SOFF_COUNT].overflow = mbox_rsp->w18of;
	counts[OCS_HW_LINK_STAT_RCV_DROPPED_NO_AER_COUNT].overflow = mbox_rsp->w19of;
	counts[OCS_HW_LINK_STAT_RCV_DROPPED_NO_RPI_COUNT].overflow = mbox_rsp->w20of;
	counts[OCS_HW_LINK_STAT_RCV_DROPPED_NO_XRI_COUNT].overflow = mbox_rsp->w21of;

	counts[OCS_HW_LINK_STAT_LINK_FAILURE_COUNT].counter = mbox_rsp->link_failure_error_count;
	counts[OCS_HW_LINK_STAT_LOSS_OF_SYNC_COUNT].counter = mbox_rsp->loss_of_sync_error_count;
	counts[OCS_HW_LINK_STAT_LOSS_OF_SIGNAL_COUNT].counter = mbox_rsp->loss_of_signal_error_count;
	counts[OCS_HW_LINK_STAT_PRIMITIVE_SEQ_COUNT].counter = mbox_rsp->primitive_sequence_error_count;
	counts[OCS_HW_LINK_STAT_INVALID_XMIT_WORD_COUNT].counter = mbox_rsp->invalid_transmission_word_error_count;
	counts[OCS_HW_LINK_STAT_CRC_COUNT].counter = mbox_rsp->crc_error_count;
	counts[OCS_HW_LINK_STAT_PRIMITIVE_SEQ_TIMEOUT_COUNT].counter = mbox_rsp->primitive_sequence_event_timeout_count;
	counts[OCS_HW_LINK_STAT_ELASTIC_BUFFER_OVERRUN_COUNT].counter = mbox_rsp->elastic_buffer_overrun_error_count;
	counts[OCS_HW_LINK_STAT_ARB_TIMEOUT_COUNT].counter = mbox_rsp->arbitration_fc_al_timout_count;
	counts[OCS_HW_LINK_STAT_ADVERTISED_RCV_B2B_CREDIT].counter = mbox_rsp->advertised_receive_bufftor_to_buffer_credit;
	counts[OCS_HW_LINK_STAT_CURR_RCV_B2B_CREDIT].counter = mbox_rsp->current_receive_buffer_to_buffer_credit;
	counts[OCS_HW_LINK_STAT_ADVERTISED_XMIT_B2B_CREDIT].counter = mbox_rsp->advertised_transmit_buffer_to_buffer_credit;
	counts[OCS_HW_LINK_STAT_CURR_XMIT_B2B_CREDIT].counter = mbox_rsp->current_transmit_buffer_to_buffer_credit;
	counts[OCS_HW_LINK_STAT_RCV_EOFA_COUNT].counter = mbox_rsp->received_eofa_count;
	counts[OCS_HW_LINK_STAT_RCV_EOFDTI_COUNT].counter = mbox_rsp->received_eofdti_count;
	counts[OCS_HW_LINK_STAT_RCV_EOFNI_COUNT].counter = mbox_rsp->received_eofni_count;
	counts[OCS_HW_LINK_STAT_RCV_SOFF_COUNT].counter = mbox_rsp->received_soff_count;
	counts[OCS_HW_LINK_STAT_RCV_DROPPED_NO_AER_COUNT].counter = mbox_rsp->received_dropped_no_aer_count;
	counts[OCS_HW_LINK_STAT_RCV_DROPPED_NO_RPI_COUNT].counter = mbox_rsp->received_dropped_no_available_rpi_resources_count;
	counts[OCS_HW_LINK_STAT_RCV_DROPPED_NO_XRI_COUNT].counter = mbox_rsp->received_dropped_no_available_xri_resources_count;

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

		ocs_free(hw->os, cb_arg, sizeof(ocs_hw_link_stat_cb_arg_t));
	}
	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	return 0;
}