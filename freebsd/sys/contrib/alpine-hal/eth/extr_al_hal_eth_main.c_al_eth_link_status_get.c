#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_hal_eth_adapter {scalar_t__ mac_mode; int /*<<< orphan*/  name; TYPE_6__* mac_regs_base; } ;
struct al_eth_link_status {int link_up; void* local_fault; void* remote_fault; } ;
struct TYPE_11__ {int /*<<< orphan*/  mac_40g_ll_status; int /*<<< orphan*/  pcs_40g_ll_status; } ;
struct TYPE_10__ {int /*<<< orphan*/  rgmii_stat; } ;
struct TYPE_9__ {int /*<<< orphan*/  link_stat; int /*<<< orphan*/  reg_data; int /*<<< orphan*/  reg_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  pcs_data; int /*<<< orphan*/  pcs_addr; } ;
struct TYPE_12__ {TYPE_5__ gen_v3; TYPE_4__ gen; TYPE_3__ sgmii; TYPE_2__ mac_10g; TYPE_1__ kr; } ;

/* Variables and functions */
 int AL_BIT (int) ; 
 scalar_t__ AL_ETH_IS_10G_MAC (scalar_t__) ; 
 scalar_t__ AL_ETH_IS_25G_MAC (scalar_t__) ; 
 scalar_t__ AL_ETH_MAC_MODE_RGMII ; 
 scalar_t__ AL_ETH_MAC_MODE_SGMII ; 
 scalar_t__ AL_ETH_MAC_MODE_XLG_LL_25G ; 
 scalar_t__ AL_ETH_MAC_MODE_XLG_LL_40G ; 
 scalar_t__ AL_ETH_MAC_MODE_XLG_LL_50G ; 
 void* AL_FALSE ; 
 void* AL_TRUE ; 
 int EPERM ; 
 int ETH_MAC_GEN_MAC_10G_STAT_LOC_FAULT ; 
 int ETH_MAC_GEN_MAC_10G_STAT_REM_FAULT ; 
 int ETH_MAC_GEN_V3_MAC_40G_LL_STATUS_LOC_FAULT ; 
 int ETH_MAC_GEN_V3_MAC_40G_LL_STATUS_REM_FAULT ; 
 int ETH_MAC_KR_PCS_BASE_R_STATUS2 ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  al_eth_mac_mode_str (scalar_t__) ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_eth_link_status_get(struct al_hal_eth_adapter *adapter,
			   struct al_eth_link_status *status)
{
	uint32_t reg;

	if (AL_ETH_IS_10G_MAC(adapter->mac_mode) || AL_ETH_IS_25G_MAC(adapter->mac_mode)) {
		status->link_up = AL_FALSE;
		status->local_fault = AL_TRUE;
		status->remote_fault = AL_TRUE;

		al_reg_write32(&adapter->mac_regs_base->kr.pcs_addr, ETH_MAC_KR_PCS_BASE_R_STATUS2);
		reg = al_reg_read32(&adapter->mac_regs_base->kr.pcs_data);

		if (reg & AL_BIT(15)) {
			reg = al_reg_read32(&adapter->mac_regs_base->mac_10g.status);

			status->remote_fault = ((reg & ETH_MAC_GEN_MAC_10G_STAT_REM_FAULT) ?
							AL_TRUE : AL_FALSE);
			status->local_fault = ((reg & ETH_MAC_GEN_MAC_10G_STAT_LOC_FAULT) ?
							AL_TRUE : AL_FALSE);

			status->link_up = ((status->remote_fault == AL_FALSE) &&
					   (status->local_fault == AL_FALSE));
		}

	} else if (adapter->mac_mode == AL_ETH_MAC_MODE_SGMII) {
		al_reg_write32(&adapter->mac_regs_base->sgmii.reg_addr, 1);
		/*
		 * This register is latched low so need to read twice to get
		 * the current link status
		 */
		reg = al_reg_read32(&adapter->mac_regs_base->sgmii.reg_data);
		reg = al_reg_read32(&adapter->mac_regs_base->sgmii.reg_data);

		status->link_up = AL_FALSE;

		if (reg & AL_BIT(2))
			status->link_up = AL_TRUE;

		reg = al_reg_read32(&adapter->mac_regs_base->sgmii.link_stat);

		if ((reg & AL_BIT(3)) == 0)
			status->link_up = AL_FALSE;

	} else if (adapter->mac_mode == AL_ETH_MAC_MODE_RGMII) {
		reg = al_reg_read32(&adapter->mac_regs_base->gen.rgmii_stat);

		status->link_up = AL_FALSE;

		if (reg & AL_BIT(4))
			status->link_up = AL_TRUE;

	} else if (adapter->mac_mode == AL_ETH_MAC_MODE_XLG_LL_25G) {
		status->link_up = AL_FALSE;
		status->local_fault = AL_TRUE;
		status->remote_fault = AL_TRUE;

		reg = al_reg_read32(&adapter->mac_regs_base->gen_v3.pcs_40g_ll_status);

		status->link_up = AL_FALSE;

		if ((reg & 0xF) == 0xF) {
			reg = al_reg_read32(&adapter->mac_regs_base->gen_v3.mac_40g_ll_status);

			status->remote_fault = ((reg & ETH_MAC_GEN_V3_MAC_40G_LL_STATUS_REM_FAULT) ?
							AL_TRUE : AL_FALSE);
			status->local_fault = ((reg & ETH_MAC_GEN_V3_MAC_40G_LL_STATUS_LOC_FAULT) ?
							AL_TRUE : AL_FALSE);

			status->link_up = ((status->remote_fault == AL_FALSE) &&
					   (status->local_fault == AL_FALSE));
		}

	} else if ((adapter->mac_mode == AL_ETH_MAC_MODE_XLG_LL_40G) ||
			(adapter->mac_mode == AL_ETH_MAC_MODE_XLG_LL_50G)) {
		reg = al_reg_read32(&adapter->mac_regs_base->gen_v3.pcs_40g_ll_status);

		status->link_up = AL_FALSE;

		if ((reg & 0x1F) == 0x1F) {
			reg = al_reg_read32(&adapter->mac_regs_base->gen_v3.mac_40g_ll_status);
			if ((reg & (ETH_MAC_GEN_V3_MAC_40G_LL_STATUS_REM_FAULT |
					ETH_MAC_GEN_V3_MAC_40G_LL_STATUS_LOC_FAULT)) == 0)
				status->link_up = AL_TRUE;
		}

	} else {
		/* not implemented yet */
		return -EPERM;
	}

	al_dbg("[%s]: mac %s port. link_status: %s.\n", adapter->name,
		al_eth_mac_mode_str(adapter->mac_mode),
		(status->link_up == AL_TRUE) ? "LINK_UP" : "LINK_DOWN");

	return 0;
}