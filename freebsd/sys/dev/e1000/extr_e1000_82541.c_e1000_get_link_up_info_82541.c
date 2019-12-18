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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct e1000_phy_info {TYPE_1__ ops; int /*<<< orphan*/  speed_downgraded; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ HALF_DUPLEX ; 
 scalar_t__ NWAY_ER_LP_NWAY_CAPS ; 
 scalar_t__ NWAY_LPAR_100TX_FD_CAPS ; 
 scalar_t__ NWAY_LPAR_10T_FD_CAPS ; 
 int /*<<< orphan*/  PHY_AUTONEG_EXP ; 
 int /*<<< orphan*/  PHY_LP_ABILITY ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ e1000_get_speed_and_duplex_copper_generic (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static s32 e1000_get_link_up_info_82541(struct e1000_hw *hw, u16 *speed,
					u16 *duplex)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	DEBUGFUNC("e1000_get_link_up_info_82541");

	ret_val = e1000_get_speed_and_duplex_copper_generic(hw, speed, duplex);
	if (ret_val)
		goto out;

	if (!phy->speed_downgraded)
		goto out;

	/*
	 * IGP01 PHY may advertise full duplex operation after speed
	 * downgrade even if it is operating at half duplex.
	 * Here we set the duplex settings to match the duplex in the
	 * link partner's capabilities.
	 */
	ret_val = phy->ops.read_reg(hw, PHY_AUTONEG_EXP, &data);
	if (ret_val)
		goto out;

	if (!(data & NWAY_ER_LP_NWAY_CAPS)) {
		*duplex = HALF_DUPLEX;
	} else {
		ret_val = phy->ops.read_reg(hw, PHY_LP_ABILITY, &data);
		if (ret_val)
			goto out;

		if (*speed == SPEED_100) {
			if (!(data & NWAY_LPAR_100TX_FD_CAPS))
				*duplex = HALF_DUPLEX;
		} else if (*speed == SPEED_10) {
			if (!(data & NWAY_LPAR_10T_FD_CAPS))
				*duplex = HALF_DUPLEX;
		}
	}

out:
	return ret_val;
}