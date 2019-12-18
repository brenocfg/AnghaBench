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
struct TYPE_3__ {int /*<<< orphan*/  power_down; int /*<<< orphan*/  power_up; int /*<<< orphan*/  get_info; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  reset; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  get_cfg_done; int /*<<< orphan*/  get_cable_length; int /*<<< orphan*/  force_speed_duplex; int /*<<< orphan*/  commit; int /*<<< orphan*/  check_polarity; } ;
struct e1000_phy_info {int addr; int reset_delay_us; int /*<<< orphan*/  id; TYPE_1__ ops; int /*<<< orphan*/  type; int /*<<< orphan*/  autoneg_mask; } ;
struct TYPE_4__ {int type; } ;
struct e1000_hw {TYPE_2__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 scalar_t__ E1000_ERR_PHY ; 
 int /*<<< orphan*/  M88E1011_I_PHY_ID ; 
#define  e1000_82540 132 
#define  e1000_82545 131 
#define  e1000_82545_rev_3 130 
#define  e1000_82546 129 
#define  e1000_82546_rev_3 128 
 int /*<<< orphan*/  e1000_check_polarity_m88 ; 
 int /*<<< orphan*/  e1000_get_cable_length_m88 ; 
 int /*<<< orphan*/  e1000_get_cfg_done_generic ; 
 scalar_t__ e1000_get_phy_id (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_get_phy_info_m88 ; 
 int /*<<< orphan*/  e1000_phy_force_speed_duplex_m88 ; 
 int /*<<< orphan*/  e1000_phy_hw_reset_generic ; 
 int /*<<< orphan*/  e1000_phy_m88 ; 
 int /*<<< orphan*/  e1000_phy_sw_reset_generic ; 
 int /*<<< orphan*/  e1000_power_down_phy_copper_82540 ; 
 int /*<<< orphan*/  e1000_power_up_phy_copper ; 
 int /*<<< orphan*/  e1000_read_phy_reg_m88 ; 
 int /*<<< orphan*/  e1000_write_phy_reg_m88 ; 

__attribute__((used)) static s32 e1000_init_phy_params_82540(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	phy->addr		= 1;
	phy->autoneg_mask	= AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us	= 10000;
	phy->type		= e1000_phy_m88;

	/* Function Pointers */
	phy->ops.check_polarity	= e1000_check_polarity_m88;
	phy->ops.commit		= e1000_phy_sw_reset_generic;
	phy->ops.force_speed_duplex = e1000_phy_force_speed_duplex_m88;
	phy->ops.get_cable_length = e1000_get_cable_length_m88;
	phy->ops.get_cfg_done	= e1000_get_cfg_done_generic;
	phy->ops.read_reg	= e1000_read_phy_reg_m88;
	phy->ops.reset		= e1000_phy_hw_reset_generic;
	phy->ops.write_reg	= e1000_write_phy_reg_m88;
	phy->ops.get_info	= e1000_get_phy_info_m88;
	phy->ops.power_up	= e1000_power_up_phy_copper;
	phy->ops.power_down	= e1000_power_down_phy_copper_82540;

	ret_val = e1000_get_phy_id(hw);
	if (ret_val)
		goto out;

	/* Verify phy id */
	switch (hw->mac.type) {
	case e1000_82540:
	case e1000_82545:
	case e1000_82545_rev_3:
	case e1000_82546:
	case e1000_82546_rev_3:
		if (phy->id == M88E1011_I_PHY_ID)
			break;
		/* Fall Through */
	default:
		ret_val = -E1000_ERR_PHY;
		goto out;
		break;
	}

out:
	return ret_val;
}