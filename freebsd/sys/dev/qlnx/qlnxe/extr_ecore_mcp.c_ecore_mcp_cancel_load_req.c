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
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_CANCEL_LOAD_REQ ; 
 int ECORE_NOTIMPL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ FW_MSG_CODE_UNSUPPORTED ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

enum _ecore_status_t ecore_mcp_cancel_load_req(struct ecore_hwfn *p_hwfn,
					       struct ecore_ptt *p_ptt)
{
	u32 resp = 0, param = 0;
	enum _ecore_status_t rc;

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_CANCEL_LOAD_REQ, 0,
			   &resp, &param);
	if (rc != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to send cancel load request, rc = %d\n", rc);
		return rc;
	}

	if (resp == FW_MSG_CODE_UNSUPPORTED) {
		DP_INFO(p_hwfn,
			"The cancel load command is unsupported by the MFW\n");
		return ECORE_NOTIMPL;
	}

	return ECORE_SUCCESS;
}