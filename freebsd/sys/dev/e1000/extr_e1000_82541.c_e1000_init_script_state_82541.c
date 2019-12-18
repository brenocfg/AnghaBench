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
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_dev_spec_82541 {int phy_init_script; } ;
struct TYPE_3__ {struct e1000_dev_spec_82541 _82541; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ dev_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ e1000_phy_igp ; 

void e1000_init_script_state_82541(struct e1000_hw *hw, bool state)
{
	struct e1000_dev_spec_82541 *dev_spec = &hw->dev_spec._82541;

	DEBUGFUNC("e1000_init_script_state_82541");

	if (hw->phy.type != e1000_phy_igp) {
		DEBUGOUT("Initialization script not necessary.\n");
		goto out;
	}

	dev_spec->phy_init_script = state;

out:
	return;
}