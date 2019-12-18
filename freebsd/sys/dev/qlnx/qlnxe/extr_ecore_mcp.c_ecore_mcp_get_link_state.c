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
struct ecore_mcp_link_state {int link_up; } ;
struct ecore_hwfn {TYPE_1__* mcp_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_2__ {struct ecore_mcp_link_state link_output; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_SLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 struct ecore_mcp_link_state* OSAL_NULL ; 

struct ecore_mcp_link_state
*ecore_mcp_get_link_state(struct ecore_hwfn *p_hwfn)
{
	if (!p_hwfn || !p_hwfn->mcp_info)
		return OSAL_NULL;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_SLOW(p_hwfn->p_dev)) {
		DP_INFO(p_hwfn, "Non-ASIC - always notify that link is up\n");
		p_hwfn->mcp_info->link_output.link_up = true;
	}
#endif

	return &p_hwfn->mcp_info->link_output;
}