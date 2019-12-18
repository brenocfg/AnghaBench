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
typedef  int uint32_t ;
struct al_hal_eth_adapter {scalar_t__ mac_mode; TYPE_4__* mac_regs_base; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_7__ {int /*<<< orphan*/  cmd_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_data; int /*<<< orphan*/  reg_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  rgmii_cfg; } ;
struct TYPE_8__ {TYPE_3__ mac_1g; TYPE_2__ sgmii; TYPE_1__ gen; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_MAC_MODE_RGMII ; 
 scalar_t__ AL_ETH_MAC_MODE_SGMII ; 
 scalar_t__ AL_FALSE ; 
 int /*<<< orphan*/  AL_REG_MASK_CLEAR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_MASK_SET (int,int /*<<< orphan*/ ) ; 
 scalar_t__ AL_TRUE ; 
 int /*<<< orphan*/  ETH_1G_MAC_CMD_CFG_10M_SPD ; 
 int /*<<< orphan*/  ETH_1G_MAC_CMD_CFG_1G_SPD ; 
 int /*<<< orphan*/  ETH_1G_MAC_CMD_CFG_HD_EN ; 
 int /*<<< orphan*/  ETH_MAC_GEN_RGMII_CFG_ENA_AUTO ; 
 int /*<<< orphan*/  ETH_MAC_GEN_RGMII_CFG_SET_1000_SEL ; 
 int /*<<< orphan*/  ETH_MAC_GEN_RGMII_CFG_SET_10_SEL ; 
 int ETH_MAC_SGMII_REG_ADDR_CTRL_REG ; 
 int ETH_MAC_SGMII_REG_ADDR_IF_MODE_REG ; 
 int ETH_MAC_SGMII_REG_DATA_CTRL_AN_ENABLE ; 
 int ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_AN ; 
 int ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_DUPLEX ; 
 int ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_EN ; 
 int ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_SPEED_100 ; 
 int ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_SPEED_1000 ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void al_eth_mac_link_config_1g_mac(
				struct al_hal_eth_adapter *adapter,
				al_bool force_1000_base_x,
				al_bool an_enable,
				uint32_t speed,
				al_bool full_duplex)
{
	uint32_t mac_ctrl;
	uint32_t sgmii_ctrl = 0;
	uint32_t sgmii_if_mode = 0;
	uint32_t rgmii_ctrl = 0;

	mac_ctrl = al_reg_read32(&adapter->mac_regs_base->mac_1g.cmd_cfg);

	if (adapter->mac_mode == AL_ETH_MAC_MODE_SGMII) {
		al_reg_write32(&adapter->mac_regs_base->sgmii.reg_addr,
			       ETH_MAC_SGMII_REG_ADDR_CTRL_REG);
		sgmii_ctrl = al_reg_read32(&adapter->mac_regs_base->sgmii.reg_data);
		/*
		 * in case bit 0 is off in sgmii_if_mode register all the other
		 * bits are ignored.
		 */
		if (force_1000_base_x == AL_FALSE)
			sgmii_if_mode = ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_EN;

		if (an_enable == AL_TRUE) {
			sgmii_if_mode |= ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_AN;
			sgmii_ctrl |= ETH_MAC_SGMII_REG_DATA_CTRL_AN_ENABLE;
		} else {
			sgmii_ctrl &= ~(ETH_MAC_SGMII_REG_DATA_CTRL_AN_ENABLE);
		}
	}

	if (adapter->mac_mode == AL_ETH_MAC_MODE_RGMII) {
		/*
		 * Use the speed provided by the MAC instead of the PHY
		 */
		rgmii_ctrl = al_reg_read32(&adapter->mac_regs_base->gen.rgmii_cfg);

		AL_REG_MASK_CLEAR(rgmii_ctrl, ETH_MAC_GEN_RGMII_CFG_ENA_AUTO);
		AL_REG_MASK_CLEAR(rgmii_ctrl, ETH_MAC_GEN_RGMII_CFG_SET_1000_SEL);
		AL_REG_MASK_CLEAR(rgmii_ctrl, ETH_MAC_GEN_RGMII_CFG_SET_10_SEL);

		al_reg_write32(&adapter->mac_regs_base->gen.rgmii_cfg, rgmii_ctrl);
	}

	if (full_duplex == AL_TRUE) {
		AL_REG_MASK_CLEAR(mac_ctrl, ETH_1G_MAC_CMD_CFG_HD_EN);
	} else {
		AL_REG_MASK_SET(mac_ctrl, ETH_1G_MAC_CMD_CFG_HD_EN);
		sgmii_if_mode |= ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_DUPLEX;
	}

	if (speed == 1000) {
		AL_REG_MASK_SET(mac_ctrl, ETH_1G_MAC_CMD_CFG_1G_SPD);
		sgmii_if_mode |= ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_SPEED_1000;
	} else {
		AL_REG_MASK_CLEAR(mac_ctrl, ETH_1G_MAC_CMD_CFG_1G_SPD);
		if (speed == 10) {
			AL_REG_MASK_SET(mac_ctrl, ETH_1G_MAC_CMD_CFG_10M_SPD);
		} else {
			sgmii_if_mode |= ETH_MAC_SGMII_REG_DATA_IF_MODE_SGMII_SPEED_100;
			AL_REG_MASK_CLEAR(mac_ctrl, ETH_1G_MAC_CMD_CFG_10M_SPD);
		}
	}

	if (adapter->mac_mode == AL_ETH_MAC_MODE_SGMII) {
		al_reg_write32(&adapter->mac_regs_base->sgmii.reg_addr,
			       ETH_MAC_SGMII_REG_ADDR_IF_MODE_REG);
		al_reg_write32(&adapter->mac_regs_base->sgmii.reg_data,
			       sgmii_if_mode);

		al_reg_write32(&adapter->mac_regs_base->sgmii.reg_addr,
			       ETH_MAC_SGMII_REG_ADDR_CTRL_REG);
		al_reg_write32(&adapter->mac_regs_base->sgmii.reg_data,
			       sgmii_ctrl);
	}

	al_reg_write32(&adapter->mac_regs_base->mac_1g.cmd_cfg, mac_ctrl);
}