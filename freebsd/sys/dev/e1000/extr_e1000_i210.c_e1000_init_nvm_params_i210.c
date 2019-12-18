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
struct TYPE_2__ {void* update; void* validate; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  valid_led_default; int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  e1000_acquire_nvm_i210 ; 
 scalar_t__ e1000_get_flash_presence_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_nvm_params_82575 (struct e1000_hw*) ; 
 void* e1000_null_ops_generic ; 
 int /*<<< orphan*/  e1000_null_write_nvm ; 
 int /*<<< orphan*/  e1000_nvm_flash_hw ; 
 int /*<<< orphan*/  e1000_nvm_invm ; 
 int /*<<< orphan*/  e1000_read_invm_i210 ; 
 int /*<<< orphan*/  e1000_read_nvm_srrd_i210 ; 
 int /*<<< orphan*/  e1000_release_nvm_i210 ; 
 void* e1000_update_nvm_checksum_i210 ; 
 int /*<<< orphan*/  e1000_valid_led_default_i210 ; 
 void* e1000_validate_nvm_checksum_i210 ; 
 int /*<<< orphan*/  e1000_write_nvm_srwr_i210 ; 

__attribute__((used)) static s32 e1000_init_nvm_params_i210(struct e1000_hw *hw)
{
	s32 ret_val;
	struct e1000_nvm_info *nvm = &hw->nvm;

	DEBUGFUNC("e1000_init_nvm_params_i210");

	ret_val = e1000_init_nvm_params_82575(hw);
	nvm->ops.acquire = e1000_acquire_nvm_i210;
	nvm->ops.release = e1000_release_nvm_i210;
	nvm->ops.valid_led_default = e1000_valid_led_default_i210;
	if (e1000_get_flash_presence_i210(hw)) {
		hw->nvm.type = e1000_nvm_flash_hw;
		nvm->ops.read    = e1000_read_nvm_srrd_i210;
		nvm->ops.write   = e1000_write_nvm_srwr_i210;
		nvm->ops.validate = e1000_validate_nvm_checksum_i210;
		nvm->ops.update   = e1000_update_nvm_checksum_i210;
	} else {
		hw->nvm.type = e1000_nvm_invm;
		nvm->ops.read     = e1000_read_invm_i210;
		nvm->ops.write    = e1000_null_write_nvm;
		nvm->ops.validate = e1000_null_ops_generic;
		nvm->ops.update   = e1000_null_ops_generic;
	}
	return ret_val;
}