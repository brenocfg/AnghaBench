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
struct TYPE_3__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_init_function_pointers_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_nvm_params_i210 ; 

void e1000_init_function_pointers_i210(struct e1000_hw *hw)
{
	e1000_init_function_pointers_82575(hw);
	hw->nvm.ops.init_params = e1000_init_nvm_params_i210;

	return;
}