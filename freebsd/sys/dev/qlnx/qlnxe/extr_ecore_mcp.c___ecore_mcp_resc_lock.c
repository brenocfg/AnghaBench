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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_resc_lock_params {int timeout; int resource; int b_granted; void* owner; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int ECORE_INVAL ; 
#define  ECORE_MCP_RESC_LOCK_TO_DEFAULT 131 
#define  ECORE_MCP_RESC_LOCK_TO_NONE 130 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 void* GET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_AGE ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_OPCODE ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_RESC ; 
 int /*<<< orphan*/  RESOURCE_CMD_RSP_OPCODE ; 
 int /*<<< orphan*/  RESOURCE_CMD_RSP_OWNER ; 
#define  RESOURCE_OPCODE_BUSY 129 
#define  RESOURCE_OPCODE_GNT 128 
 int RESOURCE_OPCODE_REQ ; 
 int RESOURCE_OPCODE_REQ_WO_AGING ; 
 int RESOURCE_OPCODE_REQ_W_AGING ; 
 int /*<<< orphan*/  SET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ecore_mcp_resource_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum _ecore_status_t
__ecore_mcp_resc_lock(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		      struct ecore_resc_lock_params *p_params)
{
	u32 param = 0, mcp_resp, mcp_param;
	u8 opcode, timeout;
	enum _ecore_status_t rc;

	switch (p_params->timeout) {
	case ECORE_MCP_RESC_LOCK_TO_DEFAULT:
		opcode = RESOURCE_OPCODE_REQ;
		timeout = 0;
		break;
	case ECORE_MCP_RESC_LOCK_TO_NONE:
		opcode = RESOURCE_OPCODE_REQ_WO_AGING;
		timeout = 0;
		break;
	default:
		opcode = RESOURCE_OPCODE_REQ_W_AGING;
		timeout = p_params->timeout;
		break;
	}

	SET_MFW_FIELD(param, RESOURCE_CMD_REQ_RESC, p_params->resource);
	SET_MFW_FIELD(param, RESOURCE_CMD_REQ_OPCODE, opcode);
	SET_MFW_FIELD(param, RESOURCE_CMD_REQ_AGE, timeout);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "Resource lock request: param 0x%08x [age %d, opcode %d, resource %d]\n",
		   param, timeout, opcode, p_params->resource);

	/* Attempt to acquire the resource */
	rc = ecore_mcp_resource_cmd(p_hwfn, p_ptt, param, &mcp_resp,
				    &mcp_param);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Analyze the response */
	p_params->owner = GET_MFW_FIELD(mcp_param, RESOURCE_CMD_RSP_OWNER);
	opcode = GET_MFW_FIELD(mcp_param, RESOURCE_CMD_RSP_OPCODE);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "Resource lock response: mcp_param 0x%08x [opcode %d, owner %d]\n",
		   mcp_param, opcode, p_params->owner);

	switch (opcode) {
	case RESOURCE_OPCODE_GNT:
		p_params->b_granted = true;
		break;
	case RESOURCE_OPCODE_BUSY:
		p_params->b_granted = false;
		break;
	default:
		DP_NOTICE(p_hwfn, false,
			  "Unexpected opcode in resource lock response [mcp_param 0x%08x, opcode %d]\n",
			  mcp_param, opcode);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}