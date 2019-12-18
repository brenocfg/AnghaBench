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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_ERR_NVM_PBA_SECTION ; 
 scalar_t__ E1000_ERR_PARAM ; 
 scalar_t__ E1000_SUCCESS ; 
 size_t NVM_PBA_OFFSET_0 ; 
 size_t NVM_PBA_OFFSET_1 ; 
 size_t NVM_PBA_PTR_GUARD ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,size_t,int,size_t*) ; 

s32 e1000_get_pba_block_size(struct e1000_hw *hw, u16 *eeprom_buf,
			     u32 eeprom_buf_size, u16 *pba_block_size)
{
	s32 ret_val;
	u16 pba_word[2];
	u16 length;

	DEBUGFUNC("e1000_get_pba_block_size");

	if (eeprom_buf == NULL) {
		ret_val = e1000_read_nvm(hw, NVM_PBA_OFFSET_0, 2, &pba_word[0]);
		if (ret_val)
			return ret_val;
	} else {
		if (eeprom_buf_size > NVM_PBA_OFFSET_1) {
			pba_word[0] = eeprom_buf[NVM_PBA_OFFSET_0];
			pba_word[1] = eeprom_buf[NVM_PBA_OFFSET_1];
		} else {
			return -E1000_ERR_PARAM;
		}
	}

	if (pba_word[0] == NVM_PBA_PTR_GUARD) {
		if (eeprom_buf == NULL) {
			ret_val = e1000_read_nvm(hw, pba_word[1] + 0, 1,
						 &length);
			if (ret_val)
				return ret_val;
		} else {
			if (eeprom_buf_size > pba_word[1])
				length = eeprom_buf[pba_word[1] + 0];
			else
				return -E1000_ERR_PARAM;
		}

		if (length == 0xFFFF || length == 0)
			return -E1000_ERR_NVM_PBA_SECTION;
	} else {
		/* PBA number in legacy format, there is no PBA Block. */
		length = 0;
	}

	if (pba_block_size != NULL)
		*pba_block_size = length;

	return E1000_SUCCESS;
}