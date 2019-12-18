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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {scalar_t__ revision_id; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_EEC_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_EEC_FLUP ; 
 int IXGBE_EEC_SEC1VAL ; 
 scalar_t__ IXGBE_ERR_EEPROM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_mac_X540 ; 
 scalar_t__ ixgbe_poll_flash_update_done_X540 (struct ixgbe_hw*) ; 

s32 ixgbe_update_flash_X540(struct ixgbe_hw *hw)
{
	u32 flup;
	s32 status;

	DEBUGFUNC("ixgbe_update_flash_X540");

	status = ixgbe_poll_flash_update_done_X540(hw);
	if (status == IXGBE_ERR_EEPROM) {
		DEBUGOUT("Flash update time out\n");
		goto out;
	}

	flup = IXGBE_READ_REG(hw, IXGBE_EEC_BY_MAC(hw)) | IXGBE_EEC_FLUP;
	IXGBE_WRITE_REG(hw, IXGBE_EEC_BY_MAC(hw), flup);

	status = ixgbe_poll_flash_update_done_X540(hw);
	if (status == IXGBE_SUCCESS)
		DEBUGOUT("Flash update complete\n");
	else
		DEBUGOUT("Flash update time out\n");

	if (hw->mac.type == ixgbe_mac_X540 && hw->revision_id == 0) {
		flup = IXGBE_READ_REG(hw, IXGBE_EEC_BY_MAC(hw));

		if (flup & IXGBE_EEC_SEC1VAL) {
			flup |= IXGBE_EEC_FLUP;
			IXGBE_WRITE_REG(hw, IXGBE_EEC_BY_MAC(hw), flup);
		}

		status = ixgbe_poll_flash_update_done_X540(hw);
		if (status == IXGBE_SUCCESS)
			DEBUGOUT("Flash update complete\n");
		else
			DEBUGOUT("Flash update time out\n");
	}
out:
	return status;
}