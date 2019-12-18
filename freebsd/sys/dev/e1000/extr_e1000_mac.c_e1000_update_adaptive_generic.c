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
struct e1000_mac_info {int collision_delta; int ifs_ratio; int tx_packet_delta; scalar_t__ current_ifs_val; scalar_t__ ifs_max_val; scalar_t__ ifs_min_val; scalar_t__ ifs_step_size; scalar_t__ in_ifs_mode; int /*<<< orphan*/  adaptive_ifs; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_AIT ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int MIN_NUM_XMITS ; 
 scalar_t__ TRUE ; 

void e1000_update_adaptive_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	DEBUGFUNC("e1000_update_adaptive_generic");

	if (!mac->adaptive_ifs) {
		DEBUGOUT("Not in Adaptive IFS mode!\n");
		return;
	}

	if ((mac->collision_delta * mac->ifs_ratio) > mac->tx_packet_delta) {
		if (mac->tx_packet_delta > MIN_NUM_XMITS) {
			mac->in_ifs_mode = TRUE;
			if (mac->current_ifs_val < mac->ifs_max_val) {
				if (!mac->current_ifs_val)
					mac->current_ifs_val = mac->ifs_min_val;
				else
					mac->current_ifs_val +=
						mac->ifs_step_size;
				E1000_WRITE_REG(hw, E1000_AIT,
						mac->current_ifs_val);
			}
		}
	} else {
		if (mac->in_ifs_mode &&
		    (mac->tx_packet_delta <= MIN_NUM_XMITS)) {
			mac->current_ifs_val = 0;
			mac->in_ifs_mode = FALSE;
			E1000_WRITE_REG(hw, E1000_AIT, 0);
		}
	}
}