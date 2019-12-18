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
 scalar_t__ IXGBE_EEPROM_RW_REG_DONE ; 
 int /*<<< orphan*/  IXGBE_EERD ; 
 scalar_t__ IXGBE_EERD_EEWR_ATTEMPTS ; 
 int /*<<< orphan*/  IXGBE_EEWR ; 
 int /*<<< orphan*/  IXGBE_ERROR_POLLING ; 
 int /*<<< orphan*/  IXGBE_ERR_EEPROM ; 
 scalar_t__ IXGBE_NVM_POLL_READ ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 ixgbe_poll_eerd_eewr_done(struct ixgbe_hw *hw, u32 ee_reg)
{
	u32 i;
	u32 reg;
	s32 status = IXGBE_ERR_EEPROM;

	DEBUGFUNC("ixgbe_poll_eerd_eewr_done");

	for (i = 0; i < IXGBE_EERD_EEWR_ATTEMPTS; i++) {
		if (ee_reg == IXGBE_NVM_POLL_READ)
			reg = IXGBE_READ_REG(hw, IXGBE_EERD);
		else
			reg = IXGBE_READ_REG(hw, IXGBE_EEWR);

		if (reg & IXGBE_EEPROM_RW_REG_DONE) {
			status = IXGBE_SUCCESS;
			break;
		}
		usec_delay(5);
	}

	if (i == IXGBE_EERD_EEWR_ATTEMPTS)
		ERROR_REPORT1(IXGBE_ERROR_POLLING,
			     "EEPROM read/write done polling timed out");

	return status;
}