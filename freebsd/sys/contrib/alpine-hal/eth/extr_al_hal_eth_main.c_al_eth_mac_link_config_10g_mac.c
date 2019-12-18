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
typedef  int uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* mac_regs_base; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  if_mode; int /*<<< orphan*/  control; } ;
struct TYPE_4__ {TYPE_1__ mac_10g; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AL_REG_MASK_CLEAR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_MASK_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_10G_MAC_CONTROL_AN_EN_MASK ; 
 int /*<<< orphan*/  ETH_10G_MAC_IF_MODE_SGMII_AN_MASK ; 
 int ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_FULL ; 
 int ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_HALF ; 
 int /*<<< orphan*/  ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_MASK ; 
 int /*<<< orphan*/  ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_SHIFT ; 
 int /*<<< orphan*/  ETH_10G_MAC_IF_MODE_SGMII_EN_MASK ; 
 int ETH_10G_MAC_IF_MODE_SGMII_SPEED_100M ; 
 int ETH_10G_MAC_IF_MODE_SGMII_SPEED_10M ; 
 int ETH_10G_MAC_IF_MODE_SGMII_SPEED_1G ; 
 int /*<<< orphan*/  ETH_10G_MAC_IF_MODE_SGMII_SPEED_MASK ; 
 int /*<<< orphan*/  ETH_10G_MAC_IF_MODE_SGMII_SPEED_SHIFT ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void al_eth_mac_link_config_10g_mac(
				struct al_hal_eth_adapter *adapter,
				al_bool force_1000_base_x,
				al_bool an_enable,
				uint32_t speed,
				al_bool full_duplex)
{
	uint32_t if_mode;
	uint32_t val;

	if_mode = al_reg_read32(&adapter->mac_regs_base->mac_10g.if_mode);

	if (force_1000_base_x) {
		uint32_t control;

		AL_REG_MASK_CLEAR(if_mode, ETH_10G_MAC_IF_MODE_SGMII_EN_MASK);

		control = al_reg_read32(&adapter->mac_regs_base->mac_10g.control);

		if (an_enable)
			AL_REG_MASK_SET(control, ETH_10G_MAC_CONTROL_AN_EN_MASK);
		else
			AL_REG_MASK_CLEAR(control, ETH_10G_MAC_CONTROL_AN_EN_MASK);

		al_reg_write32(&adapter->mac_regs_base->mac_10g.control, control);

	} else {
		AL_REG_MASK_SET(if_mode, ETH_10G_MAC_IF_MODE_SGMII_EN_MASK);
		if (an_enable) {
			AL_REG_MASK_SET(if_mode, ETH_10G_MAC_IF_MODE_SGMII_AN_MASK);
		} else {
			AL_REG_MASK_CLEAR(if_mode, ETH_10G_MAC_IF_MODE_SGMII_AN_MASK);

			if (speed == 1000)
				val = ETH_10G_MAC_IF_MODE_SGMII_SPEED_1G;
			else if (speed == 100)
				val = ETH_10G_MAC_IF_MODE_SGMII_SPEED_100M;
			else
				val = ETH_10G_MAC_IF_MODE_SGMII_SPEED_10M;

			AL_REG_FIELD_SET(if_mode,
					 ETH_10G_MAC_IF_MODE_SGMII_SPEED_MASK,
					 ETH_10G_MAC_IF_MODE_SGMII_SPEED_SHIFT,
					 val);

			AL_REG_FIELD_SET(if_mode,
					 ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_MASK,
					 ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_SHIFT,
					 ((full_duplex) ?
						ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_FULL :
						ETH_10G_MAC_IF_MODE_SGMII_DUPLEX_HALF));
		}
	}

	al_reg_write32(&adapter->mac_regs_base->mac_10g.if_mode, if_mode);
}