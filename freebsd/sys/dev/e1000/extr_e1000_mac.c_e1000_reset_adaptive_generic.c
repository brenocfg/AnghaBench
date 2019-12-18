#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct e1000_mac_info {int /*<<< orphan*/  in_ifs_mode; int /*<<< orphan*/  ifs_ratio; int /*<<< orphan*/  ifs_step_size; int /*<<< orphan*/  ifs_max_val; int /*<<< orphan*/  ifs_min_val; scalar_t__ current_ifs_val; int /*<<< orphan*/  adaptive_ifs; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_AIT ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFS_MAX ; 
 int /*<<< orphan*/  IFS_MIN ; 
 int /*<<< orphan*/  IFS_RATIO ; 
 int /*<<< orphan*/  IFS_STEP ; 

void e1000_reset_adaptive_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	DEBUGFUNC("e1000_reset_adaptive_generic");

	if (!mac->adaptive_ifs) {
		DEBUGOUT("Not in Adaptive IFS mode!\n");
		return;
	}

	mac->current_ifs_val = 0;
	mac->ifs_min_val = IFS_MIN;
	mac->ifs_max_val = IFS_MAX;
	mac->ifs_step_size = IFS_STEP;
	mac->ifs_ratio = IFS_RATIO;

	mac->in_ifs_mode = FALSE;
	E1000_WRITE_REG(hw, E1000_AIT, 0);
}