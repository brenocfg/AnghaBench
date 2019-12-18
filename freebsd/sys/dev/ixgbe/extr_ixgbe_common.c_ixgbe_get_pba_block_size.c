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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,scalar_t__,size_t*) ;scalar_t__ (* read_buffer ) (struct ixgbe_hw*,size_t,int,size_t*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_ERR_PARAM ; 
 scalar_t__ IXGBE_ERR_PBA_SECTION ; 
 size_t IXGBE_PBANUM0_PTR ; 
 size_t IXGBE_PBANUM1_PTR ; 
 size_t IXGBE_PBANUM_PTR_GUARD ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ stub1 (struct ixgbe_hw*,size_t,int,size_t*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,scalar_t__,size_t*) ; 

s32 ixgbe_get_pba_block_size(struct ixgbe_hw *hw, u16 *eeprom_buf,
			     u32 eeprom_buf_size, u16 *pba_block_size)
{
	s32 ret_val;
	u16 pba_word[2];
	u16 length;

	DEBUGFUNC("ixgbe_get_pba_block_size");

	if (eeprom_buf == NULL) {
		ret_val = hw->eeprom.ops.read_buffer(hw, IXGBE_PBANUM0_PTR, 2,
						     &pba_word[0]);
		if (ret_val)
			return ret_val;
	} else {
		if (eeprom_buf_size > IXGBE_PBANUM1_PTR) {
			pba_word[0] = eeprom_buf[IXGBE_PBANUM0_PTR];
			pba_word[1] = eeprom_buf[IXGBE_PBANUM1_PTR];
		} else {
			return IXGBE_ERR_PARAM;
		}
	}

	if (pba_word[0] == IXGBE_PBANUM_PTR_GUARD) {
		if (eeprom_buf == NULL) {
			ret_val = hw->eeprom.ops.read(hw, pba_word[1] + 0,
						      &length);
			if (ret_val)
				return ret_val;
		} else {
			if (eeprom_buf_size > pba_word[1])
				length = eeprom_buf[pba_word[1] + 0];
			else
				return IXGBE_ERR_PARAM;
		}

		if (length == 0xFFFF || length == 0)
			return IXGBE_ERR_PBA_SECTION;
	} else {
		/* PBA number in legacy format, there is no PBA Block. */
		length = 0;
	}

	if (pba_block_size != NULL)
		*pba_block_size = length;

	return IXGBE_SUCCESS;
}