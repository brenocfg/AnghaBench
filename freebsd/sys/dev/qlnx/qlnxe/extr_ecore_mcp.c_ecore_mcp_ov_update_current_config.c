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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum ecore_ov_client { ____Placeholder_ecore_ov_client } ecore_ov_client ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_OV_CURR_CFG_OS ; 
 int /*<<< orphan*/  DRV_MB_PARAM_OV_CURR_CFG_OTHER ; 
 int /*<<< orphan*/  DRV_MB_PARAM_OV_CURR_CFG_VENDOR_SPEC ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_CURR_CFG ; 
 int ECORE_INVAL ; 
#define  ECORE_OV_CLIENT_DRV 130 
#define  ECORE_OV_CLIENT_USER 129 
#define  ECORE_OV_CLIENT_VENDOR_SPEC 128 
 int ECORE_SUCCESS ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t
ecore_mcp_ov_update_current_config(struct ecore_hwfn *p_hwfn,
				   struct ecore_ptt *p_ptt,
				   enum ecore_ov_client client)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	enum _ecore_status_t rc;

	switch (client) {
	case ECORE_OV_CLIENT_DRV:
		drv_mb_param = DRV_MB_PARAM_OV_CURR_CFG_OS;
		break;
	case ECORE_OV_CLIENT_USER:
		drv_mb_param = DRV_MB_PARAM_OV_CURR_CFG_OTHER;
		break;
	case ECORE_OV_CLIENT_VENDOR_SPEC:
		drv_mb_param = DRV_MB_PARAM_OV_CURR_CFG_VENDOR_SPEC;
		break;
	default:
		DP_NOTICE(p_hwfn, true,
			  "Invalid client type %d\n", client);
		return ECORE_INVAL;
	}

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_CURR_CFG,
			   drv_mb_param, &resp, &param);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");

	return rc;
}