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
typedef  int u32 ;
struct ecore_hwfn {TYPE_1__* p_dcbx_info; } ;
struct ecore_dcbx_dscp_params {int* dscp_pri_map; int /*<<< orphan*/  enabled; } ;
struct ecore_dcbx_get {struct ecore_dcbx_dscp_params dscp; } ;
struct dcb_dscp_map {int* dscp_pri_map; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct dcb_dscp_map dscp_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_DSCP_ENABLE ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int) ; 
 int ECORE_DCBX_DSCP_SIZE ; 
 int /*<<< orphan*/  ECORE_MSG_DCB ; 
 int /*<<< orphan*/  GET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void  ecore_dcbx_get_dscp_params(struct ecore_hwfn *p_hwfn,
					struct ecore_dcbx_get *params)
{
	struct ecore_dcbx_dscp_params *p_dscp;
	struct dcb_dscp_map *p_dscp_map;
	int i, j, entry;
	u32 pri_map;

	p_dscp = &params->dscp;
	p_dscp_map = &p_hwfn->p_dcbx_info->dscp_map;
	p_dscp->enabled = GET_MFW_FIELD(p_dscp_map->flags, DCB_DSCP_ENABLE);

	/* MFW encodes 64 dscp entries into 8 element array of u32 entries,
	 * where each entry holds the 4bit priority map for 8 dscp entries.
	 */
	for (i = 0, entry = 0; i < ECORE_DCBX_DSCP_SIZE / 8; i++) {
		pri_map = p_dscp_map->dscp_pri_map[i];
		DP_VERBOSE(p_hwfn, ECORE_MSG_DCB, "elem %d pri_map 0x%x\n",
			   entry, pri_map);
		for (j = 0; j < ECORE_DCBX_DSCP_SIZE / 8; j++, entry++)
			p_dscp->dscp_pri_map[entry] = (u32)(pri_map >>
							   (j * 4)) & 0xf;
	}
}