#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_hal_eth_adapter {scalar_t__ mac_mode; TYPE_5__* ec_regs_base; TYPE_3__* mac_regs_base; int /*<<< orphan*/  name; } ;
struct al_eth_eee_params {scalar_t__ enable; int tx_eee_timer; int min_interval; int stop_cnt; scalar_t__ fast_wake; } ;
struct TYPE_9__ {int /*<<< orphan*/  cfg_e; int /*<<< orphan*/  stop_cnt; int /*<<< orphan*/  post_cnt; int /*<<< orphan*/  pre_cnt; } ;
struct TYPE_10__ {TYPE_4__ eee; } ;
struct TYPE_7__ {int /*<<< orphan*/  pcs_40g_ll_eee_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcs_cfg; } ;
struct TYPE_8__ {TYPE_2__ gen_v3; TYPE_1__ kr; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_IS_10G_MAC (scalar_t__) ; 
 scalar_t__ AL_ETH_IS_25G_MAC (scalar_t__) ; 
 scalar_t__ AL_ETH_MAC_MODE_XLG_LL_40G ; 
 scalar_t__ AL_ETH_MAC_MODE_XLG_LL_50G ; 
 int EC_EEE_CFG_E_ENABLE ; 
 int EC_EEE_CFG_E_MASK_EC_TMI_STOP ; 
 int EC_EEE_CFG_E_MASK_MAC_EEE ; 
 int EC_EEE_CFG_E_USE_EC_RX_FIFO ; 
 int EC_EEE_CFG_E_USE_EC_TX_FIFO ; 
 int /*<<< orphan*/  ETH_MAC_GEN_V3_PCS_40G_EEE_CONTROL_ADDR ; 
 int /*<<< orphan*/  ETH_MAC_GEN_V3_PCS_40G_LL_EEE_CFG_TIMER_VAL_MASK ; 
 int ETH_MAC_GEN_V3_PCS_40G_LL_EEE_CFG_TIMER_VAL_SHIFT ; 
 int ETH_MAC_KR_10_PCS_CFG_EEE_TIMER_VAL ; 
 int ETH_MAC_KR_25_PCS_CFG_EEE_TIMER_VAL ; 
 int /*<<< orphan*/  ETH_MAC_KR_PCS_CFG_EEE_TIMER_VAL_MASK ; 
 int ETH_MAC_KR_PCS_CFG_EEE_TIMER_VAL_SHIFT ; 
 int ETH_MAC_XLG_40_PCS_CFG_EEE_TIMER_VAL ; 
 int ETH_MAC_XLG_50_PCS_CFG_EEE_TIMER_VAL ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_40g_pcs_reg_write (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int al_eth_eee_config(struct al_hal_eth_adapter *adapter, struct al_eth_eee_params *params)
{
	uint32_t reg;
	al_dbg("[%s]: config eee.\n", adapter->name);

	if (params->enable == 0) {
		al_dbg("[%s]: disable eee.\n", adapter->name);
		al_reg_write32(&adapter->ec_regs_base->eee.cfg_e, 0);
		return 0;
	}
	if (AL_ETH_IS_10G_MAC(adapter->mac_mode) || AL_ETH_IS_25G_MAC(adapter->mac_mode)) {
		al_reg_write32_masked(
			&adapter->mac_regs_base->kr.pcs_cfg,
			ETH_MAC_KR_PCS_CFG_EEE_TIMER_VAL_MASK,
			((AL_ETH_IS_10G_MAC(adapter->mac_mode)) ?
			ETH_MAC_KR_10_PCS_CFG_EEE_TIMER_VAL :
			ETH_MAC_KR_25_PCS_CFG_EEE_TIMER_VAL) <<
			ETH_MAC_KR_PCS_CFG_EEE_TIMER_VAL_SHIFT);
	}
	if ((adapter->mac_mode == AL_ETH_MAC_MODE_XLG_LL_40G) ||
		(adapter->mac_mode == AL_ETH_MAC_MODE_XLG_LL_50G)) {
		al_reg_write32_masked(
			&adapter->mac_regs_base->gen_v3.pcs_40g_ll_eee_cfg,
			ETH_MAC_GEN_V3_PCS_40G_LL_EEE_CFG_TIMER_VAL_MASK,
			((adapter->mac_mode == AL_ETH_MAC_MODE_XLG_LL_40G) ?
			ETH_MAC_XLG_40_PCS_CFG_EEE_TIMER_VAL :
			ETH_MAC_XLG_50_PCS_CFG_EEE_TIMER_VAL) <<
			ETH_MAC_GEN_V3_PCS_40G_LL_EEE_CFG_TIMER_VAL_SHIFT);
		/* set Deep sleep mode as the LPI function (instead of Fast wake mode) */
		al_eth_40g_pcs_reg_write(adapter, ETH_MAC_GEN_V3_PCS_40G_EEE_CONTROL_ADDR,
			params->fast_wake ? 1 : 0);
	}

	al_reg_write32(&adapter->ec_regs_base->eee.pre_cnt, params->tx_eee_timer);
	al_reg_write32(&adapter->ec_regs_base->eee.post_cnt, params->min_interval);
	al_reg_write32(&adapter->ec_regs_base->eee.stop_cnt, params->stop_cnt);

	reg = EC_EEE_CFG_E_MASK_EC_TMI_STOP | EC_EEE_CFG_E_MASK_MAC_EEE |
	       EC_EEE_CFG_E_ENABLE |
	       EC_EEE_CFG_E_USE_EC_TX_FIFO | EC_EEE_CFG_E_USE_EC_RX_FIFO;

	/*
	 * Addressing RMN: 3732
	 *
	 * RMN description:
	 * When the HW get into eee mode, it can't transmit any pause packet
	 * (when flow control policy is enabled).
	 * In such case, the HW has no way to handle extreme pushback from
	 * the Rx_path fifos.
	 *
	 * Software flow:
	 * Configure RX_FIFO empty as eee mode term.
	 * That way, nothing will prevent pause packet transmittion in
	 * case of extreme pushback from the Rx_path fifos.
	 *
	 */

	al_reg_write32(&adapter->ec_regs_base->eee.cfg_e, reg);

	return 0;
}