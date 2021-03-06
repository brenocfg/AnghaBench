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
struct i40e_hw {char const* err_str; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
#define  I40E_ERR_ADAPTER_STOPPED 194 
#define  I40E_ERR_ADMIN_QUEUE_CRITICAL_ERROR 193 
#define  I40E_ERR_ADMIN_QUEUE_ERROR 192 
#define  I40E_ERR_ADMIN_QUEUE_FULL 191 
#define  I40E_ERR_ADMIN_QUEUE_NO_WORK 190 
#define  I40E_ERR_ADMIN_QUEUE_TIMEOUT 189 
#define  I40E_ERR_AUTONEG_NOT_COMPLETE 188 
#define  I40E_ERR_BACKING_PAGE_ERROR 187 
#define  I40E_ERR_BAD_IWARP_CQE 186 
#define  I40E_ERR_BAD_PTR 185 
#define  I40E_ERR_BUF_TOO_SHORT 184 
#define  I40E_ERR_CONFIG 183 
#define  I40E_ERR_CQP_COMPL_ERROR 182 
#define  I40E_ERR_DEVICE_NOT_SUPPORTED 181 
#define  I40E_ERR_DIAG_TEST_FAILED 180 
#define  I40E_ERR_FIRMWARE_API_VERSION 179 
#define  I40E_ERR_FLUSHED_QUEUE 178 
#define  I40E_ERR_INVALID_AEQ_ID 177 
#define  I40E_ERR_INVALID_ALIGNMENT 176 
#define  I40E_ERR_INVALID_ARP_INDEX 175 
#define  I40E_ERR_INVALID_CEQ_ID 174 
#define  I40E_ERR_INVALID_CQ_ID 173 
#define  I40E_ERR_INVALID_FPM_FUNC_ID 172 
#define  I40E_ERR_INVALID_FRAG_COUNT 171 
#define  I40E_ERR_INVALID_HMCFN_ID 170 
#define  I40E_ERR_INVALID_HMC_OBJ_COUNT 169 
#define  I40E_ERR_INVALID_HMC_OBJ_INDEX 168 
#define  I40E_ERR_INVALID_IMM_DATA_SIZE 167 
#define  I40E_ERR_INVALID_LINK_SETTINGS 166 
#define  I40E_ERR_INVALID_MAC_ADDR 165 
#define  I40E_ERR_INVALID_PAGE_DESC_INDEX 164 
#define  I40E_ERR_INVALID_PBLE_INDEX 163 
#define  I40E_ERR_INVALID_PD_ID 162 
#define  I40E_ERR_INVALID_PUSH_PAGE_INDEX 161 
#define  I40E_ERR_INVALID_QP_ID 160 
#define  I40E_ERR_INVALID_SD_INDEX 159 
#define  I40E_ERR_INVALID_SD_TYPE 158 
#define  I40E_ERR_INVALID_SIZE 157 
#define  I40E_ERR_INVALID_SRQ_ARM_LIMIT 156 
#define  I40E_ERR_INVALID_VF_ID 155 
#define  I40E_ERR_LINK_SETUP 154 
#define  I40E_ERR_MAC_TYPE 153 
#define  I40E_ERR_MASTER_REQUESTS_PENDING 152 
#define  I40E_ERR_MEMCPY_FAILED 151 
#define  I40E_ERR_NOT_IMPLEMENTED 150 
#define  I40E_ERR_NOT_READY 149 
#define  I40E_ERR_NO_AVAILABLE_VSI 148 
#define  I40E_ERR_NO_MEMORY 147 
#define  I40E_ERR_NO_PBLCHUNKS_AVAILABLE 146 
#define  I40E_ERR_NVM 145 
#define  I40E_ERR_NVM_BLANK_MODE 144 
#define  I40E_ERR_NVM_CHECKSUM 143 
#define  I40E_ERR_OPCODE_MISMATCH 142 
#define  I40E_ERR_PARAM 141 
#define  I40E_ERR_PE_DOORBELL_NOT_ENABLED 140 
#define  I40E_ERR_PHY 139 
#define  I40E_ERR_QP_INVALID_MSG_SIZE 138 
#define  I40E_ERR_QP_TOOMANY_WRS_POSTED 137 
#define  I40E_ERR_QUEUE_EMPTY 136 
#define  I40E_ERR_RESET_FAILED 135 
#define  I40E_ERR_RING_FULL 134 
#define  I40E_ERR_SRQ_ENABLED 133 
#define  I40E_ERR_SWFW_SYNC 132 
#define  I40E_ERR_TIMEOUT 131 
#define  I40E_ERR_UNKNOWN_PHY 130 
#define  I40E_NOT_SUPPORTED 129 
#define  I40E_SUCCESS 128 
 int /*<<< orphan*/  snprintf (char const*,int,char*,int) ; 

const char *i40e_stat_str(struct i40e_hw *hw, enum i40e_status_code stat_err)
{
	switch (stat_err) {
	case I40E_SUCCESS:
		return "OK";
	case I40E_ERR_NVM:
		return "I40E_ERR_NVM";
	case I40E_ERR_NVM_CHECKSUM:
		return "I40E_ERR_NVM_CHECKSUM";
	case I40E_ERR_PHY:
		return "I40E_ERR_PHY";
	case I40E_ERR_CONFIG:
		return "I40E_ERR_CONFIG";
	case I40E_ERR_PARAM:
		return "I40E_ERR_PARAM";
	case I40E_ERR_MAC_TYPE:
		return "I40E_ERR_MAC_TYPE";
	case I40E_ERR_UNKNOWN_PHY:
		return "I40E_ERR_UNKNOWN_PHY";
	case I40E_ERR_LINK_SETUP:
		return "I40E_ERR_LINK_SETUP";
	case I40E_ERR_ADAPTER_STOPPED:
		return "I40E_ERR_ADAPTER_STOPPED";
	case I40E_ERR_INVALID_MAC_ADDR:
		return "I40E_ERR_INVALID_MAC_ADDR";
	case I40E_ERR_DEVICE_NOT_SUPPORTED:
		return "I40E_ERR_DEVICE_NOT_SUPPORTED";
	case I40E_ERR_MASTER_REQUESTS_PENDING:
		return "I40E_ERR_MASTER_REQUESTS_PENDING";
	case I40E_ERR_INVALID_LINK_SETTINGS:
		return "I40E_ERR_INVALID_LINK_SETTINGS";
	case I40E_ERR_AUTONEG_NOT_COMPLETE:
		return "I40E_ERR_AUTONEG_NOT_COMPLETE";
	case I40E_ERR_RESET_FAILED:
		return "I40E_ERR_RESET_FAILED";
	case I40E_ERR_SWFW_SYNC:
		return "I40E_ERR_SWFW_SYNC";
	case I40E_ERR_NO_AVAILABLE_VSI:
		return "I40E_ERR_NO_AVAILABLE_VSI";
	case I40E_ERR_NO_MEMORY:
		return "I40E_ERR_NO_MEMORY";
	case I40E_ERR_BAD_PTR:
		return "I40E_ERR_BAD_PTR";
	case I40E_ERR_RING_FULL:
		return "I40E_ERR_RING_FULL";
	case I40E_ERR_INVALID_PD_ID:
		return "I40E_ERR_INVALID_PD_ID";
	case I40E_ERR_INVALID_QP_ID:
		return "I40E_ERR_INVALID_QP_ID";
	case I40E_ERR_INVALID_CQ_ID:
		return "I40E_ERR_INVALID_CQ_ID";
	case I40E_ERR_INVALID_CEQ_ID:
		return "I40E_ERR_INVALID_CEQ_ID";
	case I40E_ERR_INVALID_AEQ_ID:
		return "I40E_ERR_INVALID_AEQ_ID";
	case I40E_ERR_INVALID_SIZE:
		return "I40E_ERR_INVALID_SIZE";
	case I40E_ERR_INVALID_ARP_INDEX:
		return "I40E_ERR_INVALID_ARP_INDEX";
	case I40E_ERR_INVALID_FPM_FUNC_ID:
		return "I40E_ERR_INVALID_FPM_FUNC_ID";
	case I40E_ERR_QP_INVALID_MSG_SIZE:
		return "I40E_ERR_QP_INVALID_MSG_SIZE";
	case I40E_ERR_QP_TOOMANY_WRS_POSTED:
		return "I40E_ERR_QP_TOOMANY_WRS_POSTED";
	case I40E_ERR_INVALID_FRAG_COUNT:
		return "I40E_ERR_INVALID_FRAG_COUNT";
	case I40E_ERR_QUEUE_EMPTY:
		return "I40E_ERR_QUEUE_EMPTY";
	case I40E_ERR_INVALID_ALIGNMENT:
		return "I40E_ERR_INVALID_ALIGNMENT";
	case I40E_ERR_FLUSHED_QUEUE:
		return "I40E_ERR_FLUSHED_QUEUE";
	case I40E_ERR_INVALID_PUSH_PAGE_INDEX:
		return "I40E_ERR_INVALID_PUSH_PAGE_INDEX";
	case I40E_ERR_INVALID_IMM_DATA_SIZE:
		return "I40E_ERR_INVALID_IMM_DATA_SIZE";
	case I40E_ERR_TIMEOUT:
		return "I40E_ERR_TIMEOUT";
	case I40E_ERR_OPCODE_MISMATCH:
		return "I40E_ERR_OPCODE_MISMATCH";
	case I40E_ERR_CQP_COMPL_ERROR:
		return "I40E_ERR_CQP_COMPL_ERROR";
	case I40E_ERR_INVALID_VF_ID:
		return "I40E_ERR_INVALID_VF_ID";
	case I40E_ERR_INVALID_HMCFN_ID:
		return "I40E_ERR_INVALID_HMCFN_ID";
	case I40E_ERR_BACKING_PAGE_ERROR:
		return "I40E_ERR_BACKING_PAGE_ERROR";
	case I40E_ERR_NO_PBLCHUNKS_AVAILABLE:
		return "I40E_ERR_NO_PBLCHUNKS_AVAILABLE";
	case I40E_ERR_INVALID_PBLE_INDEX:
		return "I40E_ERR_INVALID_PBLE_INDEX";
	case I40E_ERR_INVALID_SD_INDEX:
		return "I40E_ERR_INVALID_SD_INDEX";
	case I40E_ERR_INVALID_PAGE_DESC_INDEX:
		return "I40E_ERR_INVALID_PAGE_DESC_INDEX";
	case I40E_ERR_INVALID_SD_TYPE:
		return "I40E_ERR_INVALID_SD_TYPE";
	case I40E_ERR_MEMCPY_FAILED:
		return "I40E_ERR_MEMCPY_FAILED";
	case I40E_ERR_INVALID_HMC_OBJ_INDEX:
		return "I40E_ERR_INVALID_HMC_OBJ_INDEX";
	case I40E_ERR_INVALID_HMC_OBJ_COUNT:
		return "I40E_ERR_INVALID_HMC_OBJ_COUNT";
	case I40E_ERR_INVALID_SRQ_ARM_LIMIT:
		return "I40E_ERR_INVALID_SRQ_ARM_LIMIT";
	case I40E_ERR_SRQ_ENABLED:
		return "I40E_ERR_SRQ_ENABLED";
	case I40E_ERR_ADMIN_QUEUE_ERROR:
		return "I40E_ERR_ADMIN_QUEUE_ERROR";
	case I40E_ERR_ADMIN_QUEUE_TIMEOUT:
		return "I40E_ERR_ADMIN_QUEUE_TIMEOUT";
	case I40E_ERR_BUF_TOO_SHORT:
		return "I40E_ERR_BUF_TOO_SHORT";
	case I40E_ERR_ADMIN_QUEUE_FULL:
		return "I40E_ERR_ADMIN_QUEUE_FULL";
	case I40E_ERR_ADMIN_QUEUE_NO_WORK:
		return "I40E_ERR_ADMIN_QUEUE_NO_WORK";
	case I40E_ERR_BAD_IWARP_CQE:
		return "I40E_ERR_BAD_IWARP_CQE";
	case I40E_ERR_NVM_BLANK_MODE:
		return "I40E_ERR_NVM_BLANK_MODE";
	case I40E_ERR_NOT_IMPLEMENTED:
		return "I40E_ERR_NOT_IMPLEMENTED";
	case I40E_ERR_PE_DOORBELL_NOT_ENABLED:
		return "I40E_ERR_PE_DOORBELL_NOT_ENABLED";
	case I40E_ERR_DIAG_TEST_FAILED:
		return "I40E_ERR_DIAG_TEST_FAILED";
	case I40E_ERR_NOT_READY:
		return "I40E_ERR_NOT_READY";
	case I40E_NOT_SUPPORTED:
		return "I40E_NOT_SUPPORTED";
	case I40E_ERR_FIRMWARE_API_VERSION:
		return "I40E_ERR_FIRMWARE_API_VERSION";
	case I40E_ERR_ADMIN_QUEUE_CRITICAL_ERROR:
		return "I40E_ERR_ADMIN_QUEUE_CRITICAL_ERROR";
	}

	snprintf(hw->err_str, sizeof(hw->err_str), "%d", stat_err);
	return hw->err_str;
}