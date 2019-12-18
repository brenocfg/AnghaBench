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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_L2_EDPM_TUNNEL_GRE_ETH_EN ; 
 int /*<<< orphan*/  DORQ_REG_L2_EDPM_TUNNEL_GRE_IP_EN ; 
 int /*<<< orphan*/  NIG_REG_ENC_TYPE_ENABLE ; 
 int /*<<< orphan*/  NIG_REG_ENC_TYPE_ENABLE_ETH_OVER_GRE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  NIG_REG_ENC_TYPE_ENABLE_IP_OVER_GRE_ENABLE_SHIFT ; 
 scalar_t__ PRS_ETH_OUTPUT_FORMAT ; 
 scalar_t__ PRS_ETH_TUNN_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GRE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GRE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PRS_REG_OUTPUT_FORMAT_4_0_BB_K2 ; 
 int /*<<< orphan*/  SET_TUNNEL_TYPE_ENABLE_BIT (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

void ecore_set_gre_enable(struct ecore_hwfn *p_hwfn,
	struct ecore_ptt *p_ptt,
	bool eth_gre_enable,
	bool ip_gre_enable)
{
	u32 reg_val;

	/* Update PRS register */
	reg_val = ecore_rd(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN);
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GRE_ENABLE_SHIFT, eth_gre_enable);
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GRE_ENABLE_SHIFT,  ip_gre_enable);
	ecore_wr(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN, reg_val);
    if (reg_val) /* TODO: handle E5 init */
    {
        reg_val = ecore_rd(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2);

        /* Update output  only if tunnel blocks not included. */
        if (reg_val == (u32)PRS_ETH_OUTPUT_FORMAT)
        {
            ecore_wr(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2, (u32)PRS_ETH_TUNN_OUTPUT_FORMAT);
        }
    }

	/* Update NIG register */
	reg_val = ecore_rd(p_hwfn, p_ptt, NIG_REG_ENC_TYPE_ENABLE);
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, NIG_REG_ENC_TYPE_ENABLE_ETH_OVER_GRE_ENABLE_SHIFT, eth_gre_enable);
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, NIG_REG_ENC_TYPE_ENABLE_IP_OVER_GRE_ENABLE_SHIFT,  ip_gre_enable);
	ecore_wr(p_hwfn, p_ptt, NIG_REG_ENC_TYPE_ENABLE, reg_val);

	/* Update DORQ registers */
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_L2_EDPM_TUNNEL_GRE_ETH_EN, eth_gre_enable ? 1 : 0);
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_L2_EDPM_TUNNEL_GRE_IP_EN, ip_gre_enable ? 1 : 0);
}