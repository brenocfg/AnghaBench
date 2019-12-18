#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_12__ {TYPE_5__ ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_10__ {TYPE_3__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_8__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_6__ phy; TYPE_4__ nvm; TYPE_2__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  e1000_init_mac_params_82541 ; 
 int /*<<< orphan*/  e1000_init_nvm_params_82541 ; 
 int /*<<< orphan*/  e1000_init_phy_params_82541 ; 

void e1000_init_function_pointers_82541(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_init_function_pointers_82541");

	hw->mac.ops.init_params = e1000_init_mac_params_82541;
	hw->nvm.ops.init_params = e1000_init_nvm_params_82541;
	hw->phy.ops.init_params = e1000_init_phy_params_82541;
}