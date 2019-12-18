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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int PRS_ETH_VXLAN_NO_L2_ENABLE_OFFSET ; 
 scalar_t__ PRS_ETH_VXLAN_NO_L2_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  PRS_REG_MSG_INFO ; 
 int /*<<< orphan*/  PRS_REG_OUTPUT_FORMAT_4_0_BB_K2 ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

void ecore_set_vxlan_no_l2_enable(struct ecore_hwfn *p_hwfn,
                                struct ecore_ptt *p_ptt,
                                bool enable)
{
    u32 reg_val, cfg_mask;

    /* read PRS config register */
    reg_val = ecore_rd(p_hwfn, p_ptt, PRS_REG_MSG_INFO);

    /* set VXLAN_NO_L2_ENABLE mask */
    cfg_mask = (1 << PRS_ETH_VXLAN_NO_L2_ENABLE_OFFSET);

    if (enable)
    {
        /* set VXLAN_NO_L2_ENABLE flag */
        reg_val |= cfg_mask;

        /* update PRS FIC  register */
        ecore_wr(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2, (u32)PRS_ETH_VXLAN_NO_L2_OUTPUT_FORMAT);
    }
    else 
    {
        /* clear VXLAN_NO_L2_ENABLE flag */
        reg_val &= ~cfg_mask;
    }

    /* write PRS config register */
    ecore_wr(p_hwfn, p_ptt, PRS_REG_MSG_INFO, reg_val);
}