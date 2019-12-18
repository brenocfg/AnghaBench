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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int* mta_shadow; int mta_reg_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_MTA ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ e1000_hash_mc_addr_generic (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

void e1000_update_mc_addr_list_generic(struct e1000_hw *hw,
				       u8 *mc_addr_list, u32 mc_addr_count)
{
	u32 hash_value, hash_bit, hash_reg;
	int i;

	DEBUGFUNC("e1000_update_mc_addr_list_generic");

	/* clear mta_shadow */
	memset(&hw->mac.mta_shadow, 0, sizeof(hw->mac.mta_shadow));

	/* update mta_shadow from mc_addr_list */
	for (i = 0; (u32) i < mc_addr_count; i++) {
		hash_value = e1000_hash_mc_addr_generic(hw, mc_addr_list);

		hash_reg = (hash_value >> 5) & (hw->mac.mta_reg_count - 1);
		hash_bit = hash_value & 0x1F;

		hw->mac.mta_shadow[hash_reg] |= (1 << hash_bit);
		mc_addr_list += (ETHER_ADDR_LEN);
	}

	/* replace the entire MTA table */
	for (i = hw->mac.mta_reg_count - 1; i >= 0; i--)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, hw->mac.mta_shadow[i]);
	E1000_WRITE_FLUSH(hw);
}