#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_8__ {int /*<<< orphan*/  write; int /*<<< orphan*/  validate; int /*<<< orphan*/  valid_led_default; int /*<<< orphan*/  update; int /*<<< orphan*/  read; int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {int flash_base_addr; int flash_bank_size; size_t word_size; TYPE_4__ ops; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct e1000_dev_spec_ich8lan {TYPE_2__* shadow_ram; } ;
struct TYPE_5__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_3__ mac; scalar_t__ flash_address; scalar_t__ hw_addr; TYPE_1__ dev_spec; struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_6__ {int value; int /*<<< orphan*/  modified; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 scalar_t__ E1000_FLASH_BASE_ADDR ; 
 int E1000_READ_FLASH_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 size_t E1000_SHADOW_RAM_WORDS ; 
 int /*<<< orphan*/  E1000_STRAP ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int FLASH_GFPREG_BASE_MASK ; 
 int FLASH_SECTOR_ADDR_SHIFT ; 
 int /*<<< orphan*/  ICH_FLASH_GFPREG ; 
 int NVM_SIZE_MULTIPLIER ; 
 int /*<<< orphan*/  e1000_acquire_nvm_ich8lan ; 
 int /*<<< orphan*/  e1000_nvm_flash_sw ; 
 scalar_t__ e1000_pch_spt ; 
 int /*<<< orphan*/  e1000_read_nvm_ich8lan ; 
 int /*<<< orphan*/  e1000_read_nvm_spt ; 
 int /*<<< orphan*/  e1000_release_nvm_ich8lan ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum_ich8lan ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum_spt ; 
 int /*<<< orphan*/  e1000_valid_led_default_ich8lan ; 
 int /*<<< orphan*/  e1000_validate_nvm_checksum_ich8lan ; 
 int /*<<< orphan*/  e1000_write_nvm_ich8lan ; 

__attribute__((used)) static s32 e1000_init_nvm_params_ich8lan(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 gfpreg, sector_base_addr, sector_end_addr;
	u16 i;
	u32 nvm_size;

	DEBUGFUNC("e1000_init_nvm_params_ich8lan");

	nvm->type = e1000_nvm_flash_sw;

	if (hw->mac.type >= e1000_pch_spt) {
		/* in SPT, gfpreg doesn't exist. NVM size is taken from the
		 * STRAP register. This is because in SPT the GbE Flash region
		 * is no longer accessed through the flash registers. Instead,
		 * the mechanism has changed, and the Flash region access
		 * registers are now implemented in GbE memory space.
		 */
		nvm->flash_base_addr = 0;
		nvm_size =
		    (((E1000_READ_REG(hw, E1000_STRAP) >> 1) & 0x1F) + 1)
		    * NVM_SIZE_MULTIPLIER;
		nvm->flash_bank_size = nvm_size / 2;
		/* Adjust to word count */
		nvm->flash_bank_size /= sizeof(u16);
		/* Set the base address for flash register access */
		hw->flash_address = hw->hw_addr + E1000_FLASH_BASE_ADDR;
	} else {
		/* Can't read flash registers if register set isn't mapped. */
		if (!hw->flash_address) {
			DEBUGOUT("ERROR: Flash registers not mapped\n");
			return -E1000_ERR_CONFIG;
		}

		gfpreg = E1000_READ_FLASH_REG(hw, ICH_FLASH_GFPREG);

		/* sector_X_addr is a "sector"-aligned address (4096 bytes)
		 * Add 1 to sector_end_addr since this sector is included in
		 * the overall size.
		 */
		sector_base_addr = gfpreg & FLASH_GFPREG_BASE_MASK;
		sector_end_addr = ((gfpreg >> 16) & FLASH_GFPREG_BASE_MASK) + 1;

		/* flash_base_addr is byte-aligned */
		nvm->flash_base_addr = sector_base_addr
				       << FLASH_SECTOR_ADDR_SHIFT;

		/* find total size of the NVM, then cut in half since the total
		 * size represents two separate NVM banks.
		 */
		nvm->flash_bank_size = ((sector_end_addr - sector_base_addr)
					<< FLASH_SECTOR_ADDR_SHIFT);
		nvm->flash_bank_size /= 2;
		/* Adjust to word count */
		nvm->flash_bank_size /= sizeof(u16);
	}

	nvm->word_size = E1000_SHADOW_RAM_WORDS;

	/* Clear shadow ram */
	for (i = 0; i < nvm->word_size; i++) {
		dev_spec->shadow_ram[i].modified = FALSE;
		dev_spec->shadow_ram[i].value    = 0xFFFF;
	}

	/* Function Pointers */
	nvm->ops.acquire	= e1000_acquire_nvm_ich8lan;
	nvm->ops.release	= e1000_release_nvm_ich8lan;
	if (hw->mac.type >= e1000_pch_spt) {
		nvm->ops.read	= e1000_read_nvm_spt;
		nvm->ops.update	= e1000_update_nvm_checksum_spt;
	} else {
		nvm->ops.read	= e1000_read_nvm_ich8lan;
		nvm->ops.update	= e1000_update_nvm_checksum_ich8lan;
	}
	nvm->ops.valid_led_default = e1000_valid_led_default_ich8lan;
	nvm->ops.validate	= e1000_validate_nvm_checksum_ich8lan;
	nvm->ops.write		= e1000_write_nvm_ich8lan;

	return E1000_SUCCESS;
}