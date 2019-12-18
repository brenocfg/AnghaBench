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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_phy_info {scalar_t__ smart_speed; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_82580_PHY_POWER_MGMT ; 
 int /*<<< orphan*/  E1000_82580_PM_D0_LPLU ; 
 int /*<<< orphan*/  E1000_82580_PM_SPD ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_smart_speed_off ; 
 scalar_t__ e1000_smart_speed_on ; 

__attribute__((used)) static s32 e1000_set_d0_lplu_state_82580(struct e1000_hw *hw, bool active)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 data;

	DEBUGFUNC("e1000_set_d0_lplu_state_82580");

	data = E1000_READ_REG(hw, E1000_82580_PHY_POWER_MGMT);

	if (active) {
		data |= E1000_82580_PM_D0_LPLU;

		/* When LPLU is enabled, we should disable SmartSpeed */
		data &= ~E1000_82580_PM_SPD;
	} else {
		data &= ~E1000_82580_PM_D0_LPLU;

		/*
		 * LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the power conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so performance is maintained.
		 */
		if (phy->smart_speed == e1000_smart_speed_on)
			data |= E1000_82580_PM_SPD;
		else if (phy->smart_speed == e1000_smart_speed_off)
			data &= ~E1000_82580_PM_SPD;
	}

	E1000_WRITE_REG(hw, E1000_82580_PHY_POWER_MGMT, data);
	return E1000_SUCCESS;
}