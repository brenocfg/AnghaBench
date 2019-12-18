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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_params ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {scalar_t__ word_size; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IXGBE_EEPROM_RW_ADDR_SHIFT ; 
 scalar_t__ IXGBE_EEPROM_RW_REG_DATA ; 
 scalar_t__ IXGBE_EEPROM_RW_REG_START ; 
 int /*<<< orphan*/  IXGBE_EEWR ; 
 int /*<<< orphan*/  IXGBE_ERROR_ARGUMENT ; 
 scalar_t__ IXGBE_ERR_EEPROM ; 
 scalar_t__ IXGBE_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  IXGBE_NVM_POLL_WRITE ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ixgbe_poll_eerd_eewr_done (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

s32 ixgbe_write_eewr_buffer_generic(struct ixgbe_hw *hw, u16 offset,
				    u16 words, u16 *data)
{
	u32 eewr;
	s32 status = IXGBE_SUCCESS;
	u16 i;

	DEBUGFUNC("ixgbe_write_eewr_generic");

	hw->eeprom.ops.init_params(hw);

	if (words == 0) {
		status = IXGBE_ERR_INVALID_ARGUMENT;
		ERROR_REPORT1(IXGBE_ERROR_ARGUMENT, "Invalid EEPROM words");
		goto out;
	}

	if (offset >= hw->eeprom.word_size) {
		status = IXGBE_ERR_EEPROM;
		ERROR_REPORT1(IXGBE_ERROR_ARGUMENT, "Invalid EEPROM offset");
		goto out;
	}

	for (i = 0; i < words; i++) {
		eewr = ((offset + i) << IXGBE_EEPROM_RW_ADDR_SHIFT) |
			(data[i] << IXGBE_EEPROM_RW_REG_DATA) |
			IXGBE_EEPROM_RW_REG_START;

		status = ixgbe_poll_eerd_eewr_done(hw, IXGBE_NVM_POLL_WRITE);
		if (status != IXGBE_SUCCESS) {
			DEBUGOUT("Eeprom write EEWR timed out\n");
			goto out;
		}

		IXGBE_WRITE_REG(hw, IXGBE_EEWR, eewr);

		status = ixgbe_poll_eerd_eewr_done(hw, IXGBE_NVM_POLL_WRITE);
		if (status != IXGBE_SUCCESS) {
			DEBUGOUT("Eeprom write EEWR timed out\n");
			goto out;
		}
	}

out:
	return status;
}