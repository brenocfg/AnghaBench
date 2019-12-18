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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IXGBE_EEC_BY_MAC (struct ixgbe_hw*) ; 
 scalar_t__ IXGBE_EEC_FLUDONE ; 
 int /*<<< orphan*/  IXGBE_ERROR_POLLING ; 
 int /*<<< orphan*/  IXGBE_ERR_EEPROM ; 
 scalar_t__ IXGBE_FLUDONE_ATTEMPTS ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static s32 ixgbe_poll_flash_update_done_X540(struct ixgbe_hw *hw)
{
	u32 i;
	u32 reg;
	s32 status = IXGBE_ERR_EEPROM;

	DEBUGFUNC("ixgbe_poll_flash_update_done_X540");

	for (i = 0; i < IXGBE_FLUDONE_ATTEMPTS; i++) {
		reg = IXGBE_READ_REG(hw, IXGBE_EEC_BY_MAC(hw));
		if (reg & IXGBE_EEC_FLUDONE) {
			status = IXGBE_SUCCESS;
			break;
		}
		msec_delay(5);
	}

	if (i == IXGBE_FLUDONE_ATTEMPTS)
		ERROR_REPORT1(IXGBE_ERROR_POLLING,
			     "Flash update status polling timed out");

	return status;
}