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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {scalar_t__ word_size; TYPE_1__ ops; int /*<<< orphan*/  address_bits; int /*<<< orphan*/  opcode_bits; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_ERR_NVM ; 
 scalar_t__ NVM_READ_OPCODE_MICROWIRE ; 
 scalar_t__ e1000_ready_nvm_eeprom (struct e1000_hw*) ; 
 scalar_t__ e1000_shift_in_eec_bits (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1000_shift_out_eec_bits (struct e1000_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_standby_nvm (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

s32 e1000_read_nvm_microwire(struct e1000_hw *hw, u16 offset, u16 words,
			     u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 i = 0;
	s32 ret_val;
	u8 read_opcode = NVM_READ_OPCODE_MICROWIRE;

	DEBUGFUNC("e1000_read_nvm_microwire");

	/* A check for invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	if ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) {
		DEBUGOUT("nvm parameter(s) out of bounds\n");
		return -E1000_ERR_NVM;
	}

	ret_val = nvm->ops.acquire(hw);
	if (ret_val)
		return ret_val;

	ret_val = e1000_ready_nvm_eeprom(hw);
	if (ret_val)
		goto release;

	for (i = 0; i < words; i++) {
		/* Send the READ command (opcode + addr) */
		e1000_shift_out_eec_bits(hw, read_opcode, nvm->opcode_bits);
		e1000_shift_out_eec_bits(hw, (u16)(offset + i),
					nvm->address_bits);

		/* Read the data.  For microwire, each word requires the
		 * overhead of setup and tear-down.
		 */
		data[i] = e1000_shift_in_eec_bits(hw, 16);
		e1000_standby_nvm(hw);
	}

release:
	nvm->ops.release(hw);

	return ret_val;
}