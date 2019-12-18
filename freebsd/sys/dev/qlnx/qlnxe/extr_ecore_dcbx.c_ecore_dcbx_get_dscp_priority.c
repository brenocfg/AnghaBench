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
typedef  size_t u8 ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
struct TYPE_2__ {size_t* dscp_pri_map; } ;
struct ecore_dcbx_get {TYPE_1__ dscp; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,size_t) ; 
 size_t ECORE_DCBX_DSCP_SIZE ; 
 int /*<<< orphan*/  ECORE_DCBX_OPERATIONAL_MIB ; 
 int ECORE_INVAL ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ecore_dcbx_get* OSAL_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_dcbx_get*) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_dcbx_get*,int /*<<< orphan*/ ,int) ; 
 int ecore_dcbx_query_params (struct ecore_hwfn*,struct ecore_dcbx_get*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t
ecore_dcbx_get_dscp_priority(struct ecore_hwfn *p_hwfn,
			     u8 dscp_index, u8 *p_dscp_pri)
{
	struct ecore_dcbx_get *p_dcbx_info;
	enum _ecore_status_t rc;

	if (dscp_index >= ECORE_DCBX_DSCP_SIZE) {
		DP_ERR(p_hwfn, "Invalid dscp index %d\n", dscp_index);
		return ECORE_INVAL;
	}

	p_dcbx_info = OSAL_ALLOC(p_hwfn->p_dev, GFP_KERNEL,
				 sizeof(*p_dcbx_info));
	if (!p_dcbx_info)
		return ECORE_NOMEM;

	OSAL_MEMSET(p_dcbx_info, 0, sizeof(*p_dcbx_info));
	rc = ecore_dcbx_query_params(p_hwfn, p_dcbx_info,
				     ECORE_DCBX_OPERATIONAL_MIB);
	if (rc) {
		OSAL_FREE(p_hwfn->p_dev, p_dcbx_info);
		return rc;
	}

	*p_dscp_pri = p_dcbx_info->dscp.dscp_pri_map[dscp_index];
	OSAL_FREE(p_hwfn->p_dev, p_dcbx_info);

	return ECORE_SUCCESS;
}