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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_FLUPD ; 
 scalar_t__ E1000_ERR_NVM ; 
 scalar_t__ E1000_FLASH_UPDATES ; 
 int /*<<< orphan*/  E1000_FLOP ; 
 int /*<<< orphan*/  E1000_HICR ; 
 int E1000_HICR_FW_RESET ; 
 int E1000_HICR_FW_RESET_ENABLE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int E1000_STM_OPCODE ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_nvm_flash_hw ; 
 scalar_t__ e1000_update_nvm_checksum_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static s32 e1000_update_nvm_checksum_82571(struct e1000_hw *hw)
{
	u32 eecd;
	s32 ret_val;
	u16 i;

	DEBUGFUNC("e1000_update_nvm_checksum_82571");

	ret_val = e1000_update_nvm_checksum_generic(hw);
	if (ret_val)
		return ret_val;

	/* If our nvm is an EEPROM, then we're done
	 * otherwise, commit the checksum to the flash NVM.
	 */
	if (hw->nvm.type != e1000_nvm_flash_hw)
		return E1000_SUCCESS;

	/* Check for pending operations. */
	for (i = 0; i < E1000_FLASH_UPDATES; i++) {
		msec_delay(1);
		if (!(E1000_READ_REG(hw, E1000_EECD) & E1000_EECD_FLUPD))
			break;
	}

	if (i == E1000_FLASH_UPDATES)
		return -E1000_ERR_NVM;

	/* Reset the firmware if using STM opcode. */
	if ((E1000_READ_REG(hw, E1000_FLOP) & 0xFF00) == E1000_STM_OPCODE) {
		/* The enabling of and the actual reset must be done
		 * in two write cycles.
		 */
		E1000_WRITE_REG(hw, E1000_HICR, E1000_HICR_FW_RESET_ENABLE);
		E1000_WRITE_FLUSH(hw);
		E1000_WRITE_REG(hw, E1000_HICR, E1000_HICR_FW_RESET);
	}

	/* Commit the write to flash */
	eecd = E1000_READ_REG(hw, E1000_EECD) | E1000_EECD_FLUPD;
	E1000_WRITE_REG(hw, E1000_EECD, eecd);

	for (i = 0; i < E1000_FLASH_UPDATES; i++) {
		msec_delay(1);
		if (!(E1000_READ_REG(hw, E1000_EECD) & E1000_EECD_FLUPD))
			break;
	}

	if (i == E1000_FLASH_UPDATES)
		return -E1000_ERR_NVM;

	return E1000_SUCCESS;
}