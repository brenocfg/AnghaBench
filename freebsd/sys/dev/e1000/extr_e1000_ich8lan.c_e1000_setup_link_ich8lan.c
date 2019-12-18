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
struct TYPE_10__ {scalar_t__ requested_mode; scalar_t__ current_mode; int /*<<< orphan*/  pause_time; int /*<<< orphan*/  refresh_time; } ;
struct TYPE_8__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* check_reset_block ) (struct e1000_hw*) ;} ;
struct TYPE_9__ {scalar_t__ type; TYPE_3__ ops; } ;
struct TYPE_6__ {scalar_t__ (* setup_physical_interface ) (struct e1000_hw*) ;} ;
struct TYPE_7__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_5__ fc; TYPE_4__ phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_PORT_CTRL_PAGE ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  E1000_FCRTV_PCH ; 
 int /*<<< orphan*/  E1000_FCTTV ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_fc_default ; 
 scalar_t__ e1000_fc_full ; 
 scalar_t__ e1000_phy_82577 ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1000_phy_82579 ; 
 scalar_t__ e1000_phy_i217 ; 
 scalar_t__ e1000_set_fc_watermarks_generic (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_setup_link_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val;

	DEBUGFUNC("e1000_setup_link_ich8lan");

	if (hw->phy.ops.check_reset_block(hw))
		return E1000_SUCCESS;

	/* ICH parts do not have a word in the NVM to determine
	 * the default flow control setting, so we explicitly
	 * set it to full.
	 */
	if (hw->fc.requested_mode == e1000_fc_default)
		hw->fc.requested_mode = e1000_fc_full;

	/* Save off the requested flow control mode for use later.  Depending
	 * on the link partner's capabilities, we may or may not use this mode.
	 */
	hw->fc.current_mode = hw->fc.requested_mode;

	DEBUGOUT1("After fix-ups FlowControl is now = %x\n",
		hw->fc.current_mode);

	/* Continue to configure the copper link. */
	ret_val = hw->mac.ops.setup_physical_interface(hw);
	if (ret_val)
		return ret_val;

	E1000_WRITE_REG(hw, E1000_FCTTV, hw->fc.pause_time);
	if ((hw->phy.type == e1000_phy_82578) ||
	    (hw->phy.type == e1000_phy_82579) ||
	    (hw->phy.type == e1000_phy_i217) ||
	    (hw->phy.type == e1000_phy_82577)) {
		E1000_WRITE_REG(hw, E1000_FCRTV_PCH, hw->fc.refresh_time);

		ret_val = hw->phy.ops.write_reg(hw,
					     PHY_REG(BM_PORT_CTRL_PAGE, 27),
					     hw->fc.pause_time);
		if (ret_val)
			return ret_val;
	}

	return e1000_set_fc_watermarks_generic(hw);
}