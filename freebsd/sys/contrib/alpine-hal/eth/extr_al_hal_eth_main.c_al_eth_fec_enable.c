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
struct al_hal_eth_adapter {scalar_t__ rev_id; TYPE_2__* mac_regs_base; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  pcs_10g_ll_cfg; } ;
struct TYPE_4__ {TYPE_1__ gen_v3; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_RX ; 
 int ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_TX ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

int al_eth_fec_enable(struct al_hal_eth_adapter *adapter, al_bool enable)
{
	if (adapter->rev_id <= AL_ETH_REV_ID_2)
		return -1;

	if (enable)
		al_reg_write32_masked(&adapter->mac_regs_base->gen_v3.pcs_10g_ll_cfg,
					(ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_RX |
					 ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_TX),
					(ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_RX |
					 ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_TX));
	else
		al_reg_write32_masked(&adapter->mac_regs_base->gen_v3.pcs_10g_ll_cfg,
					(ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_RX |
					 ETH_MAC_GEN_V3_PCS_10G_LL_CFG_FEC_EN_TX),
					0);
	return 0;
}