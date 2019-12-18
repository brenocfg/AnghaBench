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
struct mcp_wwn {int data_src_size; struct mcp_wwn* p_data_src; int /*<<< orphan*/  cmd; void* wwn_lower; void* wwn_upper; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int data_src_size; struct ecore_mcp_mb_params* p_data_src; int /*<<< orphan*/  cmd; void* wwn_lower; void* wwn_upper; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  int /*<<< orphan*/  fabric_name ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OEM_UPDATE_FCOE_FABRIC_NAME ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct mcp_wwn*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct mcp_wwn*) ; 

enum _ecore_status_t
ecore_mcp_update_fcoe_fabric_name(struct ecore_hwfn *p_hwfn,
				  struct ecore_ptt *p_ptt, u8 *wwn)
{
	struct ecore_mcp_mb_params mb_params;
	struct mcp_wwn fabric_name;
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(&fabric_name, sizeof(fabric_name));
	fabric_name.wwn_upper = *(u32 *)wwn;
	fabric_name.wwn_lower = *(u32 *)(wwn + 4);

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_OEM_UPDATE_FCOE_FABRIC_NAME;
	mb_params.p_data_src = &fabric_name;
	mb_params.data_src_size = sizeof(fabric_name);
	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to update fcoe wwn, rc = %d\n", rc);

	return rc;
}