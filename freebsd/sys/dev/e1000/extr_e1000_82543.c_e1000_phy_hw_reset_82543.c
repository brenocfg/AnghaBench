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
struct TYPE_4__ {int /*<<< orphan*/  (* get_cfg_done ) (struct e1000_hw*) ;} ;
struct TYPE_3__ {TYPE_2__ ops; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_SDP4_DATA ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_SDP4_DIR ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_phy_hw_reset_82543(struct e1000_hw *hw)
{
	u32 ctrl_ext;
	s32 ret_val;

	DEBUGFUNC("e1000_phy_hw_reset_82543");

	/*
	 * Read the Extended Device Control Register, assert the PHY_RESET_DIR
	 * bit to put the PHY into reset...
	 */
	ctrl_ext = E1000_READ_REG(hw, E1000_CTRL_EXT);
	ctrl_ext |= E1000_CTRL_EXT_SDP4_DIR;
	ctrl_ext &= ~E1000_CTRL_EXT_SDP4_DATA;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);
	E1000_WRITE_FLUSH(hw);

	msec_delay(10);

	/* ...then take it out of reset. */
	ctrl_ext |= E1000_CTRL_EXT_SDP4_DATA;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);
	E1000_WRITE_FLUSH(hw);

	usec_delay(150);

	if (!(hw->phy.ops.get_cfg_done))
		return E1000_SUCCESS;

	ret_val = hw->phy.ops.get_cfg_done(hw);

	return ret_val;
}