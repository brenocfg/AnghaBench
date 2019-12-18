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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_info {size_t mfw_mb_length; scalar_t__* mfw_mb_cur; scalar_t__* mfw_mb_shadow; scalar_t__ mfw_mb_addr; } ;
struct ecore_hwfn {TYPE_1__* p_dcbx_info; struct ecore_mcp_info* mcp_info; } ;
struct ecore_dcbx_set {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  set; } ;
typedef  int /*<<< orphan*/  OSAL_BE32 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_DCBX_OPERATIONAL_MIB ; 
 int /*<<< orphan*/  ECORE_DCBX_REMOTE_LLDP_MIB ; 
 int /*<<< orphan*/  ECORE_DCBX_REMOTE_MIB ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_LINK ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
#define  MFW_DRV_MSG_BW_UPDATE 145 
#define  MFW_DRV_MSG_CRITICAL_ERROR_OCCURRED 144 
#define  MFW_DRV_MSG_DCBX_OPERATIONAL_MIB_UPDATED 143 
#define  MFW_DRV_MSG_DCBX_REMOTE_MIB_UPDATED 142 
#define  MFW_DRV_MSG_ERROR_RECOVERY 141 
#define  MFW_DRV_MSG_FAILURE_DETECTED 140 
#define  MFW_DRV_MSG_GET_FCOE_STATS 139 
#define  MFW_DRV_MSG_GET_ISCSI_STATS 138 
#define  MFW_DRV_MSG_GET_LAN_STATS 137 
#define  MFW_DRV_MSG_GET_RDMA_STATS 136 
#define  MFW_DRV_MSG_GET_TLV_REQ 135 
#define  MFW_DRV_MSG_LINK_CHANGE 134 
#define  MFW_DRV_MSG_LLDP_DATA_UPDATED 133 
#define  MFW_DRV_MSG_LLDP_RECEIVED_TLVS_UPDATED 132 
 int MFW_DRV_MSG_MAX_DWORDS (size_t) ; 
#define  MFW_DRV_MSG_OEM_CFG_UPDATE 131 
#define  MFW_DRV_MSG_S_TAG_UPDATE 130 
#define  MFW_DRV_MSG_TRANSCEIVER_STATE_CHANGE 129 
#define  MFW_DRV_MSG_VF_DISABLED 128 
 int /*<<< orphan*/  OSAL_CPU_TO_BE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  OSAL_MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_MFW_TLV_REQ (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_dcbx_mib_update_event (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_lldp_mib_update_event (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_critical_error (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_fan_failure (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_link_change (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 int /*<<< orphan*/  ecore_mcp_handle_process_kill (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_transceiver_change (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_ufp_event (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_vf_flr (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_read_mb (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_send_protocol_stats (struct ecore_hwfn*,struct ecore_ptt*,size_t) ; 
 int /*<<< orphan*/  ecore_mcp_update_bw (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_update_stag (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_mcp_handle_events(struct ecore_hwfn *p_hwfn,
					     struct ecore_ptt *p_ptt)
{
	struct ecore_mcp_info *info = p_hwfn->mcp_info;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	bool found = false;
	u16 i;

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP, "Received message from MFW\n");

	/* Read Messages from MFW */
	ecore_mcp_read_mb(p_hwfn, p_ptt);

	/* Compare current messages to old ones */
	for (i = 0; i < info->mfw_mb_length; i++) {
		if (info->mfw_mb_cur[i] == info->mfw_mb_shadow[i])
			continue;

		found = true;

		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
			   "Msg [%d] - old CMD 0x%02x, new CMD 0x%02x\n",
			   i, info->mfw_mb_shadow[i], info->mfw_mb_cur[i]);

		switch (i) {
		case MFW_DRV_MSG_LINK_CHANGE:
			ecore_mcp_handle_link_change(p_hwfn, p_ptt, false);
			break;
		case MFW_DRV_MSG_VF_DISABLED:
			ecore_mcp_handle_vf_flr(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_LLDP_DATA_UPDATED:
			ecore_dcbx_mib_update_event(p_hwfn, p_ptt,
						    ECORE_DCBX_REMOTE_LLDP_MIB);
			break;
		case MFW_DRV_MSG_DCBX_REMOTE_MIB_UPDATED:
			ecore_dcbx_mib_update_event(p_hwfn, p_ptt,
						    ECORE_DCBX_REMOTE_MIB);
			break;
		case MFW_DRV_MSG_DCBX_OPERATIONAL_MIB_UPDATED:
			ecore_dcbx_mib_update_event(p_hwfn, p_ptt,
						    ECORE_DCBX_OPERATIONAL_MIB);
			/* clear the user-config cache */
			OSAL_MEMSET(&p_hwfn->p_dcbx_info->set, 0,
				    sizeof(struct ecore_dcbx_set));
			break;
		case MFW_DRV_MSG_LLDP_RECEIVED_TLVS_UPDATED:
			ecore_lldp_mib_update_event(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_OEM_CFG_UPDATE:
			ecore_mcp_handle_ufp_event(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_TRANSCEIVER_STATE_CHANGE:
			ecore_mcp_handle_transceiver_change(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_ERROR_RECOVERY:
			ecore_mcp_handle_process_kill(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_GET_LAN_STATS:
		case MFW_DRV_MSG_GET_FCOE_STATS:
		case MFW_DRV_MSG_GET_ISCSI_STATS:
		case MFW_DRV_MSG_GET_RDMA_STATS:
			ecore_mcp_send_protocol_stats(p_hwfn, p_ptt, i);
			break;
		case MFW_DRV_MSG_BW_UPDATE:
			ecore_mcp_update_bw(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_S_TAG_UPDATE:
			ecore_mcp_update_stag(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_FAILURE_DETECTED:
			ecore_mcp_handle_fan_failure(p_hwfn);
			break;
		case MFW_DRV_MSG_CRITICAL_ERROR_OCCURRED:
			ecore_mcp_handle_critical_error(p_hwfn, p_ptt);
			break;
		case MFW_DRV_MSG_GET_TLV_REQ:
			OSAL_MFW_TLV_REQ(p_hwfn);
			break;
		default:
			DP_INFO(p_hwfn, "Unimplemented MFW message %d\n", i);
			rc = ECORE_INVAL;
		}
	}

	/* ACK everything */
	for (i = 0; i < MFW_DRV_MSG_MAX_DWORDS(info->mfw_mb_length); i++) {
		OSAL_BE32 val = OSAL_CPU_TO_BE32(((u32 *)info->mfw_mb_cur)[i]);

		/* MFW expect answer in BE, so we force write in that format */
		ecore_wr(p_hwfn, p_ptt,
			 info->mfw_mb_addr + sizeof(u32) +
			 MFW_DRV_MSG_MAX_DWORDS(info->mfw_mb_length) *
			 sizeof(u32) + i * sizeof(u32), val);
	}

	if (!found) {
		DP_INFO(p_hwfn,
			"Received an MFW message indication but no new message!\n");
		rc = ECORE_INVAL;
	}

	/* Copy the new mfw messages into the shadow */
	OSAL_MEMCPY(info->mfw_mb_shadow, info->mfw_mb_cur, info->mfw_mb_length);

	return rc;
}