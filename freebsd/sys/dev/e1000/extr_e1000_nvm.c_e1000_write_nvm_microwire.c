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
struct TYPE_2__ {int (* acquire ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {scalar_t__ word_size; scalar_t__ opcode_bits; int address_bits; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_DO ; 
 int E1000_ERR_NVM ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ NVM_EWDS_OPCODE_MICROWIRE ; 
 scalar_t__ NVM_EWEN_OPCODE_MICROWIRE ; 
 scalar_t__ NVM_WRITE_OPCODE_MICROWIRE ; 
 int e1000_ready_nvm_eeprom (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_shift_out_eec_bits (struct e1000_hw*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  e1000_standby_nvm (struct e1000_hw*) ; 
 int stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_write_nvm_microwire(struct e1000_hw *hw, u16 offset, u16 words,
			      u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	s32  ret_val;
	u32 eecd;
	u16 words_written = 0;
	u16 widx = 0;

	DEBUGFUNC("e1000_write_nvm_microwire");

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

	e1000_shift_out_eec_bits(hw, NVM_EWEN_OPCODE_MICROWIRE,
				 (u16)(nvm->opcode_bits + 2));

	e1000_shift_out_eec_bits(hw, 0, (u16)(nvm->address_bits - 2));

	e1000_standby_nvm(hw);

	while (words_written < words) {
		e1000_shift_out_eec_bits(hw, NVM_WRITE_OPCODE_MICROWIRE,
					 nvm->opcode_bits);

		e1000_shift_out_eec_bits(hw, (u16)(offset + words_written),
					 nvm->address_bits);

		e1000_shift_out_eec_bits(hw, data[words_written], 16);

		e1000_standby_nvm(hw);

		for (widx = 0; widx < 200; widx++) {
			eecd = E1000_READ_REG(hw, E1000_EECD);
			if (eecd & E1000_EECD_DO)
				break;
			usec_delay(50);
		}

		if (widx == 200) {
			DEBUGOUT("NVM Write did not complete\n");
			ret_val = -E1000_ERR_NVM;
			goto release;
		}

		e1000_standby_nvm(hw);

		words_written++;
	}

	e1000_shift_out_eec_bits(hw, NVM_EWDS_OPCODE_MICROWIRE,
				 (u16)(nvm->opcode_bits + 2));

	e1000_shift_out_eec_bits(hw, 0, (u16)(nvm->address_bits - 2));

release:
	nvm->ops.release(hw);

	return ret_val;
}