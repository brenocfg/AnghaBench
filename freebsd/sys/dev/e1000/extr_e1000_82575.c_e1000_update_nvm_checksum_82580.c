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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* write ) (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ;scalar_t__ (* read ) (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int NVM_82580_LAN_FUNC_OFFSET (int) ; 
 int NVM_COMPATIBILITY_BIT_MASK ; 
 int /*<<< orphan*/  NVM_COMPATIBILITY_REG_3 ; 
 scalar_t__ e1000_update_nvm_checksum_with_offset (struct e1000_hw*,int) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static s32 e1000_update_nvm_checksum_82580(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 j, nvm_data;
	u16 nvm_offset;

	DEBUGFUNC("e1000_update_nvm_checksum_82580");

	ret_val = hw->nvm.ops.read(hw, NVM_COMPATIBILITY_REG_3, 1, &nvm_data);
	if (ret_val) {
		DEBUGOUT("NVM Read Error while updating checksum compatibility bit.\n");
		goto out;
	}

	if (!(nvm_data & NVM_COMPATIBILITY_BIT_MASK)) {
		/* set compatibility bit to validate checksums appropriately */
		nvm_data = nvm_data | NVM_COMPATIBILITY_BIT_MASK;
		ret_val = hw->nvm.ops.write(hw, NVM_COMPATIBILITY_REG_3, 1,
					    &nvm_data);
		if (ret_val) {
			DEBUGOUT("NVM Write Error while updating checksum compatibility bit.\n");
			goto out;
		}
	}

	for (j = 0; j < 4; j++) {
		nvm_offset = NVM_82580_LAN_FUNC_OFFSET(j);
		ret_val = e1000_update_nvm_checksum_with_offset(hw, nvm_offset);
		if (ret_val)
			goto out;
	}

out:
	return ret_val;
}