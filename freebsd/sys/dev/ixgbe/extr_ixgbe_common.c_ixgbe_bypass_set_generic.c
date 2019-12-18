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
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int BYPASS_PAGE_CTL0 ; 
 int BYPASS_PAGE_M ; 
 int BYPASS_WE ; 
 int /*<<< orphan*/  IXGBE_BYPASS_FW_WRITE_FAILURE ; 
 int /*<<< orphan*/  IXGBE_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_bypass_rw_generic (struct ixgbe_hw*,int,int*) ; 
 int /*<<< orphan*/  ixgbe_bypass_valid_rd_generic (int,int) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_bypass_set_generic(struct ixgbe_hw *hw, u32 ctrl, u32 event,
			     u32 action)
{
	u32 by_ctl = 0;
	u32 cmd, verify;
	u32 count = 0;

	/* Get current values */
	cmd = ctrl;	/* just reading only need control number */
	if (ixgbe_bypass_rw_generic(hw, cmd, &by_ctl))
		return IXGBE_ERR_INVALID_ARGUMENT;

	/* Set to new action */
	cmd = (by_ctl & ~event) | BYPASS_WE | action;
	if (ixgbe_bypass_rw_generic(hw, cmd, &by_ctl))
		return IXGBE_ERR_INVALID_ARGUMENT;

	/* Page 0 force a FW eeprom write which is slow so verify */
	if ((cmd & BYPASS_PAGE_M) == BYPASS_PAGE_CTL0) {
		verify = BYPASS_PAGE_CTL0;
		do {
			if (count++ > 5)
				return IXGBE_BYPASS_FW_WRITE_FAILURE;

			if (ixgbe_bypass_rw_generic(hw, verify, &by_ctl))
				return IXGBE_ERR_INVALID_ARGUMENT;
		} while (!ixgbe_bypass_valid_rd_generic(cmd, by_ctl));
	} else {
		/* We have give the FW time for the write to stick */
		msec_delay(100);
	}

	return IXGBE_SUCCESS;
}