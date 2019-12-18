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
struct TYPE_2__ {int /*<<< orphan*/  validate; int /*<<< orphan*/  update; int /*<<< orphan*/  write; int /*<<< orphan*/  release; int /*<<< orphan*/  read; } ;
struct e1000_nvm_info {int address_bits; int delay_usec; int opcode_bits; int word_size; TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_nvm_eeprom_microwire ; 
 int /*<<< orphan*/  e1000_read_nvm_microwire ; 
 int /*<<< orphan*/  e1000_stop_nvm ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_validate_nvm_checksum_generic ; 
 int /*<<< orphan*/  e1000_write_nvm_microwire ; 

__attribute__((used)) static s32 e1000_init_nvm_params_82542(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;

	DEBUGFUNC("e1000_init_nvm_params_82542");

	nvm->address_bits	=  6;
	nvm->delay_usec		= 50;
	nvm->opcode_bits	=  3;
	nvm->type		= e1000_nvm_eeprom_microwire;
	nvm->word_size		= 64;

	/* Function Pointers */
	nvm->ops.read		= e1000_read_nvm_microwire;
	nvm->ops.release	= e1000_stop_nvm;
	nvm->ops.write		= e1000_write_nvm_microwire;
	nvm->ops.update		= e1000_update_nvm_checksum_generic;
	nvm->ops.validate	= e1000_validate_nvm_checksum_generic;

	return E1000_SUCCESS;
}