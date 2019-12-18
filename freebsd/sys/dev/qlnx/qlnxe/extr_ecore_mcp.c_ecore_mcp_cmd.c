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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {scalar_t__ mcp_resp; scalar_t__ mcp_param; scalar_t__ param; scalar_t__ cmd; } ;
struct ecore_hwfn {size_t port_id; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_EMUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DRV_MSG_CODE_UNLOAD_REQ ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mcp_mb_params*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 
 int /*<<< orphan*/  loaded ; 
 int /*<<< orphan*/ * loaded_port ; 

enum _ecore_status_t ecore_mcp_cmd(struct ecore_hwfn *p_hwfn,
				   struct ecore_ptt *p_ptt, u32 cmd, u32 param,
				   u32 *o_mcp_resp, u32 *o_mcp_param)
{
	struct ecore_mcp_mb_params mb_params;
	enum _ecore_status_t rc;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_EMUL(p_hwfn->p_dev)) {
		if (cmd == DRV_MSG_CODE_UNLOAD_REQ) {
			loaded--;
			loaded_port[p_hwfn->port_id]--;
			DP_VERBOSE(p_hwfn, ECORE_MSG_SP, "Unload cnt: 0x%x\n",
				   loaded);
		}
		return ECORE_SUCCESS;
	}
#endif

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;
	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc != ECORE_SUCCESS)
		return rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	return ECORE_SUCCESS;
}