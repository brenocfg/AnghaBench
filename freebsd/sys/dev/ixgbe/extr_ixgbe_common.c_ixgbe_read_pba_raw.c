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
typedef  int u16 ;
struct ixgbe_pba {int* word; int* pba_block; } ;
struct TYPE_3__ {scalar_t__ (* read_buffer ) (struct ixgbe_hw*,scalar_t__,int,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_PARAM ; 
 size_t IXGBE_PBANUM0_PTR ; 
 size_t IXGBE_PBANUM1_PTR ; 
 scalar_t__ IXGBE_PBANUM_PTR_GUARD ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_get_pba_block_size (struct ixgbe_hw*,int*,size_t,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,size_t,int,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,scalar_t__,int,int*) ; 

s32 ixgbe_read_pba_raw(struct ixgbe_hw *hw, u16 *eeprom_buf,
		       u32 eeprom_buf_size, u16 max_pba_block_size,
		       struct ixgbe_pba *pba)
{
	s32 ret_val;
	u16 pba_block_size;

	if (pba == NULL)
		return IXGBE_ERR_PARAM;

	if (eeprom_buf == NULL) {
		ret_val = hw->eeprom.ops.read_buffer(hw, IXGBE_PBANUM0_PTR, 2,
						     &pba->word[0]);
		if (ret_val)
			return ret_val;
	} else {
		if (eeprom_buf_size > IXGBE_PBANUM1_PTR) {
			pba->word[0] = eeprom_buf[IXGBE_PBANUM0_PTR];
			pba->word[1] = eeprom_buf[IXGBE_PBANUM1_PTR];
		} else {
			return IXGBE_ERR_PARAM;
		}
	}

	if (pba->word[0] == IXGBE_PBANUM_PTR_GUARD) {
		if (pba->pba_block == NULL)
			return IXGBE_ERR_PARAM;

		ret_val = ixgbe_get_pba_block_size(hw, eeprom_buf,
						   eeprom_buf_size,
						   &pba_block_size);
		if (ret_val)
			return ret_val;

		if (pba_block_size > max_pba_block_size)
			return IXGBE_ERR_PARAM;

		if (eeprom_buf == NULL) {
			ret_val = hw->eeprom.ops.read_buffer(hw, pba->word[1],
							     pba_block_size,
							     pba->pba_block);
			if (ret_val)
				return ret_val;
		} else {
			if (eeprom_buf_size > (u32)(pba->word[1] +
					      pba_block_size)) {
				memcpy(pba->pba_block,
				       &eeprom_buf[pba->word[1]],
				       pba_block_size * sizeof(u16));
			} else {
				return IXGBE_ERR_PARAM;
			}
		}
	}

	return IXGBE_SUCCESS;
}