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
struct ecore_resc_unlock_params {int /*<<< orphan*/  resource; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_RESC_LOCK_IND_TABLE ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_resc_unlock_params*,int) ; 
 int ecore_mcp_resc_unlock (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_resc_unlock_params*) ; 

enum _ecore_status_t
ecore_mcp_ind_table_unlock(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt)
{
	struct ecore_resc_unlock_params resc_unlock_params;
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(&resc_unlock_params,
		      sizeof(struct ecore_resc_unlock_params));
	resc_unlock_params.resource = ECORE_RESC_LOCK_IND_TABLE;
	rc = ecore_mcp_resc_unlock(p_hwfn, p_ptt,
				  &resc_unlock_params);
	return rc;
}