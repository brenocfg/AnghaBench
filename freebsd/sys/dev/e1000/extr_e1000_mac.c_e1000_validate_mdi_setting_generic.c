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
struct TYPE_4__ {int mdix; } ;
struct TYPE_3__ {int /*<<< orphan*/  autoneg; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 

__attribute__((used)) static s32 e1000_validate_mdi_setting_generic(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_validate_mdi_setting_generic");

	if (!hw->mac.autoneg && (hw->phy.mdix == 0 || hw->phy.mdix == 3)) {
		DEBUGOUT("Invalid MDI setting detected\n");
		hw->phy.mdix = 1;
		return -E1000_ERR_CONFIG;
	}

	return E1000_SUCCESS;
}