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
typedef  scalar_t__ u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int DRV_MB_PARAM_FCOE_CVID_OFFSET ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OEM_UPDATE_FCOE_CVID ; 
 int ECORE_SUCCESS ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,int*,int*) ; 

enum _ecore_status_t
ecore_mcp_update_fcoe_cvid(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			   u16 vlan)
{
	u32 resp = 0, param = 0;
	enum _ecore_status_t rc;

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OEM_UPDATE_FCOE_CVID,
			   (u32)vlan << DRV_MB_PARAM_FCOE_CVID_OFFSET,
			   &resp, &param);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to update fcoe vlan, rc = %d\n", rc);

	return rc;
}