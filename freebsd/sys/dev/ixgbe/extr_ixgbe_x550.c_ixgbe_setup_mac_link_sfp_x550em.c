#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {scalar_t__ (* write_link ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  addr; TYPE_2__ ops; } ;
struct TYPE_4__ {int lan_id; } ;
struct ixgbe_hw {TYPE_3__ link; TYPE_1__ bus; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int FALSE ; 
 int IXGBE_CS4227_EDC_MODE_CX1 ; 
 int IXGBE_CS4227_EDC_MODE_SR ; 
 int IXGBE_CS4227_LINE_SPARE24_LSB ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_PRESENT ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int) ; 
 int /*<<< orphan*/  ixgbe_setup_kr_speed_x550em (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_supported_sfp_modules_X550em (struct ixgbe_hw*,int*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int,int) ; 

s32 ixgbe_setup_mac_link_sfp_x550em(struct ixgbe_hw *hw,
				    ixgbe_link_speed speed,
				    bool autoneg_wait_to_complete)
{
	s32 ret_val;
	u16 reg_slice, reg_val;
	bool setup_linear = FALSE;
	UNREFERENCED_1PARAMETER(autoneg_wait_to_complete);

	/* Check if SFP module is supported and linear */
	ret_val = ixgbe_supported_sfp_modules_X550em(hw, &setup_linear);

	/* If no SFP module present, then return success. Return success since
	 * there is no reason to configure CS4227 and SFP not present error is
	 * not excepted in the setup MAC link flow.
	 */
	if (ret_val == IXGBE_ERR_SFP_NOT_PRESENT)
		return IXGBE_SUCCESS;

	if (ret_val != IXGBE_SUCCESS)
		return ret_val;

	/* Configure internal PHY for KR/KX. */
	ixgbe_setup_kr_speed_x550em(hw, speed);

	/* Configure CS4227 LINE side to proper mode. */
	reg_slice = IXGBE_CS4227_LINE_SPARE24_LSB +
		    (hw->bus.lan_id << 12);
	if (setup_linear)
		reg_val = (IXGBE_CS4227_EDC_MODE_CX1 << 1) | 0x1;
	else
		reg_val = (IXGBE_CS4227_EDC_MODE_SR << 1) | 0x1;
	ret_val = hw->link.ops.write_link(hw, hw->link.addr, reg_slice,
					  reg_val);
	return ret_val;
}