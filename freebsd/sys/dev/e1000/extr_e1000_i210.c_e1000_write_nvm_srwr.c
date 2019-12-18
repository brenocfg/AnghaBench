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
typedef  scalar_t__ u16 ;
struct e1000_nvm_info {scalar_t__ word_size; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 scalar_t__ E1000_NVM_RW_ADDR_SHIFT ; 
 scalar_t__ E1000_NVM_RW_REG_DATA ; 
 int E1000_NVM_RW_REG_DONE ; 
 scalar_t__ E1000_NVM_RW_REG_START ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SRWR ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_write_nvm_srwr(struct e1000_hw *hw, u16 offset, u16 words,
				u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 i, k, eewr = 0;
	u32 attempts = 100000;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_write_nvm_srwr");

	/*
	 * A check for invalid values:  offset too large, too many words,
	 * too many words for the offset, and not enough words.
	 */
	if ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) {
		DEBUGOUT("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		goto out;
	}

	for (i = 0; i < words; i++) {
		eewr = ((offset+i) << E1000_NVM_RW_ADDR_SHIFT) |
			(data[i] << E1000_NVM_RW_REG_DATA) |
			E1000_NVM_RW_REG_START;

		E1000_WRITE_REG(hw, E1000_SRWR, eewr);

		for (k = 0; k < attempts; k++) {
			if (E1000_NVM_RW_REG_DONE &
			    E1000_READ_REG(hw, E1000_SRWR)) {
				ret_val = E1000_SUCCESS;
				break;
			}
			usec_delay(5);
		}

		if (ret_val != E1000_SUCCESS) {
			DEBUGOUT("Shadow RAM write EEWR timed out\n");
			break;
		}
	}

out:
	return ret_val;
}