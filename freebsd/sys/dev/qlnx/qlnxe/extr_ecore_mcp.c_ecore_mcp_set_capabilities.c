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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int DRV_MB_PARAM_FEATURE_SUPPORT_FUNC_VLINK ; 
 int DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EEE ; 
 int DRV_MB_PARAM_FEATURE_SUPPORT_PORT_SMARTLINQ ; 
 int /*<<< orphan*/  DRV_MSG_CODE_FEATURE_SUPPORT ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int*,int*) ; 

enum _ecore_status_t ecore_mcp_set_capabilities(struct ecore_hwfn *p_hwfn,
						struct ecore_ptt *p_ptt)
{
	u32 mcp_resp, mcp_param, features;

	features = DRV_MB_PARAM_FEATURE_SUPPORT_PORT_SMARTLINQ |
		   DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EEE |
		   DRV_MB_PARAM_FEATURE_SUPPORT_FUNC_VLINK;

	return ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_FEATURE_SUPPORT,
			     features, &mcp_resp, &mcp_param);
}