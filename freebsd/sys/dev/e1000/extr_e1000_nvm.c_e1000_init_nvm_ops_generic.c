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
struct TYPE_2__ {int /*<<< orphan*/  write; void* validate; int /*<<< orphan*/  valid_led_default; void* update; int /*<<< orphan*/  reload; int /*<<< orphan*/  release; int /*<<< orphan*/  read; void* acquire; void* init_params; } ;
struct e1000_nvm_info {TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  e1000_null_led_default ; 
 int /*<<< orphan*/  e1000_null_nvm_generic ; 
 void* e1000_null_ops_generic ; 
 int /*<<< orphan*/  e1000_null_read_nvm ; 
 int /*<<< orphan*/  e1000_null_write_nvm ; 
 int /*<<< orphan*/  e1000_reload_nvm_generic ; 

void e1000_init_nvm_ops_generic(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	DEBUGFUNC("e1000_init_nvm_ops_generic");

	/* Initialize function pointers */
	nvm->ops.init_params = e1000_null_ops_generic;
	nvm->ops.acquire = e1000_null_ops_generic;
	nvm->ops.read = e1000_null_read_nvm;
	nvm->ops.release = e1000_null_nvm_generic;
	nvm->ops.reload = e1000_reload_nvm_generic;
	nvm->ops.update = e1000_null_ops_generic;
	nvm->ops.valid_led_default = e1000_null_led_default;
	nvm->ops.validate = e1000_null_ops_generic;
	nvm->ops.write = e1000_null_write_nvm;
}