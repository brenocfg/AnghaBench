#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {TYPE_1__* mcp_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_GET_MFW_FEATURE_SUPPORT ; 
 int ECORE_MSG_PROBE ; 
 int ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_mcp_get_capabilities(struct ecore_hwfn *p_hwfn,
						struct ecore_ptt *p_ptt)
{
	u32 mcp_resp;
	enum _ecore_status_t rc;

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_GET_MFW_FEATURE_SUPPORT,
			   0, &mcp_resp, &p_hwfn->mcp_info->capabilities);
	if (rc == ECORE_SUCCESS)
		DP_VERBOSE(p_hwfn, (ECORE_MSG_SP | ECORE_MSG_PROBE),
			   "MFW supported features: %08x\n",
			   p_hwfn->mcp_info->capabilities);

	return rc;
}