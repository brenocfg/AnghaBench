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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_addr; int /*<<< orphan*/  public_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int /*<<< orphan*/  MFW_PORT (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  PUBLIC_PORT ; 
 int /*<<< orphan*/  SECTION_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECTION_OFFSIZE_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

void ecore_mcp_cmd_port_init(struct ecore_hwfn *p_hwfn,
			     struct ecore_ptt *p_ptt)
{
	u32 addr = SECTION_OFFSIZE_ADDR(p_hwfn->mcp_info->public_base,
					PUBLIC_PORT);
	u32 mfw_mb_offsize = ecore_rd(p_hwfn, p_ptt, addr);

	p_hwfn->mcp_info->port_addr = SECTION_ADDR(mfw_mb_offsize,
						   MFW_PORT(p_hwfn));
	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "port_addr = 0x%x, port_id 0x%02x\n",
		   p_hwfn->mcp_info->port_addr, MFW_PORT(p_hwfn));
}