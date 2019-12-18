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
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int flags; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int wol_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_UNLOAD_WOL_DISABLED ; 
 int /*<<< orphan*/  DRV_MB_PARAM_UNLOAD_WOL_ENABLED ; 
 int /*<<< orphan*/  DRV_MB_PARAM_UNLOAD_WOL_MCP ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_REQ ; 
 int ECORE_MB_FLAG_AVOID_BLOCK ; 
 int ECORE_MB_FLAG_CAN_SLEEP ; 
#define  ECORE_OV_WOL_DEFAULT 130 
#define  ECORE_OV_WOL_DISABLED 129 
#define  ECORE_OV_WOL_ENABLED 128 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mcp_mb_params*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 

enum _ecore_status_t ecore_mcp_unload_req(struct ecore_hwfn *p_hwfn,
					  struct ecore_ptt *p_ptt)
{
	struct ecore_mcp_mb_params mb_params;
	u32 wol_param;

	switch (p_hwfn->p_dev->wol_config) {
	case ECORE_OV_WOL_DISABLED:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_DISABLED;
		break;
	case ECORE_OV_WOL_ENABLED:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_ENABLED;
		break;
	default:
		DP_NOTICE(p_hwfn, true,
			  "Unknown WoL configuration %02x\n",
			  p_hwfn->p_dev->wol_config);
		/* Fallthrough */
	case ECORE_OV_WOL_DEFAULT:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_MCP;
	}

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_UNLOAD_REQ;
	mb_params.param = wol_param;
	mb_params.flags = ECORE_MB_FLAG_CAN_SLEEP | ECORE_MB_FLAG_AVOID_BLOCK;

	return ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
}