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
struct mdump_config_stc {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_mdump_cmd_params {int data_dst_size; scalar_t__ mcp_resp; struct mdump_config_stc* p_data_dst; int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  mdump_cmd_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,scalar_t__) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_MDUMP_GET_CONFIG ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 scalar_t__ FW_MSG_CODE_OK ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mdump_cmd_params*,int) ; 
 int ecore_mcp_mdump_cmd (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mdump_cmd_params*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_mcp_mdump_get_config(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			   struct mdump_config_stc *p_mdump_config)
{
	struct ecore_mdump_cmd_params mdump_cmd_params;
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(&mdump_cmd_params, sizeof(mdump_cmd_params));
	mdump_cmd_params.cmd = DRV_MSG_CODE_MDUMP_GET_CONFIG;
	mdump_cmd_params.p_data_dst = p_mdump_config;
	mdump_cmd_params.data_dst_size = sizeof(*p_mdump_config);

	rc = ecore_mcp_mdump_cmd(p_hwfn, p_ptt, &mdump_cmd_params);
	if (rc != ECORE_SUCCESS)
		return rc;

	if (mdump_cmd_params.mcp_resp != FW_MSG_CODE_OK) {
		DP_INFO(p_hwfn,
			"Failed to get the mdump configuration and logs info [mcp_resp 0x%x]\n",
			mdump_cmd_params.mcp_resp);
		rc = ECORE_UNKNOWN_ERROR;
	}

	return rc;
}