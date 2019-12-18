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
struct TYPE_2__ {int /*<<< orphan*/  cfg_on_link_up; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  get_cable_length; int /*<<< orphan*/  force_speed_duplex; int /*<<< orphan*/  set_d3_lplu_state; int /*<<< orphan*/  reset; int /*<<< orphan*/  release; int /*<<< orphan*/  get_info; int /*<<< orphan*/  get_cfg_done; int /*<<< orphan*/  commit; int /*<<< orphan*/  check_reset_block; int /*<<< orphan*/  check_polarity; int /*<<< orphan*/  acquire; int /*<<< orphan*/  power_down; int /*<<< orphan*/  power_up; } ;
struct e1000_phy_info {scalar_t__ media_type; int addr; int reset_delay_us; scalar_t__ id; TYPE_1__ ops; int /*<<< orphan*/  type; int /*<<< orphan*/  autoneg_mask; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ GG82563_E_PHY_ID ; 
 int /*<<< orphan*/  e1000_acquire_phy_80003es2lan ; 
 int /*<<< orphan*/  e1000_cfg_on_link_up_80003es2lan ; 
 int /*<<< orphan*/  e1000_check_polarity_m88 ; 
 int /*<<< orphan*/  e1000_check_reset_block_generic ; 
 int /*<<< orphan*/  e1000_get_cable_length_80003es2lan ; 
 int /*<<< orphan*/  e1000_get_cfg_done_80003es2lan ; 
 int /*<<< orphan*/  e1000_get_phy_id (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_get_phy_info_m88 ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_phy_force_speed_duplex_80003es2lan ; 
 int /*<<< orphan*/  e1000_phy_gg82563 ; 
 int /*<<< orphan*/  e1000_phy_hw_reset_generic ; 
 int /*<<< orphan*/  e1000_phy_none ; 
 int /*<<< orphan*/  e1000_phy_sw_reset_generic ; 
 int /*<<< orphan*/  e1000_power_down_phy_copper_80003es2lan ; 
 int /*<<< orphan*/  e1000_power_up_phy_copper ; 
 int /*<<< orphan*/  e1000_read_phy_reg_gg82563_80003es2lan ; 
 int /*<<< orphan*/  e1000_release_phy_80003es2lan ; 
 int /*<<< orphan*/  e1000_set_d3_lplu_state_generic ; 
 int /*<<< orphan*/  e1000_write_phy_reg_gg82563_80003es2lan ; 

__attribute__((used)) static s32 e1000_init_phy_params_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	DEBUGFUNC("e1000_init_phy_params_80003es2lan");

	if (hw->phy.media_type != e1000_media_type_copper) {
		phy->type = e1000_phy_none;
		return E1000_SUCCESS;
	} else {
		phy->ops.power_up = e1000_power_up_phy_copper;
		phy->ops.power_down = e1000_power_down_phy_copper_80003es2lan;
	}

	phy->addr		= 1;
	phy->autoneg_mask	= AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us	= 100;
	phy->type		= e1000_phy_gg82563;

	phy->ops.acquire	= e1000_acquire_phy_80003es2lan;
	phy->ops.check_polarity	= e1000_check_polarity_m88;
	phy->ops.check_reset_block = e1000_check_reset_block_generic;
	phy->ops.commit		= e1000_phy_sw_reset_generic;
	phy->ops.get_cfg_done	= e1000_get_cfg_done_80003es2lan;
	phy->ops.get_info	= e1000_get_phy_info_m88;
	phy->ops.release	= e1000_release_phy_80003es2lan;
	phy->ops.reset		= e1000_phy_hw_reset_generic;
	phy->ops.set_d3_lplu_state = e1000_set_d3_lplu_state_generic;

	phy->ops.force_speed_duplex = e1000_phy_force_speed_duplex_80003es2lan;
	phy->ops.get_cable_length = e1000_get_cable_length_80003es2lan;
	phy->ops.read_reg	= e1000_read_phy_reg_gg82563_80003es2lan;
	phy->ops.write_reg	= e1000_write_phy_reg_gg82563_80003es2lan;

	phy->ops.cfg_on_link_up = e1000_cfg_on_link_up_80003es2lan;

	/* This can only be done after all function pointers are setup. */
	ret_val = e1000_get_phy_id(hw);

	/* Verify phy id */
	if (phy->id != GG82563_E_PHY_ID)
		return -E1000_ERR_PHY;

	return ret_val;
}