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
 scalar_t__ DRV_MB_PARAM_BIST_CLOCK_TEST ; 
 scalar_t__ DRV_MB_PARAM_BIST_RC_PASSED ; 
 scalar_t__ DRV_MB_PARAM_BIST_TEST_INDEX_OFFSET ; 
 int /*<<< orphan*/  DRV_MSG_CODE_BIST_TEST ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 scalar_t__ FW_MSG_CODE_MASK ; 
 scalar_t__ FW_MSG_CODE_OK ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 

enum _ecore_status_t ecore_mcp_bist_clock_test(struct ecore_hwfn *p_hwfn,
					       struct ecore_ptt *p_ptt)
{
	u32 drv_mb_param, rsp, param;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	drv_mb_param = (DRV_MB_PARAM_BIST_CLOCK_TEST <<
			DRV_MB_PARAM_BIST_TEST_INDEX_OFFSET);

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BIST_TEST,
			   drv_mb_param, &rsp, &param);

	if (rc != ECORE_SUCCESS)
		return rc;

	if (((rsp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK) ||
	    (param != DRV_MB_PARAM_BIST_RC_PASSED))
		rc = ECORE_UNKNOWN_ERROR;

	return rc;
}