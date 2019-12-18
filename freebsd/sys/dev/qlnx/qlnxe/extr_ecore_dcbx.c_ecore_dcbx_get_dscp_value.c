#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ecore_hwfn {TYPE_2__* p_dcbx_info; } ;
struct ecore_dcbx_dscp_params {size_t* dscp_pri_map; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {struct ecore_dcbx_dscp_params dscp; } ;
struct TYPE_4__ {TYPE_1__ get; } ;

/* Variables and functions */
 size_t ECORE_DCBX_DSCP_DISABLED ; 
 size_t ECORE_DCBX_DSCP_SIZE ; 

u8 ecore_dcbx_get_dscp_value(struct ecore_hwfn *p_hwfn, u8 pri)
{
	struct ecore_dcbx_dscp_params *dscp = &p_hwfn->p_dcbx_info->get.dscp;
	u8 i;

	if (!dscp->enabled)
		return ECORE_DCBX_DSCP_DISABLED;

	for (i = 0; i < ECORE_DCBX_DSCP_SIZE; i++)
		if (pri == dscp->dscp_pri_map[i])
			return i;

	return ECORE_DCBX_DSCP_DISABLED;
}