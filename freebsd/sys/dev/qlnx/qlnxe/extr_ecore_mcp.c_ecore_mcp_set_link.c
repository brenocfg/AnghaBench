#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct eth_phy_cfg {int eee_cfg; int data_src_size; struct eth_phy_cfg* p_data_src; int /*<<< orphan*/  cmd; int /*<<< orphan*/  loopback_mode; int /*<<< orphan*/  adv_speed; int /*<<< orphan*/  pause; int /*<<< orphan*/  speed; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int eee_cfg; int data_src_size; struct ecore_mcp_mb_params* p_data_src; int /*<<< orphan*/  cmd; int /*<<< orphan*/  loopback_mode; int /*<<< orphan*/  adv_speed; int /*<<< orphan*/  pause; int /*<<< orphan*/  speed; } ;
struct TYPE_8__ {int adv_caps; int tx_lpi_timer; scalar_t__ tx_lpi_enable; scalar_t__ enable; } ;
struct TYPE_6__ {int /*<<< orphan*/  advertised_speeds; int /*<<< orphan*/  forced_speed; int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {scalar_t__ forced_tx; scalar_t__ forced_rx; scalar_t__ autoneg; } ;
struct ecore_mcp_link_params {TYPE_4__ eee; int /*<<< orphan*/  loopback_mode; TYPE_2__ speed; TYPE_1__ pause; } ;
struct ecore_hwfn {int b_drv_link_init; TYPE_3__* mcp_info; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  phy_cfg ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_7__ {int capabilities; struct ecore_mcp_link_params link_input; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_EMUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_INIT_PHY ; 
 int /*<<< orphan*/  DRV_MSG_CODE_LINK_RESET ; 
 int ECORE_EEE_10G_ADV ; 
 int ECORE_EEE_1G_ADV ; 
 int /*<<< orphan*/  ECORE_MSG_LINK ; 
 int ECORE_SUCCESS ; 
 int EEE_CFG_ADV_SPEED_10G ; 
 int EEE_CFG_ADV_SPEED_1G ; 
 int EEE_CFG_EEE_ENABLED ; 
 int EEE_CFG_TX_LPI ; 
 int EEE_TX_TIMER_USEC_MASK ; 
 int EEE_TX_TIMER_USEC_OFFSET ; 
 int /*<<< orphan*/  ETH_PAUSE_AUTONEG ; 
 int /*<<< orphan*/  ETH_PAUSE_RX ; 
 int /*<<< orphan*/  ETH_PAUSE_TX ; 
 int FW_MB_PARAM_FEATURE_SUPPORT_EEE ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct eth_phy_cfg*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct eth_phy_cfg*) ; 
 int /*<<< orphan*/  ecore_mcp_handle_link_change (struct ecore_hwfn*,struct ecore_ptt*,int) ; 

enum _ecore_status_t ecore_mcp_set_link(struct ecore_hwfn *p_hwfn,
					struct ecore_ptt *p_ptt,
					bool b_up)
{
	struct ecore_mcp_link_params *params = &p_hwfn->mcp_info->link_input;
	struct ecore_mcp_mb_params mb_params;
	struct eth_phy_cfg phy_cfg;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	u32 cmd;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_EMUL(p_hwfn->p_dev))
		return ECORE_SUCCESS;
#endif

	/* Set the shmem configuration according to params */
	OSAL_MEM_ZERO(&phy_cfg, sizeof(phy_cfg));
	cmd = b_up ? DRV_MSG_CODE_INIT_PHY : DRV_MSG_CODE_LINK_RESET;
	if (!params->speed.autoneg)
		phy_cfg.speed = params->speed.forced_speed;
	phy_cfg.pause |= (params->pause.autoneg) ? ETH_PAUSE_AUTONEG : 0;
	phy_cfg.pause |= (params->pause.forced_rx) ? ETH_PAUSE_RX : 0;
	phy_cfg.pause |= (params->pause.forced_tx) ? ETH_PAUSE_TX : 0;
	phy_cfg.adv_speed = params->speed.advertised_speeds;
	phy_cfg.loopback_mode = params->loopback_mode;

	/* There are MFWs that share this capability regardless of whether
	 * this is feasible or not. And given that at the very least adv_caps
	 * would be set internally by ecore, we want to make sure LFA would
	 * still work.
	 */
	if ((p_hwfn->mcp_info->capabilities &
	     FW_MB_PARAM_FEATURE_SUPPORT_EEE) &&
	    params->eee.enable) {
		phy_cfg.eee_cfg |= EEE_CFG_EEE_ENABLED;
		if (params->eee.tx_lpi_enable)
			phy_cfg.eee_cfg |= EEE_CFG_TX_LPI;
		if (params->eee.adv_caps & ECORE_EEE_1G_ADV)
			phy_cfg.eee_cfg |= EEE_CFG_ADV_SPEED_1G;
		if (params->eee.adv_caps & ECORE_EEE_10G_ADV)
			phy_cfg.eee_cfg |= EEE_CFG_ADV_SPEED_10G;
		phy_cfg.eee_cfg |= (params->eee.tx_lpi_timer <<
				    EEE_TX_TIMER_USEC_OFFSET) &
					EEE_TX_TIMER_USEC_MASK;
	}

	p_hwfn->b_drv_link_init = b_up;

	if (b_up)
		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
			   "Configuring Link: Speed 0x%08x, Pause 0x%08x, adv_speed 0x%08x, loopback 0x%08x\n",
			   phy_cfg.speed, phy_cfg.pause, phy_cfg.adv_speed,
			   phy_cfg.loopback_mode);
	else
		DP_VERBOSE(p_hwfn, ECORE_MSG_LINK, "Resetting link\n");

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = cmd;
	mb_params.p_data_src = &phy_cfg;
	mb_params.data_src_size = sizeof(phy_cfg);
	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);

	/* if mcp fails to respond we must abort */
	if (rc != ECORE_SUCCESS) {
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");
		return rc;
	}

	/* Mimic link-change attention, done for several reasons:
	 *  - On reset, there's no guarantee MFW would trigger
	 *    an attention.
	 *  - On initialization, older MFWs might not indicate link change
	 *    during LFA, so we'll never get an UP indication.
	 */
	ecore_mcp_handle_link_change(p_hwfn, p_ptt, !b_up);

	return ECORE_SUCCESS;
}