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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct e1000_phy_info {scalar_t__ type; scalar_t__ smart_speed; TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_PHY_CTRL ; 
 int /*<<< orphan*/  E1000_PHY_CTRL_D0A_LPLU ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CONFIG ; 
 int /*<<< orphan*/  IGP01E1000_PSCFR_SMART_SPEED ; 
 int /*<<< orphan*/  e1000_gig_downshift_workaround_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_ich8lan ; 
 scalar_t__ e1000_phy_ife ; 
 scalar_t__ e1000_phy_igp_3 ; 
 scalar_t__ e1000_smart_speed_off ; 
 scalar_t__ e1000_smart_speed_on ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_set_d0_lplu_state_ich8lan(struct e1000_hw *hw, bool active)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 phy_ctrl;
	s32 ret_val = E1000_SUCCESS;
	u16 data;

	DEBUGFUNC("e1000_set_d0_lplu_state_ich8lan");

	if (phy->type == e1000_phy_ife)
		return E1000_SUCCESS;

	phy_ctrl = E1000_READ_REG(hw, E1000_PHY_CTRL);

	if (active) {
		phy_ctrl |= E1000_PHY_CTRL_D0A_LPLU;
		E1000_WRITE_REG(hw, E1000_PHY_CTRL, phy_ctrl);

		if (phy->type != e1000_phy_igp_3)
			return E1000_SUCCESS;

		/* Call gig speed drop workaround on LPLU before accessing
		 * any PHY registers
		 */
		if (hw->mac.type == e1000_ich8lan)
			e1000_gig_downshift_workaround_ich8lan(hw);

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = phy->ops.read_reg(hw,
					    IGP01E1000_PHY_PORT_CONFIG,
					    &data);
		if (ret_val)
			return ret_val;
		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = phy->ops.write_reg(hw,
					     IGP01E1000_PHY_PORT_CONFIG,
					     data);
		if (ret_val)
			return ret_val;
	} else {
		phy_ctrl &= ~E1000_PHY_CTRL_D0A_LPLU;
		E1000_WRITE_REG(hw, E1000_PHY_CTRL, phy_ctrl);

		if (phy->type != e1000_phy_igp_3)
			return E1000_SUCCESS;

		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the power conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so performance is maintained.
		 */
		if (phy->smart_speed == e1000_smart_speed_on) {
			ret_val = phy->ops.read_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			if (ret_val)
				return ret_val;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			if (ret_val)
				return ret_val;
		} else if (phy->smart_speed == e1000_smart_speed_off) {
			ret_val = phy->ops.read_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			if (ret_val)
				return ret_val;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			if (ret_val)
				return ret_val;
		}
	}

	return E1000_SUCCESS;
}