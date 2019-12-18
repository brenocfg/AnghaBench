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
typedef  union drv_union_data {int dummy; } drv_union_data ;
typedef  int /*<<< orphan*/  u64 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {union drv_union_data* p_data_dst; int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MSG_CODE_MEM_ECC_EVENTS ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_mcp_mb_params*,int /*<<< orphan*/ ,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 

enum _ecore_status_t ecore_mcp_mem_ecc_events(struct ecore_hwfn *p_hwfn,
					      struct ecore_ptt *p_ptt,
					      u64 *num_events)
{
	struct ecore_mcp_mb_params mb_params;

	OSAL_MEMSET(&mb_params, 0, sizeof(struct ecore_mcp_mb_params));
	mb_params.cmd = DRV_MSG_CODE_MEM_ECC_EVENTS;
	mb_params.p_data_dst = (union drv_union_data *)num_events;

	return ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
}