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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_nvm_info {int flash_bank_size; } ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_SEC1VAL ; 
 int E1000_EECD_SEC1VAL_VALID_MASK ; 
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 int E1000_ICH_NVM_SIG_VALUE ; 
 int E1000_ICH_NVM_SIG_WORD ; 
 int E1000_ICH_NVM_VALID_SIG_MASK ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
#define  e1000_ich8lan 131 
#define  e1000_ich9lan 130 
#define  e1000_pch_cnp 129 
#define  e1000_pch_spt 128 
 int /*<<< orphan*/  e1000_read_flash_byte_ich8lan (struct e1000_hw*,int,int*) ; 
 int /*<<< orphan*/  e1000_read_flash_dword_ich8lan (struct e1000_hw*,int,int*) ; 

__attribute__((used)) static s32 e1000_valid_nvm_bank_detect_ich8lan(struct e1000_hw *hw, u32 *bank)
{
	u32 eecd;
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 bank1_offset = nvm->flash_bank_size * sizeof(u16);
	u32 act_offset = E1000_ICH_NVM_SIG_WORD * 2 + 1;
	u32 nvm_dword = 0;
	u8 sig_byte = 0;
	s32 ret_val;

	DEBUGFUNC("e1000_valid_nvm_bank_detect_ich8lan");

	switch (hw->mac.type) {
	case e1000_pch_spt:
	case e1000_pch_cnp:
		bank1_offset = nvm->flash_bank_size;
		act_offset = E1000_ICH_NVM_SIG_WORD;

		/* set bank to 0 in case flash read fails */
		*bank = 0;

		/* Check bank 0 */
		ret_val = e1000_read_flash_dword_ich8lan(hw, act_offset,
							 &nvm_dword);
		if (ret_val)
			return ret_val;
		sig_byte = (u8)((nvm_dword & 0xFF00) >> 8);
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 0;
			return E1000_SUCCESS;
		}

		/* Check bank 1 */
		ret_val = e1000_read_flash_dword_ich8lan(hw, act_offset +
							 bank1_offset,
							 &nvm_dword);
		if (ret_val)
			return ret_val;
		sig_byte = (u8)((nvm_dword & 0xFF00) >> 8);
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 1;
			return E1000_SUCCESS;
		}

		DEBUGOUT("ERROR: No valid NVM bank present\n");
		return -E1000_ERR_NVM;
	case e1000_ich8lan:
	case e1000_ich9lan:
		eecd = E1000_READ_REG(hw, E1000_EECD);
		if ((eecd & E1000_EECD_SEC1VAL_VALID_MASK) ==
		    E1000_EECD_SEC1VAL_VALID_MASK) {
			if (eecd & E1000_EECD_SEC1VAL)
				*bank = 1;
			else
				*bank = 0;

			return E1000_SUCCESS;
		}
		DEBUGOUT("Unable to determine valid NVM bank via EEC - reading flash signature\n");
		/* fall-thru */
	default:
		/* set bank to 0 in case flash read fails */
		*bank = 0;

		/* Check bank 0 */
		ret_val = e1000_read_flash_byte_ich8lan(hw, act_offset,
							&sig_byte);
		if (ret_val)
			return ret_val;
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 0;
			return E1000_SUCCESS;
		}

		/* Check bank 1 */
		ret_val = e1000_read_flash_byte_ich8lan(hw, act_offset +
							bank1_offset,
							&sig_byte);
		if (ret_val)
			return ret_val;
		if ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) {
			*bank = 1;
			return E1000_SUCCESS;
		}

		DEBUGOUT("ERROR: No valid NVM bank present\n");
		return -E1000_ERR_NVM;
	}
}