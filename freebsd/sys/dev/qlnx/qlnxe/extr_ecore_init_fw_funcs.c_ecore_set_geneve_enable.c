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
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_L2_EDPM_TUNNEL_NGE_ETH_EN_K2_E5 ; 
 int /*<<< orphan*/  DORQ_REG_L2_EDPM_TUNNEL_NGE_IP_EN_K2_E5 ; 
 scalar_t__ ECORE_IS_BB_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIG_REG_NGE_ETH_ENABLE ; 
 int /*<<< orphan*/  NIG_REG_NGE_IP_ENABLE ; 
 scalar_t__ PRS_ETH_OUTPUT_FORMAT ; 
 scalar_t__ PRS_ETH_TUNN_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PRS_REG_OUTPUT_FORMAT_4_0_BB_K2 ; 
 int /*<<< orphan*/  SET_TUNNEL_TYPE_ENABLE_BIT (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

void ecore_set_geneve_enable(struct ecore_hwfn *p_hwfn,
                             struct ecore_ptt *p_ptt,
                             bool eth_geneve_enable,
                             bool ip_geneve_enable)
{
	u32 reg_val;

	/* Update PRS register */
	reg_val = ecore_rd(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN);
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_SHIFT, eth_geneve_enable);   
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_SHIFT, ip_geneve_enable);
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
	ecore_wr(p_hwfn, p_ptt, NIG_REG_NGE_ETH_ENABLE, eth_geneve_enable ? 1 : 0);
	ecore_wr(p_hwfn, p_ptt, NIG_REG_NGE_IP_ENABLE, ip_geneve_enable ? 1 : 0);
    
	/* EDPM with geneve tunnel not supported in BB */
	if (ECORE_IS_BB_B0(p_hwfn->p_dev))
		return;

	/* Update DORQ registers */
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_L2_EDPM_TUNNEL_NGE_ETH_EN_K2_E5, eth_geneve_enable ? 1 : 0);
	ecore_wr(p_hwfn, p_ptt, DORQ_REG_L2_EDPM_TUNNEL_NGE_IP_EN_K2_E5, ip_geneve_enable ? 1 : 0);
}