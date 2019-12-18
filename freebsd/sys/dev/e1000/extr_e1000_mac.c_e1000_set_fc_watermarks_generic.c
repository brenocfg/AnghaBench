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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int current_mode; int /*<<< orphan*/  high_water; scalar_t__ send_xon; int /*<<< orphan*/  low_water; } ;
struct e1000_hw {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_FCRTH ; 
 int /*<<< orphan*/  E1000_FCRTL ; 
 int /*<<< orphan*/  E1000_FCRTL_XONE ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int e1000_fc_tx_pause ; 

s32 e1000_set_fc_watermarks_generic(struct e1000_hw *hw)
{
	u32 fcrtl = 0, fcrth = 0;

	DEBUGFUNC("e1000_set_fc_watermarks_generic");

	/* Set the flow control receive threshold registers.  Normally,
	 * these registers will be set to a default threshold that may be
	 * adjusted later by the driver's runtime code.  However, if the
	 * ability to transmit pause frames is not enabled, then these
	 * registers will be set to 0.
	 */
	if (hw->fc.current_mode & e1000_fc_tx_pause) {
		/* We need to set up the Receive Threshold high and low water
		 * marks as well as (optionally) enabling the transmission of
		 * XON frames.
		 */
		fcrtl = hw->fc.low_water;
		if (hw->fc.send_xon)
			fcrtl |= E1000_FCRTL_XONE;

		fcrth = hw->fc.high_water;
	}
	E1000_WRITE_REG(hw, E1000_FCRTL, fcrtl);
	E1000_WRITE_REG(hw, E1000_FCRTH, fcrth);

	return E1000_SUCCESS;
}