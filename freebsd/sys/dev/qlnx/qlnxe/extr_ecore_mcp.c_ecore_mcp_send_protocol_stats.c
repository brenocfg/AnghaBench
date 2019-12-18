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
typedef  union ecore_mcp_protocol_stats {int dummy; } ecore_mcp_protocol_stats ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int data_src_size; union ecore_mcp_protocol_stats* p_data_src; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum ecore_mcp_protocol_type { ____Placeholder_ecore_mcp_protocol_type } ecore_mcp_protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  enum MFW_DRV_MSG_TYPE { ____Placeholder_MFW_DRV_MSG_TYPE } MFW_DRV_MSG_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_GET_STATS ; 
 int /*<<< orphan*/  DRV_MSG_CODE_STATS_TYPE_FCOE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_STATS_TYPE_ISCSI ; 
 int /*<<< orphan*/  DRV_MSG_CODE_STATS_TYPE_LAN ; 
 int /*<<< orphan*/  DRV_MSG_CODE_STATS_TYPE_RDMA ; 
 int ECORE_MCP_FCOE_STATS ; 
 int ECORE_MCP_ISCSI_STATS ; 
 int ECORE_MCP_LAN_STATS ; 
 int ECORE_MCP_RDMA_STATS ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
#define  MFW_DRV_MSG_GET_FCOE_STATS 131 
#define  MFW_DRV_MSG_GET_ISCSI_STATS 130 
#define  MFW_DRV_MSG_GET_LAN_STATS 129 
#define  MFW_DRV_MSG_GET_RDMA_STATS 128 
 int /*<<< orphan*/  OSAL_GET_PROTOCOL_STATS (int /*<<< orphan*/ ,int,union ecore_mcp_protocol_stats*) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mcp_mb_params*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 

__attribute__((used)) static void ecore_mcp_send_protocol_stats(struct ecore_hwfn *p_hwfn,
					  struct ecore_ptt *p_ptt,
					  enum MFW_DRV_MSG_TYPE type)
{
	enum ecore_mcp_protocol_type stats_type;
	union ecore_mcp_protocol_stats stats;
	struct ecore_mcp_mb_params mb_params;
	u32 hsi_param;
	enum _ecore_status_t rc;

	switch (type) {
	case MFW_DRV_MSG_GET_LAN_STATS:
		stats_type = ECORE_MCP_LAN_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_LAN;
		break;
	case MFW_DRV_MSG_GET_FCOE_STATS:
		stats_type = ECORE_MCP_FCOE_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_FCOE;
		break;
	case MFW_DRV_MSG_GET_ISCSI_STATS:
		stats_type = ECORE_MCP_ISCSI_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_ISCSI;
		break;
	case MFW_DRV_MSG_GET_RDMA_STATS:
		stats_type = ECORE_MCP_RDMA_STATS;
		hsi_param = DRV_MSG_CODE_STATS_TYPE_RDMA;
		break;
	default:
		DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
			   "Invalid protocol type %d\n", type);
		return;
	}

	OSAL_GET_PROTOCOL_STATS(p_hwfn->p_dev, stats_type, &stats);

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_GET_STATS;
	mb_params.param = hsi_param;
	mb_params.p_data_src = &stats;
	mb_params.data_src_size = sizeof(stats);
	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to send protocol stats, rc = %d\n", rc);
}