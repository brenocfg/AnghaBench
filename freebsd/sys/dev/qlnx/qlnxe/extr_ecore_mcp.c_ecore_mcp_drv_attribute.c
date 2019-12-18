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
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int data_src_size; scalar_t__ mcp_resp; int /*<<< orphan*/  mcp_param; struct ecore_mcp_mb_params* p_data_src; int /*<<< orphan*/  offset; int /*<<< orphan*/  mask; int /*<<< orphan*/  val; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;
struct ecore_mcp_drv_attr {int const attr_cmd; int attr_num; int /*<<< orphan*/  val; int /*<<< orphan*/  offset; int /*<<< orphan*/  mask; } ;
struct ecore_hwfn {int dummy; } ;
struct attribute_cmd_write_stc {int data_src_size; scalar_t__ mcp_resp; int /*<<< orphan*/  mcp_param; struct attribute_cmd_write_stc* p_data_src; int /*<<< orphan*/  offset; int /*<<< orphan*/  mask; int /*<<< orphan*/  val; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  enum _attribute_commands_e { ____Placeholder__attribute_commands_e } _attribute_commands_e ;
typedef  int /*<<< orphan*/  attr_cmd_write ;

/* Variables and functions */
 int ATTRIBUTE_CMD_CLEAR ; 
 int ATTRIBUTE_CMD_READ ; 
 int ATTRIBUTE_CMD_READ_CLEAR ; 
 int ATTRIBUTE_CMD_WRITE ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,...) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int const) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ATTRIBUTE_CMD ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ATTRIBUTE_KEY ; 
 int /*<<< orphan*/  DRV_MSG_CODE_ATTRIBUTE ; 
 int ECORE_INVAL ; 
#define  ECORE_MCP_DRV_ATTR_CMD_CLEAR 131 
#define  ECORE_MCP_DRV_ATTR_CMD_READ 130 
#define  ECORE_MCP_DRV_ATTR_CMD_READ_CLEAR 129 
#define  ECORE_MCP_DRV_ATTR_CMD_WRITE 128 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_NOTIMPL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ FW_MSG_CODE_OK ; 
 scalar_t__ FW_MSG_CODE_UNSUPPORTED ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mcp_mb_params*,int) ; 
 int /*<<< orphan*/  SET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 

enum _ecore_status_t
ecore_mcp_drv_attribute(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			struct ecore_mcp_drv_attr *p_drv_attr)
{
	struct attribute_cmd_write_stc attr_cmd_write;
	enum _attribute_commands_e mfw_attr_cmd;
	struct ecore_mcp_mb_params mb_params;
	enum _ecore_status_t rc;

	switch (p_drv_attr->attr_cmd) {
	case ECORE_MCP_DRV_ATTR_CMD_READ:
		mfw_attr_cmd = ATTRIBUTE_CMD_READ;
		break;
	case ECORE_MCP_DRV_ATTR_CMD_WRITE:
		mfw_attr_cmd = ATTRIBUTE_CMD_WRITE;
		break;
	case ECORE_MCP_DRV_ATTR_CMD_READ_CLEAR:
		mfw_attr_cmd = ATTRIBUTE_CMD_READ_CLEAR;
		break;
	case ECORE_MCP_DRV_ATTR_CMD_CLEAR:
		mfw_attr_cmd = ATTRIBUTE_CMD_CLEAR;
		break;
	default:
		DP_NOTICE(p_hwfn, false, "Unknown attribute command %d\n",
			  p_drv_attr->attr_cmd);
		return ECORE_INVAL;
	}

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_ATTRIBUTE;
	SET_MFW_FIELD(mb_params.param, DRV_MB_PARAM_ATTRIBUTE_KEY,
		      p_drv_attr->attr_num);
	SET_MFW_FIELD(mb_params.param, DRV_MB_PARAM_ATTRIBUTE_CMD,
		      mfw_attr_cmd);
	if (p_drv_attr->attr_cmd == ECORE_MCP_DRV_ATTR_CMD_WRITE) {
		OSAL_MEM_ZERO(&attr_cmd_write, sizeof(attr_cmd_write));
		attr_cmd_write.val = p_drv_attr->val;
		attr_cmd_write.mask = p_drv_attr->mask;
		attr_cmd_write.offset = p_drv_attr->offset;

		mb_params.p_data_src = &attr_cmd_write;
		mb_params.data_src_size = sizeof(attr_cmd_write);
	}

	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc != ECORE_SUCCESS)
		return rc;

	if (mb_params.mcp_resp == FW_MSG_CODE_UNSUPPORTED) {
		DP_INFO(p_hwfn,
			"The attribute command is not supported by the MFW\n");
		return ECORE_NOTIMPL;
	} else if (mb_params.mcp_resp != FW_MSG_CODE_OK) {
		DP_INFO(p_hwfn,
			"Failed to send an attribute command [mcp_resp 0x%x, attr_cmd %d, attr_num %d]\n",
			mb_params.mcp_resp, p_drv_attr->attr_cmd,
			p_drv_attr->attr_num);
		return ECORE_INVAL;
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "Attribute Command: cmd %d [mfw_cmd %d], num %d, in={val 0x%08x, mask 0x%08x, offset 0x%08x}, out={val 0x%08x}\n",
		   p_drv_attr->attr_cmd, mfw_attr_cmd, p_drv_attr->attr_num,
		   p_drv_attr->val, p_drv_attr->mask, p_drv_attr->offset,
		   mb_params.mcp_param);

	if (p_drv_attr->attr_cmd == ECORE_MCP_DRV_ATTR_CMD_READ ||
	    p_drv_attr->attr_cmd == ECORE_MCP_DRV_ATTR_CMD_READ_CLEAR)
		p_drv_attr->val = mb_params.mcp_param;

	return ECORE_SUCCESS;
}