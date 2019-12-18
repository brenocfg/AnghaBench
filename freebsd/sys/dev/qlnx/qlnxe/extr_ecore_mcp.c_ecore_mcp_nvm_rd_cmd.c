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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int data_dst_size; void* mcp_param; void* mcp_resp; int /*<<< orphan*/ * p_data_dst; void* param; void* cmd; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int MCP_DRV_NVM_BUF_LEN ; 
 int /*<<< orphan*/  OSAL_MEMCPY (void**,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mcp_mb_params*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 

enum _ecore_status_t ecore_mcp_nvm_rd_cmd(struct ecore_hwfn *p_hwfn,
					  struct ecore_ptt *p_ptt,
					  u32 cmd,
					  u32 param,
					  u32 *o_mcp_resp,
					  u32 *o_mcp_param,
					  u32 *o_txn_size,
					  u32 *o_buf)
{
	struct ecore_mcp_mb_params mb_params;
	u8 raw_data[MCP_DRV_NVM_BUF_LEN];
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;
	mb_params.p_data_dst = raw_data;

	/* Use the maximal value since the actual one is part of the response */
	mb_params.data_dst_size = MCP_DRV_NVM_BUF_LEN;

	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc != ECORE_SUCCESS)
		return rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	*o_txn_size = *o_mcp_param;
	OSAL_MEMCPY(o_buf, raw_data, *o_txn_size);

	return ECORE_SUCCESS;
}