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
typedef  size_t u8 ;
struct ecore_tlv_parsed_buf {size_t* p_val; } ;
struct ecore_mfw_tlv_fcoe {int /*<<< orphan*/ * scsi_chk_tstamp; int /*<<< orphan*/ * scsi_rx_chk; int /*<<< orphan*/ * scsi_rx_chk_set; int /*<<< orphan*/  scsi_tsk_abort; int /*<<< orphan*/  scsi_tsk_abort_set; int /*<<< orphan*/  scsi_aca_active; int /*<<< orphan*/  scsi_aca_active_set; int /*<<< orphan*/  scsi_tsk_full; int /*<<< orphan*/  scsi_tsk_full_set; int /*<<< orphan*/  scsi_rsv_conflicts; int /*<<< orphan*/  scsi_rsv_conflicts_set; int /*<<< orphan*/  scsi_inter_cond_met; int /*<<< orphan*/  scsi_inter_cond_met_set; int /*<<< orphan*/  scsi_inter; int /*<<< orphan*/  scsi_inter_set; int /*<<< orphan*/  scsi_busy; int /*<<< orphan*/  scsi_busy_set; int /*<<< orphan*/  scsi_cond_met; int /*<<< orphan*/  scsi_cond_met_set; int /*<<< orphan*/  scsi_chks; int /*<<< orphan*/  scsi_chks_set; int /*<<< orphan*/  eofni; int /*<<< orphan*/  eofni_set; int /*<<< orphan*/  eofa; int /*<<< orphan*/  eofa_set; int /*<<< orphan*/  rx_lip; int /*<<< orphan*/  rx_lip_set; int /*<<< orphan*/  tx_lip; int /*<<< orphan*/  tx_lip_set; int /*<<< orphan*/  lrr; int /*<<< orphan*/  lrr_set; int /*<<< orphan*/  lr; int /*<<< orphan*/  lr_set; int /*<<< orphan*/  ols; int /*<<< orphan*/  ols_set; int /*<<< orphan*/  rx_nos; int /*<<< orphan*/  rx_nos_set; int /*<<< orphan*/  tx_nos; int /*<<< orphan*/  tx_nos_set; int /*<<< orphan*/  tx_tprlos; int /*<<< orphan*/  tx_tprlos_set; int /*<<< orphan*/  abort_task_sets; int /*<<< orphan*/  abort_task_sets_set; int /*<<< orphan*/  tx_lun_rst; int /*<<< orphan*/  tx_lun_rst_set; int /*<<< orphan*/ * rx_rscn_nport; int /*<<< orphan*/ * rx_rscn_nport_set; int /*<<< orphan*/  rx_rscn; int /*<<< orphan*/  rx_rscn_set; int /*<<< orphan*/ * abts_tstamp; int /*<<< orphan*/ * abts_dst_fcid; int /*<<< orphan*/ * abts_dst_fcid_set; int /*<<< orphan*/  rx_abts_rjt; int /*<<< orphan*/  rx_abts_rjt_set; int /*<<< orphan*/  rx_abts_acc; int /*<<< orphan*/  rx_abts_acc_set; int /*<<< orphan*/  tx_abts; int /*<<< orphan*/  tx_abts_set; int /*<<< orphan*/  rx_accs; int /*<<< orphan*/  rx_accs_set; int /*<<< orphan*/  tx_prlis; int /*<<< orphan*/  tx_prlis_set; int /*<<< orphan*/  tx_accs; int /*<<< orphan*/  tx_accs_set; int /*<<< orphan*/  rx_logos; int /*<<< orphan*/  rx_logos_set; int /*<<< orphan*/ * plogo_tstamp; int /*<<< orphan*/ * plogo_src_fcid; int /*<<< orphan*/ * plogo_src_fcid_set; int /*<<< orphan*/  plogo_rjt; int /*<<< orphan*/  plogo_rjt_set; int /*<<< orphan*/  plogo_acc; int /*<<< orphan*/  plogo_acc_set; int /*<<< orphan*/  tx_plogos; int /*<<< orphan*/  tx_plogos_set; int /*<<< orphan*/ * plogi_acc_tstamp; int /*<<< orphan*/ * plogi_acc_src_fcid; int /*<<< orphan*/ * plogi_acc_src_fcid_set; int /*<<< orphan*/ * plogi_tstamp; int /*<<< orphan*/ * plogi_dst_fcid; int /*<<< orphan*/ * plogi_dst_fcid_set; int /*<<< orphan*/  plogi_rjt; int /*<<< orphan*/  plogi_rjt_set; int /*<<< orphan*/  plogi_acc; int /*<<< orphan*/  plogi_acc_set; int /*<<< orphan*/  plogi; int /*<<< orphan*/  plogi_set; int /*<<< orphan*/  fdisc_rjt; int /*<<< orphan*/  fdisc_rjt_set; int /*<<< orphan*/  fdisc_acc; int /*<<< orphan*/  fdisc_acc_set; int /*<<< orphan*/  fdiscs; int /*<<< orphan*/  fdiscs_set; int /*<<< orphan*/  flogi_rjt_tstamp; int /*<<< orphan*/  flogi_rjt; int /*<<< orphan*/  flogi_rjt_set; int /*<<< orphan*/  flogi_acc_tstamp; int /*<<< orphan*/ * flogi_acc_param; int /*<<< orphan*/ * flogi_acc_param_set; int /*<<< orphan*/  flogi_tstamp; int /*<<< orphan*/ * flogi_param; int /*<<< orphan*/ * flogi_param_set; int /*<<< orphan*/  code_violation_err; int /*<<< orphan*/  code_violation_err_set; int /*<<< orphan*/  disparity_err; int /*<<< orphan*/  disparity_err_set; int /*<<< orphan*/  primtive_err; int /*<<< orphan*/  primtive_err_set; int /*<<< orphan*/  losig_err; int /*<<< orphan*/  losig_err_set; int /*<<< orphan*/  losync_err; int /*<<< orphan*/  losync_err_set; int /*<<< orphan*/ * crc_err; int /*<<< orphan*/ * crc_err_src_fcid; int /*<<< orphan*/ * crc_err_src_fcid_set; int /*<<< orphan*/  crc_count; int /*<<< orphan*/  crc_count_set; int /*<<< orphan*/  fcoe_tx_bytes; int /*<<< orphan*/  fcoe_tx_bytes_set; int /*<<< orphan*/  fcoe_tx_frames; int /*<<< orphan*/  fcoe_tx_frames_set; int /*<<< orphan*/  fcoe_rx_bytes; int /*<<< orphan*/  fcoe_rx_bytes_set; int /*<<< orphan*/  fcoe_rx_frames; int /*<<< orphan*/  fcoe_rx_frames_set; int /*<<< orphan*/  fcoe_rxq_depth; int /*<<< orphan*/  fcoe_rxq_depth_set; int /*<<< orphan*/  fcoe_txq_depth; int /*<<< orphan*/  fcoe_txq_depth_set; int /*<<< orphan*/  tx_bcast; int /*<<< orphan*/  tx_bcast_set; int /*<<< orphan*/  rx_bcast; int /*<<< orphan*/  rx_bcast_set; int /*<<< orphan*/  fcoe_boot_progress; int /*<<< orphan*/  fcoe_boot_progress_set; int /*<<< orphan*/  link_failures; int /*<<< orphan*/  link_failures_set; int /*<<< orphan*/  fip_rx_descr_size; int /*<<< orphan*/  fip_rx_descr_size_set; int /*<<< orphan*/  fip_tx_descr_size; int /*<<< orphan*/  fip_tx_descr_size_set; int /*<<< orphan*/  port_state; int /*<<< orphan*/  port_state_set; int /*<<< orphan*/  port_alias; int /*<<< orphan*/  port_alias_set; int /*<<< orphan*/  qos_pri; int /*<<< orphan*/  qos_pri_set; int /*<<< orphan*/  switch_fw_version; int /*<<< orphan*/  switch_fw_version_set; int /*<<< orphan*/  switch_model; int /*<<< orphan*/  switch_model_set; int /*<<< orphan*/  vendor_name; int /*<<< orphan*/  vendor_name_set; int /*<<< orphan*/  switch_portid; int /*<<< orphan*/  switch_portid_set; int /*<<< orphan*/  switch_portnum; int /*<<< orphan*/  switch_portnum_set; int /*<<< orphan*/  switch_name; int /*<<< orphan*/  switch_name_set; int /*<<< orphan*/  num_npiv_ids; int /*<<< orphan*/  num_npiv_ids_set; int /*<<< orphan*/  npiv_state; int /*<<< orphan*/  npiv_state_set; int /*<<< orphan*/  boot_type; int /*<<< orphan*/  boot_type_set; int /*<<< orphan*/  cr_tov; int /*<<< orphan*/  cr_tov_set; int /*<<< orphan*/  ed_tov; int /*<<< orphan*/  ed_tov_set; int /*<<< orphan*/  ra_tov; int /*<<< orphan*/  ra_tov_set; int /*<<< orphan*/  rt_tov; int /*<<< orphan*/  rt_tov_set; int /*<<< orphan*/  scsi_timeout; int /*<<< orphan*/  scsi_timeout_set; } ;
struct ecore_drv_tlv_hdr {int tlv_type; } ;

/* Variables and functions */
#define  DRV_TLV_ABORT_TASK_SETS_ISSUED 276 
#define  DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID 275 
#define  DRV_TLV_ABTS_1_TIMESTAMP 274 
#define  DRV_TLV_ABTS_2_SENT_DESTINATION_FC_ID 273 
#define  DRV_TLV_ABTS_2_TIMESTAMP 272 
#define  DRV_TLV_ABTS_3_SENT_DESTINATION_FC_ID 271 
#define  DRV_TLV_ABTS_3_TIMESTAMP 270 
#define  DRV_TLV_ABTS_4_SENT_DESTINATION_FC_ID 269 
#define  DRV_TLV_ABTS_4_TIMESTAMP 268 
#define  DRV_TLV_ABTS_5_SENT_DESTINATION_FC_ID 267 
#define  DRV_TLV_ABTS_5_TIMESTAMP 266 
#define  DRV_TLV_ABTS_ACCS_RECEIVED 265 
#define  DRV_TLV_ABTS_RJTS_RECEIVED 264 
#define  DRV_TLV_ABTS_SENT_COUNT 263 
#define  DRV_TLV_ACCS_ISSUED 262 
#define  DRV_TLV_ACCS_RECEIVED 261 
#define  DRV_TLV_BOOT_TYPE 260 
#define  DRV_TLV_CODE_VIOLATION_ERROR_COUNT 259 
#define  DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID 258 
#define  DRV_TLV_CRC_ERROR_1_TIMESTAMP 257 
#define  DRV_TLV_CRC_ERROR_2_RECEIVED_SOURCE_FC_ID 256 
#define  DRV_TLV_CRC_ERROR_2_TIMESTAMP 255 
#define  DRV_TLV_CRC_ERROR_3_RECEIVED_SOURCE_FC_ID 254 
#define  DRV_TLV_CRC_ERROR_3_TIMESTAMP 253 
#define  DRV_TLV_CRC_ERROR_4_RECEIVED_SOURCE_FC_ID 252 
#define  DRV_TLV_CRC_ERROR_4_TIMESTAMP 251 
#define  DRV_TLV_CRC_ERROR_5_RECEIVED_SOURCE_FC_ID 250 
#define  DRV_TLV_CRC_ERROR_5_TIMESTAMP 249 
#define  DRV_TLV_CRC_ERROR_COUNT 248 
#define  DRV_TLV_CR_TOV 247 
#define  DRV_TLV_DISPARITY_ERROR_COUNT 246 
#define  DRV_TLV_EOFA_COUNT 245 
#define  DRV_TLV_EOFNI_COUNT 244 
#define  DRV_TLV_E_D_TOV 243 
#define  DRV_TLV_FCOE_BOOT_PROGRESS 242 
#define  DRV_TLV_FCOE_RX_BYTES_RECEIVED 241 
#define  DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_AVG_DEPTH 240 
#define  DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_SIZE 239 
#define  DRV_TLV_FCOE_RX_FRAMES_RECEIVED 238 
#define  DRV_TLV_FCOE_TX_BYTES_SENT 237 
#define  DRV_TLV_FCOE_TX_DESCRIPTOR_QUEUE_AVG_DEPTH 236 
#define  DRV_TLV_FCOE_TX_FRAMES_SENT 235 
#define  DRV_TLV_FDISCS_SENT_COUNT 234 
#define  DRV_TLV_FDISC_ACCS_RECEIVED 233 
#define  DRV_TLV_FDISC_RJTS_RECEIVED 232 
#define  DRV_TLV_FIP_TX_DESCRIPTORS_QUEUE_SIZE 231 
#define  DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1 230 
#define  DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_2 229 
#define  DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_3 228 
#define  DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_4 227 
#define  DRV_TLV_LAST_FLOGI_ACC_TIMESTAMP 226 
#define  DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1 225 
#define  DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_2 224 
#define  DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_3 223 
#define  DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_4 222 
#define  DRV_TLV_LAST_FLOGI_RJT 221 
#define  DRV_TLV_LAST_FLOGI_RJT_TIMESTAMP 220 
#define  DRV_TLV_LAST_FLOGI_TIMESTAMP 219 
#define  DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1 218 
#define  DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_2 217 
#define  DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_3 216 
#define  DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_4 215 
#define  DRV_TLV_LINK_FAILURE_COUNT 214 
#define  DRV_TLV_LIP_RECEIVED_COUNT 213 
#define  DRV_TLV_LIP_SENT_COUNT 212 
#define  DRV_TLV_LOGOS_ISSUED 211 
#define  DRV_TLV_LOGOS_RECEIVED 210 
#define  DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID 209 
#define  DRV_TLV_LOGO_1_TIMESTAMP 208 
#define  DRV_TLV_LOGO_2_RECEIVED_SOURCE_FC_ID 207 
#define  DRV_TLV_LOGO_2_TIMESTAMP 206 
#define  DRV_TLV_LOGO_3_RECEIVED_SOURCE_FC_ID 205 
#define  DRV_TLV_LOGO_3_TIMESTAMP 204 
#define  DRV_TLV_LOGO_4_RECEIVED_SOURCE_FC_ID 203 
#define  DRV_TLV_LOGO_4_TIMESTAMP 202 
#define  DRV_TLV_LOGO_5_RECEIVED_SOURCE_FC_ID 201 
#define  DRV_TLV_LOGO_5_TIMESTAMP 200 
#define  DRV_TLV_LOGO_ACCS_RECEIVED 199 
#define  DRV_TLV_LOGO_RJTS_RECEIVED 198 
#define  DRV_TLV_LOSS_OF_SIGNAL_ERRORS 197 
#define  DRV_TLV_LOSS_OF_SYNC_ERROR_COUNT 196 
#define  DRV_TLV_LRR_COUNT 195 
#define  DRV_TLV_LR_COUNT 194 
#define  DRV_TLV_LUN_RESETS_ISSUED 193 
#define  DRV_TLV_NOS_RECEIVED_COUNT 192 
#define  DRV_TLV_NOS_SENT_COUNT 191 
#define  DRV_TLV_NPIV_STATE 190 
#define  DRV_TLV_NUM_OF_NPIV_IDS 189 
#define  DRV_TLV_OLS_COUNT 188 
#define  DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID 187 
#define  DRV_TLV_PLOGI_1_ACC_TIMESTAMP 186 
#define  DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID 185 
#define  DRV_TLV_PLOGI_1_TIMESTAMP 184 
#define  DRV_TLV_PLOGI_2_ACC_RECEIVED_SOURCE_FC_ID 183 
#define  DRV_TLV_PLOGI_2_ACC_TIMESTAMP 182 
#define  DRV_TLV_PLOGI_2_SENT_DESTINATION_FC_ID 181 
#define  DRV_TLV_PLOGI_2_TIMESTAMP 180 
#define  DRV_TLV_PLOGI_3_ACC_RECEIVED_SOURCE_FC_ID 179 
#define  DRV_TLV_PLOGI_3_ACC_TIMESTAMP 178 
#define  DRV_TLV_PLOGI_3_SENT_DESTINATION_FC_ID 177 
#define  DRV_TLV_PLOGI_3_TIMESTAMP 176 
#define  DRV_TLV_PLOGI_4_ACC_RECEIVED_SOURCE_FC_ID 175 
#define  DRV_TLV_PLOGI_4_ACC_TIMESTAMP 174 
#define  DRV_TLV_PLOGI_4_SENT_DESTINATION_FC_ID 173 
#define  DRV_TLV_PLOGI_4_TIMESTAMP 172 
#define  DRV_TLV_PLOGI_5_ACC_RECEIVED_SOURCE_FC_ID 171 
#define  DRV_TLV_PLOGI_5_ACC_TIMESTAMP 170 
#define  DRV_TLV_PLOGI_5_SENT_DESTINATION_FC_ID 169 
#define  DRV_TLV_PLOGI_5_TIMESTAMP 168 
#define  DRV_TLV_PLOGI_ACCS_RECEIVED 167 
#define  DRV_TLV_PLOGI_RJTS_RECEIVED 166 
#define  DRV_TLV_PLOGI_SENT_COUNT 165 
#define  DRV_TLV_PORT_ALIAS 164 
#define  DRV_TLV_PORT_STATE 163 
#define  DRV_TLV_PRIMITIVE_SEQUENCE_PROTOCOL_ERROR_COUNT 162 
#define  DRV_TLV_PRLIS_ISSUED 161 
#define  DRV_TLV_QOS_PRIORITY_PER_802_1P 160 
#define  DRV_TLV_RSCNS_RECEIVED 159 
#define  DRV_TLV_RX_BROADCAST_PACKETS 158 
#define  DRV_TLV_R_A_TOV 157 
#define  DRV_TLV_R_T_TOV 156 
#define  DRV_TLV_SCSI_CHECK_1_TIMESTAMP 155 
#define  DRV_TLV_SCSI_CHECK_2_TIMESTAMP 154 
#define  DRV_TLV_SCSI_CHECK_3_TIMESTAMP 153 
#define  DRV_TLV_SCSI_CHECK_4_TIMESTAMP 152 
#define  DRV_TLV_SCSI_CHECK_5_TIMESTAMP 151 
#define  DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ 150 
#define  DRV_TLV_SCSI_CHECK_CONDITION_2_RECEIVED_SK_ASC_ASCQ 149 
#define  DRV_TLV_SCSI_CHECK_CONDITION_3_RECEIVED_SK_ASC_ASCQ 148 
#define  DRV_TLV_SCSI_CHECK_CONDITION_4_RECEIVED_SK_ASC_ASCQ 147 
#define  DRV_TLV_SCSI_CHECK_CONDITION_5_RECEIVED_SK_ASC_ASCQ 146 
#define  DRV_TLV_SCSI_STATUS_ACA_ACTIVE_COUNT 145 
#define  DRV_TLV_SCSI_STATUS_BUSY_COUNT 144 
#define  DRV_TLV_SCSI_STATUS_CHECK_CONDITION_COUNT 143 
#define  DRV_TLV_SCSI_STATUS_CONDITION_MET_COUNT 142 
#define  DRV_TLV_SCSI_STATUS_INTERMEDIATE_CONDITION_MET_COUNT 141 
#define  DRV_TLV_SCSI_STATUS_INTERMEDIATE_COUNT 140 
#define  DRV_TLV_SCSI_STATUS_RESERVATION_CONFLICT_COUNT 139 
#define  DRV_TLV_SCSI_STATUS_TASK_ABORTED_COUNT 138 
#define  DRV_TLV_SCSI_STATUS_TASK_SET_FULL_COUNT 137 
#define  DRV_TLV_SCSI_TO 136 
#define  DRV_TLV_SWITCH_FW_VER 135 
#define  DRV_TLV_SWITCH_MODEL 134 
#define  DRV_TLV_SWITCH_NAME 133 
#define  DRV_TLV_SWITCH_PORT_ID 132 
#define  DRV_TLV_SWITCH_PORT_NUM 131 
#define  DRV_TLV_TPRLOS_SENT 130 
#define  DRV_TLV_TX_BROADCAST_PACKETS 129 
#define  DRV_TLV_VENDOR_NAME 128 
 int ecore_mfw_get_tlv_time_value (int /*<<< orphan*/ *,struct ecore_tlv_parsed_buf*) ; 

__attribute__((used)) static int
ecore_mfw_get_fcoe_tlv_value(struct ecore_drv_tlv_hdr *p_tlv,
			     struct ecore_mfw_tlv_fcoe *p_drv_buf,
			     struct ecore_tlv_parsed_buf *p_buf)
{
	switch (p_tlv->tlv_type) {
	case DRV_TLV_SCSI_TO:
		if (p_drv_buf->scsi_timeout_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_timeout;
			return sizeof(p_drv_buf->scsi_timeout);
		}
		break;
	case DRV_TLV_R_T_TOV:
		if (p_drv_buf->rt_tov_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rt_tov;
			return sizeof(p_drv_buf->rt_tov);
		}
		break;
	case DRV_TLV_R_A_TOV:
		if (p_drv_buf->ra_tov_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->ra_tov;
			return sizeof(p_drv_buf->ra_tov);
		}
		break;
	case DRV_TLV_E_D_TOV:
		if (p_drv_buf->ed_tov_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->ed_tov;
			return sizeof(p_drv_buf->ed_tov);
		}
		break;
	case DRV_TLV_CR_TOV:
		if (p_drv_buf->cr_tov_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->cr_tov;
			return sizeof(p_drv_buf->cr_tov);
		}
		break;
	case DRV_TLV_BOOT_TYPE:
		if (p_drv_buf->boot_type_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->boot_type;
			return sizeof(p_drv_buf->boot_type);
		}
		break;
	case DRV_TLV_NPIV_STATE:
		if (p_drv_buf->npiv_state_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->npiv_state;
			return sizeof(p_drv_buf->npiv_state);
		}
		break;
	case DRV_TLV_NUM_OF_NPIV_IDS:
		if (p_drv_buf->num_npiv_ids_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->num_npiv_ids;
			return sizeof(p_drv_buf->num_npiv_ids);
		}
		break;
	case DRV_TLV_SWITCH_NAME:
		if (p_drv_buf->switch_name_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->switch_name;
			return sizeof(p_drv_buf->switch_name);
		}
		break;
	case DRV_TLV_SWITCH_PORT_NUM:
		if (p_drv_buf->switch_portnum_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->switch_portnum;
			return sizeof(p_drv_buf->switch_portnum);
		}
		break;
	case DRV_TLV_SWITCH_PORT_ID:
		if (p_drv_buf->switch_portid_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->switch_portid;
			return sizeof(p_drv_buf->switch_portid);
		}
		break;
	case DRV_TLV_VENDOR_NAME:
		if (p_drv_buf->vendor_name_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->vendor_name;
			return sizeof(p_drv_buf->vendor_name);
		}
		break;
	case DRV_TLV_SWITCH_MODEL:
		if (p_drv_buf->switch_model_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->switch_model;
			return sizeof(p_drv_buf->switch_model);
		}
		break;
	case DRV_TLV_SWITCH_FW_VER:
		if (p_drv_buf->switch_fw_version_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->switch_fw_version;
			return sizeof(p_drv_buf->switch_fw_version);
		}
		break;
	case DRV_TLV_QOS_PRIORITY_PER_802_1P:
		if (p_drv_buf->qos_pri_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->qos_pri;
			return sizeof(p_drv_buf->qos_pri);
		}
		break;
	case DRV_TLV_PORT_ALIAS:
		if (p_drv_buf->port_alias_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->port_alias;
			return sizeof(p_drv_buf->port_alias);
		}
		break;
	case DRV_TLV_PORT_STATE:
		if (p_drv_buf->port_state_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->port_state;
			return sizeof(p_drv_buf->port_state);
		}
		break;
	case DRV_TLV_FIP_TX_DESCRIPTORS_QUEUE_SIZE:
		if (p_drv_buf->fip_tx_descr_size_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fip_tx_descr_size;
			return sizeof(p_drv_buf->fip_tx_descr_size);
		}
		break;
	case DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_SIZE:
		if (p_drv_buf->fip_rx_descr_size_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fip_rx_descr_size;
			return sizeof(p_drv_buf->fip_rx_descr_size);
		}
		break;
	case DRV_TLV_LINK_FAILURE_COUNT:
		if (p_drv_buf->link_failures_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->link_failures;
			return sizeof(p_drv_buf->link_failures);
		}
		break;
	case DRV_TLV_FCOE_BOOT_PROGRESS:
		if (p_drv_buf->fcoe_boot_progress_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_boot_progress;
			return sizeof(p_drv_buf->fcoe_boot_progress);
		}
		break;
	case DRV_TLV_RX_BROADCAST_PACKETS:
		if (p_drv_buf->rx_bcast_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_bcast;
			return sizeof(p_drv_buf->rx_bcast);
		}
		break;
	case DRV_TLV_TX_BROADCAST_PACKETS:
		if (p_drv_buf->tx_bcast_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_bcast;
			return sizeof(p_drv_buf->tx_bcast);
		}
		break;
	case DRV_TLV_FCOE_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
		if (p_drv_buf->fcoe_txq_depth_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_txq_depth;
			return sizeof(p_drv_buf->fcoe_txq_depth);
		}
		break;
	case DRV_TLV_FCOE_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
		if (p_drv_buf->fcoe_rxq_depth_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_rxq_depth;
			return sizeof(p_drv_buf->fcoe_rxq_depth);
		}
		break;
	case DRV_TLV_FCOE_RX_FRAMES_RECEIVED:
		if (p_drv_buf->fcoe_rx_frames_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_rx_frames;
			return sizeof(p_drv_buf->fcoe_rx_frames);
		}
		break;
	case DRV_TLV_FCOE_RX_BYTES_RECEIVED:
		if (p_drv_buf->fcoe_rx_bytes_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_rx_bytes;
			return sizeof(p_drv_buf->fcoe_rx_bytes);
		}
		break;
	case DRV_TLV_FCOE_TX_FRAMES_SENT:
		if (p_drv_buf->fcoe_tx_frames_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_tx_frames;
			return sizeof(p_drv_buf->fcoe_tx_frames);
		}
		break;
	case DRV_TLV_FCOE_TX_BYTES_SENT:
		if (p_drv_buf->fcoe_tx_bytes_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fcoe_tx_bytes;
			return sizeof(p_drv_buf->fcoe_tx_bytes);
		}
		break;
	case DRV_TLV_CRC_ERROR_COUNT:
		if (p_drv_buf->crc_count_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->crc_count;
			return sizeof(p_drv_buf->crc_count);
		}
		break;
	case DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_CRC_ERROR_2_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_CRC_ERROR_3_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_CRC_ERROR_4_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_CRC_ERROR_5_RECEIVED_SOURCE_FC_ID:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_CRC_ERROR_1_RECEIVED_SOURCE_FC_ID) / 2;

		if (p_drv_buf->crc_err_src_fcid_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->crc_err_src_fcid[idx];
			return sizeof(p_drv_buf->crc_err_src_fcid[idx]);
		}
		break;
	}

	case DRV_TLV_CRC_ERROR_1_TIMESTAMP:
	case DRV_TLV_CRC_ERROR_2_TIMESTAMP:
	case DRV_TLV_CRC_ERROR_3_TIMESTAMP:
	case DRV_TLV_CRC_ERROR_4_TIMESTAMP:
	case DRV_TLV_CRC_ERROR_5_TIMESTAMP:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_CRC_ERROR_1_TIMESTAMP) / 2;

		return ecore_mfw_get_tlv_time_value(&p_drv_buf->crc_err[idx],
						    p_buf);
	}

	case DRV_TLV_LOSS_OF_SYNC_ERROR_COUNT:
		if (p_drv_buf->losync_err_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->losync_err;
			return sizeof(p_drv_buf->losync_err);
		}
		break;
	case DRV_TLV_LOSS_OF_SIGNAL_ERRORS:
		if (p_drv_buf->losig_err_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->losig_err;
			return sizeof(p_drv_buf->losig_err);
		}
		break;
	case DRV_TLV_PRIMITIVE_SEQUENCE_PROTOCOL_ERROR_COUNT:
		if (p_drv_buf->primtive_err_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->primtive_err;
			return sizeof(p_drv_buf->primtive_err);
		}
		break;
	case DRV_TLV_DISPARITY_ERROR_COUNT:
		if (p_drv_buf->disparity_err_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->disparity_err;
			return sizeof(p_drv_buf->disparity_err);
		}
		break;
	case DRV_TLV_CODE_VIOLATION_ERROR_COUNT:
		if (p_drv_buf->code_violation_err_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->code_violation_err;
			return sizeof(p_drv_buf->code_violation_err);
		}
		break;
	case DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1:
	case DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_2:
	case DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_3:
	case DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_4:
	{
		u8 idx = p_tlv->tlv_type -
			 DRV_TLV_LAST_FLOGI_ISSUED_COMMON_PARAMETERS_WORD_1;
		if (p_drv_buf->flogi_param_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->flogi_param[idx];
			return sizeof(p_drv_buf->flogi_param[idx]);
		}
		break;
	}
	case DRV_TLV_LAST_FLOGI_TIMESTAMP:
		return ecore_mfw_get_tlv_time_value(&p_drv_buf->flogi_tstamp,
						    p_buf);
	case DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1:
	case DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_2:
	case DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_3:
	case DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_4:
	{
		u8 idx = p_tlv->tlv_type -
			 DRV_TLV_LAST_FLOGI_ACC_COMMON_PARAMETERS_WORD_1;

		if (p_drv_buf->flogi_acc_param_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->flogi_acc_param[idx];
			return sizeof(p_drv_buf->flogi_acc_param[idx]);
		}
		break;
	}
	case DRV_TLV_LAST_FLOGI_ACC_TIMESTAMP:
		return ecore_mfw_get_tlv_time_value(&p_drv_buf->flogi_acc_tstamp,
						    p_buf);
	case DRV_TLV_LAST_FLOGI_RJT:
		if (p_drv_buf->flogi_rjt_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->flogi_rjt;
			return sizeof(p_drv_buf->flogi_rjt);
		}
		break;
	case DRV_TLV_LAST_FLOGI_RJT_TIMESTAMP:
		return ecore_mfw_get_tlv_time_value(&p_drv_buf->flogi_rjt_tstamp,
						    p_buf);
	case DRV_TLV_FDISCS_SENT_COUNT:
		if (p_drv_buf->fdiscs_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fdiscs;
			return sizeof(p_drv_buf->fdiscs);
		}
		break;
	case DRV_TLV_FDISC_ACCS_RECEIVED:
		if (p_drv_buf->fdisc_acc_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fdisc_acc;
			return sizeof(p_drv_buf->fdisc_acc);
		}
		break;
	case DRV_TLV_FDISC_RJTS_RECEIVED:
		if (p_drv_buf->fdisc_rjt_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->fdisc_rjt;
			return sizeof(p_drv_buf->fdisc_rjt);
		}
		break;
	case DRV_TLV_PLOGI_SENT_COUNT:
		if (p_drv_buf->plogi_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogi;
			return sizeof(p_drv_buf->plogi);
		}
		break;
	case DRV_TLV_PLOGI_ACCS_RECEIVED:
		if (p_drv_buf->plogi_acc_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogi_acc;
			return sizeof(p_drv_buf->plogi_acc);
		}
		break;
	case DRV_TLV_PLOGI_RJTS_RECEIVED:
		if (p_drv_buf->plogi_rjt_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogi_rjt;
			return sizeof(p_drv_buf->plogi_rjt);
		}
		break;
	case DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID:
	case DRV_TLV_PLOGI_2_SENT_DESTINATION_FC_ID:
	case DRV_TLV_PLOGI_3_SENT_DESTINATION_FC_ID:
	case DRV_TLV_PLOGI_4_SENT_DESTINATION_FC_ID:
	case DRV_TLV_PLOGI_5_SENT_DESTINATION_FC_ID:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_PLOGI_1_SENT_DESTINATION_FC_ID) / 2;

		if (p_drv_buf->plogi_dst_fcid_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogi_dst_fcid[idx];
			return sizeof(p_drv_buf->plogi_dst_fcid[idx]);
		}
		break;
	}
	case DRV_TLV_PLOGI_1_TIMESTAMP:
	case DRV_TLV_PLOGI_2_TIMESTAMP:
	case DRV_TLV_PLOGI_3_TIMESTAMP:
	case DRV_TLV_PLOGI_4_TIMESTAMP:
	case DRV_TLV_PLOGI_5_TIMESTAMP:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_PLOGI_1_TIMESTAMP) / 2;

		return ecore_mfw_get_tlv_time_value(&p_drv_buf->plogi_tstamp[idx],
						    p_buf);
	}

	case DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_PLOGI_2_ACC_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_PLOGI_3_ACC_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_PLOGI_4_ACC_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_PLOGI_5_ACC_RECEIVED_SOURCE_FC_ID:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_PLOGI_1_ACC_RECEIVED_SOURCE_FC_ID) / 2;

		if (p_drv_buf->plogi_acc_src_fcid_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogi_acc_src_fcid[idx];
			return sizeof(p_drv_buf->plogi_acc_src_fcid[idx]);
		}
		break;
	}
	case DRV_TLV_PLOGI_1_ACC_TIMESTAMP:
	case DRV_TLV_PLOGI_2_ACC_TIMESTAMP:
	case DRV_TLV_PLOGI_3_ACC_TIMESTAMP:
	case DRV_TLV_PLOGI_4_ACC_TIMESTAMP:
	case DRV_TLV_PLOGI_5_ACC_TIMESTAMP:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_PLOGI_1_ACC_TIMESTAMP) / 2;

		return ecore_mfw_get_tlv_time_value(&p_drv_buf->plogi_acc_tstamp[idx],
						    p_buf);
	}

	case DRV_TLV_LOGOS_ISSUED:
		if (p_drv_buf->tx_plogos_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_plogos;
			return sizeof(p_drv_buf->tx_plogos);
		}
		break;
	case DRV_TLV_LOGO_ACCS_RECEIVED:
		if (p_drv_buf->plogo_acc_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogo_acc;
			return sizeof(p_drv_buf->plogo_acc);
		}
		break;
	case DRV_TLV_LOGO_RJTS_RECEIVED:
		if (p_drv_buf->plogo_rjt_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogo_rjt;
			return sizeof(p_drv_buf->plogo_rjt);
		}
		break;
	case DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_LOGO_2_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_LOGO_3_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_LOGO_4_RECEIVED_SOURCE_FC_ID:
	case DRV_TLV_LOGO_5_RECEIVED_SOURCE_FC_ID:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_LOGO_1_RECEIVED_SOURCE_FC_ID) / 2;

		if (p_drv_buf->plogo_src_fcid_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->plogo_src_fcid[idx];
			return sizeof(p_drv_buf->plogo_src_fcid[idx]);
		}
		break;
	}
	case DRV_TLV_LOGO_1_TIMESTAMP:
	case DRV_TLV_LOGO_2_TIMESTAMP:
	case DRV_TLV_LOGO_3_TIMESTAMP:
	case DRV_TLV_LOGO_4_TIMESTAMP:
	case DRV_TLV_LOGO_5_TIMESTAMP:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_LOGO_1_TIMESTAMP) / 2;

		return ecore_mfw_get_tlv_time_value(&p_drv_buf->plogo_tstamp[idx],
						    p_buf);
	}
	case DRV_TLV_LOGOS_RECEIVED:
		if (p_drv_buf->rx_logos_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_logos;
			return sizeof(p_drv_buf->rx_logos);
		}
		break;
	case DRV_TLV_ACCS_ISSUED:
		if (p_drv_buf->tx_accs_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_accs;
			return sizeof(p_drv_buf->tx_accs);
		}
		break;
	case DRV_TLV_PRLIS_ISSUED:
		if (p_drv_buf->tx_prlis_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_prlis;
			return sizeof(p_drv_buf->tx_prlis);
		}
		break;
	case DRV_TLV_ACCS_RECEIVED:
		if (p_drv_buf->rx_accs_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_accs;
			return sizeof(p_drv_buf->rx_accs);
		}
		break;
	case DRV_TLV_ABTS_SENT_COUNT:
		if (p_drv_buf->tx_abts_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_abts;
			return sizeof(p_drv_buf->tx_abts);
		}
		break;
	case DRV_TLV_ABTS_ACCS_RECEIVED:
		if (p_drv_buf->rx_abts_acc_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_abts_acc;
			return sizeof(p_drv_buf->rx_abts_acc);
		}
		break;
	case DRV_TLV_ABTS_RJTS_RECEIVED:
		if (p_drv_buf->rx_abts_rjt_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_abts_rjt;
			return sizeof(p_drv_buf->rx_abts_rjt);
		}
		break;
	case DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID:
	case DRV_TLV_ABTS_2_SENT_DESTINATION_FC_ID:
	case DRV_TLV_ABTS_3_SENT_DESTINATION_FC_ID:
	case DRV_TLV_ABTS_4_SENT_DESTINATION_FC_ID:
	case DRV_TLV_ABTS_5_SENT_DESTINATION_FC_ID:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_ABTS_1_SENT_DESTINATION_FC_ID) / 2;

		if (p_drv_buf->abts_dst_fcid_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->abts_dst_fcid[idx];
			return sizeof(p_drv_buf->abts_dst_fcid[idx]);
		}
		break;
	}
	case DRV_TLV_ABTS_1_TIMESTAMP:
	case DRV_TLV_ABTS_2_TIMESTAMP:
	case DRV_TLV_ABTS_3_TIMESTAMP:
	case DRV_TLV_ABTS_4_TIMESTAMP:
	case DRV_TLV_ABTS_5_TIMESTAMP:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_ABTS_1_TIMESTAMP) / 2;

		return ecore_mfw_get_tlv_time_value(&p_drv_buf->abts_tstamp[idx],
						    p_buf);
	}

	case DRV_TLV_RSCNS_RECEIVED:
		if (p_drv_buf->rx_rscn_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_rscn;
			return sizeof(p_drv_buf->rx_rscn);
		}
		break;
	case DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1:
	case DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_2:
	case DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_3:
	case DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_4:
	{
		u8 idx = p_tlv->tlv_type - DRV_TLV_LAST_RSCN_RECEIVED_N_PORT_1;

		if (p_drv_buf->rx_rscn_nport_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_rscn_nport[idx];
			return sizeof(p_drv_buf->rx_rscn_nport[idx]);
		}
		break;
	}
	case DRV_TLV_LUN_RESETS_ISSUED:
		if (p_drv_buf->tx_lun_rst_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_lun_rst;
			return sizeof(p_drv_buf->tx_lun_rst);
		}
		break;
	case DRV_TLV_ABORT_TASK_SETS_ISSUED:
		if (p_drv_buf->abort_task_sets_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->abort_task_sets;
			return sizeof(p_drv_buf->abort_task_sets);
		}
		break;
	case DRV_TLV_TPRLOS_SENT:
		if (p_drv_buf->tx_tprlos_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_tprlos;
			return sizeof(p_drv_buf->tx_tprlos);
		}
		break;
	case DRV_TLV_NOS_SENT_COUNT:
		if (p_drv_buf->tx_nos_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_nos;
			return sizeof(p_drv_buf->tx_nos);
		}
		break;
	case DRV_TLV_NOS_RECEIVED_COUNT:
		if (p_drv_buf->rx_nos_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_nos;
			return sizeof(p_drv_buf->rx_nos);
		}
		break;
	case DRV_TLV_OLS_COUNT:
		if (p_drv_buf->ols_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->ols;
			return sizeof(p_drv_buf->ols);
		}
		break;
	case DRV_TLV_LR_COUNT:
		if (p_drv_buf->lr_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->lr;
			return sizeof(p_drv_buf->lr);
		}
		break;
	case DRV_TLV_LRR_COUNT:
		if (p_drv_buf->lrr_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->lrr;
			return sizeof(p_drv_buf->lrr);
		}
		break;
	case DRV_TLV_LIP_SENT_COUNT:
		if (p_drv_buf->tx_lip_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->tx_lip;
			return sizeof(p_drv_buf->tx_lip);
		}
		break;
	case DRV_TLV_LIP_RECEIVED_COUNT:
		if (p_drv_buf->rx_lip_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->rx_lip;
			return sizeof(p_drv_buf->rx_lip);
		}
		break;
	case DRV_TLV_EOFA_COUNT:
		if (p_drv_buf->eofa_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->eofa;
			return sizeof(p_drv_buf->eofa);
		}
		break;
	case DRV_TLV_EOFNI_COUNT:
		if (p_drv_buf->eofni_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->eofni;
			return sizeof(p_drv_buf->eofni);
		}
		break;
	case DRV_TLV_SCSI_STATUS_CHECK_CONDITION_COUNT:
		if (p_drv_buf->scsi_chks_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_chks;
			return sizeof(p_drv_buf->scsi_chks);
		}
		break;
	case DRV_TLV_SCSI_STATUS_CONDITION_MET_COUNT:
		if (p_drv_buf->scsi_cond_met_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_cond_met;
			return sizeof(p_drv_buf->scsi_cond_met);
		}
		break;
	case DRV_TLV_SCSI_STATUS_BUSY_COUNT:
		if (p_drv_buf->scsi_busy_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_busy;
			return sizeof(p_drv_buf->scsi_busy);
		}
		break;
	case DRV_TLV_SCSI_STATUS_INTERMEDIATE_COUNT:
		if (p_drv_buf->scsi_inter_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_inter;
			return sizeof(p_drv_buf->scsi_inter);
		}
		break;
	case DRV_TLV_SCSI_STATUS_INTERMEDIATE_CONDITION_MET_COUNT:
		if (p_drv_buf->scsi_inter_cond_met_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_inter_cond_met;
			return sizeof(p_drv_buf->scsi_inter_cond_met);
		}
		break;
	case DRV_TLV_SCSI_STATUS_RESERVATION_CONFLICT_COUNT:
		if (p_drv_buf->scsi_rsv_conflicts_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_rsv_conflicts;
			return sizeof(p_drv_buf->scsi_rsv_conflicts);
		}
		break;
	case DRV_TLV_SCSI_STATUS_TASK_SET_FULL_COUNT:
		if (p_drv_buf->scsi_tsk_full_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_tsk_full;
			return sizeof(p_drv_buf->scsi_tsk_full);
		}
		break;
	case DRV_TLV_SCSI_STATUS_ACA_ACTIVE_COUNT:
		if (p_drv_buf->scsi_aca_active_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_aca_active;
			return sizeof(p_drv_buf->scsi_aca_active);
		}
		break;
	case DRV_TLV_SCSI_STATUS_TASK_ABORTED_COUNT:
		if (p_drv_buf->scsi_tsk_abort_set) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_tsk_abort;
			return sizeof(p_drv_buf->scsi_tsk_abort);
		}
		break;
	case DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ:
	case DRV_TLV_SCSI_CHECK_CONDITION_2_RECEIVED_SK_ASC_ASCQ:
	case DRV_TLV_SCSI_CHECK_CONDITION_3_RECEIVED_SK_ASC_ASCQ:
	case DRV_TLV_SCSI_CHECK_CONDITION_4_RECEIVED_SK_ASC_ASCQ:
	case DRV_TLV_SCSI_CHECK_CONDITION_5_RECEIVED_SK_ASC_ASCQ:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_SCSI_CHECK_CONDITION_1_RECEIVED_SK_ASC_ASCQ) / 2;

		if (p_drv_buf->scsi_rx_chk_set[idx]) {
			p_buf->p_val = (u8 *)&p_drv_buf->scsi_rx_chk[idx];
			return sizeof(p_drv_buf->scsi_rx_chk[idx]);
		}
		break;
	}
	case DRV_TLV_SCSI_CHECK_1_TIMESTAMP:
	case DRV_TLV_SCSI_CHECK_2_TIMESTAMP:
	case DRV_TLV_SCSI_CHECK_3_TIMESTAMP:
	case DRV_TLV_SCSI_CHECK_4_TIMESTAMP:
	case DRV_TLV_SCSI_CHECK_5_TIMESTAMP:
	{
		u8 idx = (p_tlv->tlv_type -
			  DRV_TLV_SCSI_CHECK_1_TIMESTAMP) / 2;

		return ecore_mfw_get_tlv_time_value(&p_drv_buf->scsi_chk_tstamp[idx],
						    p_buf);
	}

	default:
		break;
	}

	return -1;
}