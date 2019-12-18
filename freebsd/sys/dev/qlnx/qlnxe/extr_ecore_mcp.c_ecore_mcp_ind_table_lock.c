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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ecore_resc_lock_params {int /*<<< orphan*/  b_granted; scalar_t__ retry_interval; scalar_t__ retry_num; int /*<<< orphan*/  resource; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_BUSY ; 
 scalar_t__ ECORE_MCP_RESC_LOCK_RETRY_CNT_DFLT ; 
 scalar_t__ ECORE_MCP_RESC_LOCK_RETRY_VAL_DFLT ; 
 int /*<<< orphan*/  ECORE_RESC_LOCK_IND_TABLE ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_resc_lock_params*,int) ; 
 int ecore_mcp_resc_lock (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_resc_lock_params*) ; 

enum _ecore_status_t
ecore_mcp_ind_table_lock(struct ecore_hwfn *p_hwfn,
			 struct ecore_ptt *p_ptt,
			 u8 retry_num,
			 u32 retry_interval)
{
	struct ecore_resc_lock_params resc_lock_params;
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(&resc_lock_params,
		      sizeof(struct ecore_resc_lock_params));
	resc_lock_params.resource = ECORE_RESC_LOCK_IND_TABLE;
	if (!retry_num)
		retry_num = ECORE_MCP_RESC_LOCK_RETRY_CNT_DFLT;
	resc_lock_params.retry_num = retry_num;

	if (!retry_interval)
		retry_interval = ECORE_MCP_RESC_LOCK_RETRY_VAL_DFLT;
	resc_lock_params.retry_interval = retry_interval;

	rc = ecore_mcp_resc_lock(p_hwfn, p_ptt, &resc_lock_params);
	if (rc == ECORE_SUCCESS && !resc_lock_params.b_granted) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to acquire the resource lock for IDT access\n");
		return ECORE_BUSY;
	}
	return rc;
}