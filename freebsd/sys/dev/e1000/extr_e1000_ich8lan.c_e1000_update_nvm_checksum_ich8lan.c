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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  (* reload ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {scalar_t__ type; scalar_t__ flash_bank_size; TYPE_3__ ops; } ;
struct e1000_dev_spec_ich8lan {TYPE_2__* shadow_ram; } ;
struct TYPE_4__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_1__ dev_spec; struct e1000_nvm_info nvm; } ;
typedef  scalar_t__ s32 ;
struct TYPE_5__ {int value; scalar_t__ modified; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,scalar_t__) ; 
 int E1000_ICH_NVM_SIG_MASK ; 
 scalar_t__ E1000_ICH_NVM_SIG_WORD ; 
 scalar_t__ E1000_SHADOW_RAM_WORDS ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ e1000_erase_flash_bank_ich8lan (struct e1000_hw*,int) ; 
 scalar_t__ e1000_nvm_flash_sw ; 
 scalar_t__ e1000_read_flash_word_ich8lan (struct e1000_hw*,scalar_t__,int*) ; 
 scalar_t__ e1000_retry_write_flash_byte_ich8lan (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_update_nvm_checksum_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_valid_nvm_bank_detect_ich8lan (struct e1000_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_update_nvm_checksum_ich8lan(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 i, act_offset, new_bank_offset, old_bank_offset, bank;
	s32 ret_val;
	u16 data = 0;

	DEBUGFUNC("e1000_update_nvm_checksum_ich8lan");

	ret_val = e1000_update_nvm_checksum_generic(hw);
	if (ret_val)
		goto out;

	if (nvm->type != e1000_nvm_flash_sw)
		goto out;

	nvm->ops.acquire(hw);

	/* We're writing to the opposite bank so if we're on bank 1,
	 * write to bank 0 etc.  We also need to erase the segment that
	 * is going to be written
	 */
	ret_val =  e1000_valid_nvm_bank_detect_ich8lan(hw, &bank);
	if (ret_val != E1000_SUCCESS) {
		DEBUGOUT("Could not detect valid bank, assuming bank 0\n");
		bank = 0;
	}

	if (bank == 0) {
		new_bank_offset = nvm->flash_bank_size;
		old_bank_offset = 0;
		ret_val = e1000_erase_flash_bank_ich8lan(hw, 1);
		if (ret_val)
			goto release;
	} else {
		old_bank_offset = nvm->flash_bank_size;
		new_bank_offset = 0;
		ret_val = e1000_erase_flash_bank_ich8lan(hw, 0);
		if (ret_val)
			goto release;
	}
	for (i = 0; i < E1000_SHADOW_RAM_WORDS; i++) {
		if (dev_spec->shadow_ram[i].modified) {
			data = dev_spec->shadow_ram[i].value;
		} else {
			ret_val = e1000_read_flash_word_ich8lan(hw, i +
								old_bank_offset,
								&data);
			if (ret_val)
				break;
		}
		/* If the word is 0x13, then make sure the signature bits
		 * (15:14) are 11b until the commit has completed.
		 * This will allow us to write 10b which indicates the
		 * signature is valid.  We want to do this after the write
		 * has completed so that we don't mark the segment valid
		 * while the write is still in progress
		 */
		if (i == E1000_ICH_NVM_SIG_WORD)
			data |= E1000_ICH_NVM_SIG_MASK;

		/* Convert offset to bytes. */
		act_offset = (i + new_bank_offset) << 1;

		usec_delay(100);

		/* Write the bytes to the new bank. */
		ret_val = e1000_retry_write_flash_byte_ich8lan(hw,
							       act_offset,
							       (u8)data);
		if (ret_val)
			break;

		usec_delay(100);
		ret_val = e1000_retry_write_flash_byte_ich8lan(hw,
							  act_offset + 1,
							  (u8)(data >> 8));
		if (ret_val)
			break;
	 }

	/* Don't bother writing the segment valid bits if sector
	 * programming failed.
	 */
	if (ret_val) {
		DEBUGOUT("Flash commit failed.\n");
		goto release;
	}

	/* Finally validate the new segment by setting bit 15:14
	 * to 10b in word 0x13 , this can be done without an
	 * erase as well since these bits are 11 to start with
	 * and we need to change bit 14 to 0b
	 */
	act_offset = new_bank_offset + E1000_ICH_NVM_SIG_WORD;
	ret_val = e1000_read_flash_word_ich8lan(hw, act_offset, &data);
	if (ret_val)
		goto release;

	data &= 0xBFFF;
	ret_val = e1000_retry_write_flash_byte_ich8lan(hw, act_offset * 2 + 1,
						       (u8)(data >> 8));
	if (ret_val)
		goto release;

	/* And invalidate the previously valid segment by setting
	 * its signature word (0x13) high_byte to 0b. This can be
	 * done without an erase because flash erase sets all bits
	 * to 1's. We can write 1's to 0's without an erase
	 */
	act_offset = (old_bank_offset + E1000_ICH_NVM_SIG_WORD) * 2 + 1;

	ret_val = e1000_retry_write_flash_byte_ich8lan(hw, act_offset, 0);

	if (ret_val)
		goto release;

	/* Great!  Everything worked, we can now clear the cached entries. */
	for (i = 0; i < E1000_SHADOW_RAM_WORDS; i++) {
		dev_spec->shadow_ram[i].modified = FALSE;
		dev_spec->shadow_ram[i].value = 0xFFFF;
	}

release:
	nvm->ops.release(hw);

	/* Reload the EEPROM, or else modifications will not appear
	 * until after the next adapter reset.
	 */
	if (!ret_val) {
		nvm->ops.reload(hw);
		msec_delay(10);
	}

out:
	if (ret_val)
		DEBUGOUT1("NVM update error: %d\n", ret_val);

	return ret_val;
}