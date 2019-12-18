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
struct TYPE_2__ {int /*<<< orphan*/  write; int /*<<< orphan*/  validate; int /*<<< orphan*/  valid_led_default; int /*<<< orphan*/  update; int /*<<< orphan*/  read; } ;
struct e1000_nvm_info {int word_size; int delay_usec; int address_bits; int opcode_bits; TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_nvm_eeprom_microwire ; 
 int /*<<< orphan*/  e1000_read_nvm_microwire ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_valid_led_default_generic ; 
 int /*<<< orphan*/  e1000_validate_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_write_nvm_microwire ; 

__attribute__((used)) static s32 e1000_init_nvm_params_82543(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;

	DEBUGFUNC("e1000_init_nvm_params_82543");

	nvm->type		= e1000_nvm_eeprom_microwire;
	nvm->word_size		= 64;
	nvm->delay_usec		= 50;
	nvm->address_bits	=  6;
	nvm->opcode_bits	=  3;

	/* Function Pointers */
	nvm->ops.read		= e1000_read_nvm_microwire;
	nvm->ops.update		= e1000_update_nvm_checksum_generic;
	nvm->ops.valid_led_default = e1000_valid_led_default_generic;
	nvm->ops.validate	= e1000_validate_nvm_checksum_generic;
	nvm->ops.write		= e1000_write_nvm_microwire;

	return E1000_SUCCESS;
}