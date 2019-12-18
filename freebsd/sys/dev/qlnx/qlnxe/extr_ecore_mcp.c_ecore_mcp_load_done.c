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
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_LOAD_DONE ; 
 int ECORE_ABORTED ; 
 int ECORE_SUCCESS ; 
 scalar_t__ FW_MB_PARAM_LOAD_DONE_DID_EFUSE_ERROR ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_REFUSED_REJECT ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

enum _ecore_status_t ecore_mcp_load_done(struct ecore_hwfn *p_hwfn,
					 struct ecore_ptt *p_ptt)
{
	u32 resp = 0, param = 0;
	enum _ecore_status_t rc;

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_LOAD_DONE, 0, &resp,
			   &param);
	if (rc != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to send a LOAD_DONE command, rc = %d\n", rc);
		return rc;
	}

	if (resp == FW_MSG_CODE_DRV_LOAD_REFUSED_REJECT) {
		DP_NOTICE(p_hwfn, false,
			  "Received a LOAD_REFUSED_REJECT response from the mfw\n");
		return ECORE_ABORTED;
	}

	/* Check if there is a DID mismatch between nvm-cfg/efuse */
	if (param & FW_MB_PARAM_LOAD_DONE_DID_EFUSE_ERROR)
		DP_NOTICE(p_hwfn, false,
			  "warning: device configuration is not supported on this board type. The device may not function as expected.\n");

	return ECORE_SUCCESS;
}