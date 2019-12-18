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
struct ixgbe_nvm_version {int or_major; int or_build; int or_patch; int /*<<< orphan*/  or_valid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,scalar_t__,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NVM_INVALID_PTR ; 
 scalar_t__ NVM_OROM_BLK_HI ; 
 scalar_t__ NVM_OROM_BLK_LOW ; 
 scalar_t__ NVM_OROM_OFFSET ; 
 int NVM_OROM_PATCH_MASK ; 
 int NVM_OROM_SHIFT ; 
 int NVM_VER_INVALID ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,scalar_t__,int*) ; 

void ixgbe_get_orom_version(struct ixgbe_hw *hw,
			    struct ixgbe_nvm_version *nvm_ver)
{
	u16 offset, eeprom_cfg_blkh, eeprom_cfg_blkl;

	nvm_ver->or_valid = FALSE;
	/* Option Rom may or may not be present.  Start with pointer */
	hw->eeprom.ops.read(hw, NVM_OROM_OFFSET, &offset);

	/* make sure offset is valid */
	if ((offset == 0x0) || (offset == NVM_INVALID_PTR))
		return;

	hw->eeprom.ops.read(hw, offset + NVM_OROM_BLK_HI, &eeprom_cfg_blkh);
	hw->eeprom.ops.read(hw, offset + NVM_OROM_BLK_LOW, &eeprom_cfg_blkl);

	/* option rom exists and is valid */
	if ((eeprom_cfg_blkl | eeprom_cfg_blkh) == 0x0 ||
	    eeprom_cfg_blkl == NVM_VER_INVALID ||
	    eeprom_cfg_blkh == NVM_VER_INVALID)
		return;

	nvm_ver->or_valid = TRUE;
	nvm_ver->or_major = eeprom_cfg_blkl >> NVM_OROM_SHIFT;
	nvm_ver->or_build = (eeprom_cfg_blkl << NVM_OROM_SHIFT) |
			    (eeprom_cfg_blkh >> NVM_OROM_SHIFT);
	nvm_ver->or_patch = eeprom_cfg_blkh & NVM_OROM_PATCH_MASK;
}