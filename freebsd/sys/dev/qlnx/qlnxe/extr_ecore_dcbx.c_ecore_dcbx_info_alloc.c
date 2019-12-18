#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  iwarp_port; } ;
struct TYPE_4__ {TYPE_2__ rdma_pf_params; } ;
struct ecore_hwfn {TYPE_1__ pf_params; TYPE_3__* p_dcbx_info; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  iwarp_port; } ;

/* Variables and functions */
 scalar_t__ DCBX_MAX_APP_PROTOCOL ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 scalar_t__ ECORE_DCBX_MAX_APP_PROTOCOL ; 
 scalar_t__ ECORE_LLDP_CHASSIS_ID_STAT_LEN ; 
 scalar_t__ ECORE_LLDP_PORT_ID_STAT_LEN ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LLDP_CHASSIS_ID_STAT_LEN ; 
 scalar_t__ LLDP_PORT_ID_STAT_LEN ; 
 int /*<<< orphan*/  OSAL_BUILD_BUG_ON (int) ; 
 TYPE_3__* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_dcbx_info_alloc(struct ecore_hwfn *p_hwfn)
{
#ifndef __EXTRACT__LINUX__
	OSAL_BUILD_BUG_ON(ECORE_LLDP_CHASSIS_ID_STAT_LEN !=
			  LLDP_CHASSIS_ID_STAT_LEN);
	OSAL_BUILD_BUG_ON(ECORE_LLDP_PORT_ID_STAT_LEN !=
			  LLDP_PORT_ID_STAT_LEN);
	OSAL_BUILD_BUG_ON(ECORE_DCBX_MAX_APP_PROTOCOL !=
			  DCBX_MAX_APP_PROTOCOL);
#endif

	p_hwfn->p_dcbx_info = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
					  sizeof(*p_hwfn->p_dcbx_info));
	if (!p_hwfn->p_dcbx_info) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate `struct ecore_dcbx_info'");
		return ECORE_NOMEM;
	}

	p_hwfn->p_dcbx_info->iwarp_port =
		p_hwfn->pf_params.rdma_pf_params.iwarp_port;

	return ECORE_SUCCESS;
}