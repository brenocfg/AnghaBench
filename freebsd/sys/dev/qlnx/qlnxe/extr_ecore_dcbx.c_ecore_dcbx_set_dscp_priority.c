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
typedef  scalar_t__ u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_2__ {scalar_t__* dscp_pri_map; } ;
struct ecore_dcbx_set {TYPE_1__ dscp; int /*<<< orphan*/  override_flags; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dcbx_set ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ECORE_DCBX_DSCP_SIZE ; 
 int /*<<< orphan*/  ECORE_DCBX_OVERRIDE_DSCP_CFG ; 
 int ECORE_INVAL ; 
 scalar_t__ ECORE_MAX_PFC_PRIORITIES ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_dcbx_set*,int /*<<< orphan*/ ,int) ; 
 int ecore_dcbx_config_params (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_dcbx_set*,int) ; 
 int ecore_dcbx_get_config_params (struct ecore_hwfn*,struct ecore_dcbx_set*) ; 

enum _ecore_status_t
ecore_dcbx_set_dscp_priority(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			     u8 dscp_index, u8 pri_val)
{
	struct ecore_dcbx_set dcbx_set;
	enum _ecore_status_t rc;

	if (dscp_index >= ECORE_DCBX_DSCP_SIZE ||
	    pri_val >= ECORE_MAX_PFC_PRIORITIES) {
		DP_ERR(p_hwfn, "Invalid dscp params: index = %d pri = %d\n",
		       dscp_index, pri_val);
		return ECORE_INVAL;
	}

	OSAL_MEMSET(&dcbx_set, 0, sizeof(dcbx_set));
	rc = ecore_dcbx_get_config_params(p_hwfn, &dcbx_set);
	if (rc)
		return rc;

	dcbx_set.override_flags = ECORE_DCBX_OVERRIDE_DSCP_CFG;
	dcbx_set.dscp.dscp_pri_map[dscp_index] = pri_val;

	return ecore_dcbx_config_params(p_hwfn, p_ptt, &dcbx_set, 1);
}