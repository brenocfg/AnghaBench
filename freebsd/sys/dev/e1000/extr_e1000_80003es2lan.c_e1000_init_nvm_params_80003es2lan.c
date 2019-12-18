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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  write; int /*<<< orphan*/  validate; int /*<<< orphan*/  valid_led_default; int /*<<< orphan*/  update; int /*<<< orphan*/  release; int /*<<< orphan*/  read; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {int opcode_bits; int delay_usec; int override; int page_size; int address_bits; int word_size; TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_ADDR_BITS ; 
 int E1000_EECD_SIZE_EX_MASK ; 
 int E1000_EECD_SIZE_EX_SHIFT ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ NVM_WORD_SIZE_BASE_SHIFT ; 
 int /*<<< orphan*/  e1000_acquire_nvm_80003es2lan ; 
 int /*<<< orphan*/  e1000_nvm_eeprom_spi ; 
#define  e1000_nvm_override_spi_large 129 
#define  e1000_nvm_override_spi_small 128 
 int /*<<< orphan*/  e1000_read_nvm_eerd ; 
 int /*<<< orphan*/  e1000_release_nvm_80003es2lan ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_valid_led_default_generic ; 
 int /*<<< orphan*/  e1000_validate_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_write_nvm_80003es2lan ; 

__attribute__((used)) static s32 e1000_init_nvm_params_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = E1000_READ_REG(hw, E1000_EECD);
	u16 size;

	DEBUGFUNC("e1000_init_nvm_params_80003es2lan");

	nvm->opcode_bits = 8;
	nvm->delay_usec = 1;
	switch (nvm->override) {
	case e1000_nvm_override_spi_large:
		nvm->page_size = 32;
		nvm->address_bits = 16;
		break;
	case e1000_nvm_override_spi_small:
		nvm->page_size = 8;
		nvm->address_bits = 8;
		break;
	default:
		nvm->page_size = eecd & E1000_EECD_ADDR_BITS ? 32 : 8;
		nvm->address_bits = eecd & E1000_EECD_ADDR_BITS ? 16 : 8;
		break;
	}

	nvm->type = e1000_nvm_eeprom_spi;

	size = (u16)((eecd & E1000_EECD_SIZE_EX_MASK) >>
		     E1000_EECD_SIZE_EX_SHIFT);

	/* Added to a constant, "size" becomes the left-shift value
	 * for setting word_size.
	 */
	size += NVM_WORD_SIZE_BASE_SHIFT;

	/* EEPROM access above 16k is unsupported */
	if (size > 14)
		size = 14;
	nvm->word_size = 1 << size;

	/* Function Pointers */
	nvm->ops.acquire	= e1000_acquire_nvm_80003es2lan;
	nvm->ops.read		= e1000_read_nvm_eerd;
	nvm->ops.release	= e1000_release_nvm_80003es2lan;
	nvm->ops.update		= e1000_update_nvm_checksum_generic;
	nvm->ops.valid_led_default = e1000_valid_led_default_generic;
	nvm->ops.validate	= e1000_validate_nvm_checksum_generic;
	nvm->ops.write		= e1000_write_nvm_80003es2lan;

	return E1000_SUCCESS;
}