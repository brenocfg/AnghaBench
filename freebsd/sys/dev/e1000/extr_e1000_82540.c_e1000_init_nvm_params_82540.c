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
struct TYPE_2__ {int /*<<< orphan*/  write; int /*<<< orphan*/  validate; int /*<<< orphan*/  valid_led_default; int /*<<< orphan*/  update; int /*<<< orphan*/  release; int /*<<< orphan*/  read; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {int delay_usec; int opcode_bits; int override; int address_bits; int word_size; TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_SIZE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_acquire_nvm_generic ; 
 int /*<<< orphan*/  e1000_nvm_eeprom_microwire ; 
#define  e1000_nvm_override_microwire_large 129 
#define  e1000_nvm_override_microwire_small 128 
 int /*<<< orphan*/  e1000_read_nvm_microwire ; 
 int /*<<< orphan*/  e1000_release_nvm_generic ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_valid_led_default_generic ; 
 int /*<<< orphan*/  e1000_validate_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_write_nvm_microwire ; 

__attribute__((used)) static s32 e1000_init_nvm_params_82540(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = E1000_READ_REG(hw, E1000_EECD);

	DEBUGFUNC("e1000_init_nvm_params_82540");

	nvm->type = e1000_nvm_eeprom_microwire;
	nvm->delay_usec = 50;
	nvm->opcode_bits = 3;
	switch (nvm->override) {
	case e1000_nvm_override_microwire_large:
		nvm->address_bits = 8;
		nvm->word_size = 256;
		break;
	case e1000_nvm_override_microwire_small:
		nvm->address_bits = 6;
		nvm->word_size = 64;
		break;
	default:
		nvm->address_bits = eecd & E1000_EECD_SIZE ? 8 : 6;
		nvm->word_size = eecd & E1000_EECD_SIZE ? 256 : 64;
		break;
	}

	/* Function Pointers */
	nvm->ops.acquire	= e1000_acquire_nvm_generic;
	nvm->ops.read		= e1000_read_nvm_microwire;
	nvm->ops.release	= e1000_release_nvm_generic;
	nvm->ops.update		= e1000_update_nvm_checksum_generic;
	nvm->ops.valid_led_default = e1000_valid_led_default_generic;
	nvm->ops.validate	= e1000_validate_nvm_checksum_generic;
	nvm->ops.write		= e1000_write_nvm_microwire;

	return E1000_SUCCESS;
}