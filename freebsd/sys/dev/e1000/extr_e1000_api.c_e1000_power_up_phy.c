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
struct TYPE_3__ {int /*<<< orphan*/  (* power_up ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_setup_link (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

void e1000_power_up_phy(struct e1000_hw *hw)
{
	if (hw->phy.ops.power_up)
		hw->phy.ops.power_up(hw);

	e1000_setup_link(hw);
}