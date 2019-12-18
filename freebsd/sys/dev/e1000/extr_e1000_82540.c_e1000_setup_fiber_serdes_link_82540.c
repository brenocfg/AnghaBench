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
struct e1000_mac_info {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {TYPE_1__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
#define  e1000_82545_rev_3 129 
#define  e1000_82546_rev_3 128 
 int /*<<< orphan*/  e1000_adjust_serdes_amplitude_82540 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_set_vco_speed_82540 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_setup_fiber_serdes_link_generic (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_setup_fiber_serdes_link_82540(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_setup_fiber_serdes_link_82540");

	switch (mac->type) {
	case e1000_82545_rev_3:
	case e1000_82546_rev_3:
		if (hw->phy.media_type == e1000_media_type_internal_serdes) {
			/*
			 * If we're on serdes media, adjust the output
			 * amplitude to value set in the EEPROM.
			 */
			ret_val = e1000_adjust_serdes_amplitude_82540(hw);
			if (ret_val)
				goto out;
		}
		/* Adjust VCO speed to improve BER performance */
		ret_val = e1000_set_vco_speed_82540(hw);
		if (ret_val)
			goto out;
	default:
		break;
	}

	ret_val = e1000_setup_fiber_serdes_link_generic(hw);

out:
	return ret_val;
}