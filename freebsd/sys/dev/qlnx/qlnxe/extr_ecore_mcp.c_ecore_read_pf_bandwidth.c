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
struct public_func {int config; } ;
struct ecore_mcp_function_info {int bandwidth_min; int bandwidth_max; } ;
struct ecore_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {struct ecore_mcp_function_info func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,int) ; 
 int FUNC_MF_CFG_MAX_BW_MASK ; 
 int FUNC_MF_CFG_MAX_BW_OFFSET ; 
 int FUNC_MF_CFG_MIN_BW_MASK ; 
 int FUNC_MF_CFG_MIN_BW_OFFSET ; 

__attribute__((used)) static void ecore_read_pf_bandwidth(struct ecore_hwfn *p_hwfn,
				    struct public_func *p_shmem_info)
{
	struct ecore_mcp_function_info *p_info;

	p_info = &p_hwfn->mcp_info->func_info;

	/* TODO - bandwidth min/max should have valid values of 1-100,
	 * as well as some indication that the feature is disabled.
	 * Until MFW/qlediag enforce those limitations, Assume THERE IS ALWAYS
	 * limit and correct value to min `1' and max `100' if limit isn't in
	 * range.
	 */
	p_info->bandwidth_min = (p_shmem_info->config &
				 FUNC_MF_CFG_MIN_BW_MASK) >>
				FUNC_MF_CFG_MIN_BW_OFFSET;
	if (p_info->bandwidth_min < 1 || p_info->bandwidth_min > 100) {
		DP_INFO(p_hwfn,
			"bandwidth minimum out of bounds [%02x]. Set to 1\n",
			p_info->bandwidth_min);
		p_info->bandwidth_min = 1;
	}

	p_info->bandwidth_max = (p_shmem_info->config &
				 FUNC_MF_CFG_MAX_BW_MASK) >>
				FUNC_MF_CFG_MAX_BW_OFFSET;
	if (p_info->bandwidth_max < 1 || p_info->bandwidth_max > 100) {
		DP_INFO(p_hwfn,
			"bandwidth maximum out of bounds [%02x]. Set to 100\n",
			p_info->bandwidth_max);
		p_info->bandwidth_max = 100;
	}
}