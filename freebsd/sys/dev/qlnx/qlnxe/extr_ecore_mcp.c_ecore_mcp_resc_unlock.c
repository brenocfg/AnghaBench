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
struct ecore_resc_unlock_params {int resource; int b_released; scalar_t__ b_force; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 int GET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_OPCODE ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_RESC ; 
 int /*<<< orphan*/  RESOURCE_CMD_RSP_OPCODE ; 
 int RESOURCE_OPCODE_FORCE_RELEASE ; 
 int RESOURCE_OPCODE_RELEASE ; 
#define  RESOURCE_OPCODE_RELEASED 130 
#define  RESOURCE_OPCODE_RELEASED_PREVIOUS 129 
#define  RESOURCE_OPCODE_WRONG_OWNER 128 
 int /*<<< orphan*/  SET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ecore_mcp_resource_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t
ecore_mcp_resc_unlock(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		      struct ecore_resc_unlock_params *p_params)
{
	u32 param = 0, mcp_resp, mcp_param;
	u8 opcode;
	enum _ecore_status_t rc;

	opcode = p_params->b_force ? RESOURCE_OPCODE_FORCE_RELEASE
				   : RESOURCE_OPCODE_RELEASE;
	SET_MFW_FIELD(param, RESOURCE_CMD_REQ_RESC, p_params->resource);
	SET_MFW_FIELD(param, RESOURCE_CMD_REQ_OPCODE, opcode);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "Resource unlock request: param 0x%08x [opcode %d, resource %d]\n",
		   param, opcode, p_params->resource);

	/* Attempt to release the resource */
	rc = ecore_mcp_resource_cmd(p_hwfn, p_ptt, param, &mcp_resp,
				    &mcp_param);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Analyze the response */
	opcode = GET_MFW_FIELD(mcp_param, RESOURCE_CMD_RSP_OPCODE);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "Resource unlock response: mcp_param 0x%08x [opcode %d]\n",
		   mcp_param, opcode);

	switch (opcode) {
	case RESOURCE_OPCODE_RELEASED_PREVIOUS:
		DP_INFO(p_hwfn,
			"Resource unlock request for an already released resource [%d]\n",
			p_params->resource);
		/* Fallthrough */
	case RESOURCE_OPCODE_RELEASED:
		p_params->b_released = true;
		break;
	case RESOURCE_OPCODE_WRONG_OWNER:
		p_params->b_released = false;
		break;
	default:
		DP_NOTICE(p_hwfn, false,
			  "Unexpected opcode in resource unlock response [mcp_param 0x%08x, opcode %d]\n",
			  mcp_param, opcode);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}