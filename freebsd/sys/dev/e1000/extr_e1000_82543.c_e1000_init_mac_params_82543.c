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
struct TYPE_3__ {int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  check_for_link; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  set_lan_id; int /*<<< orphan*/  get_bus_info; } ;
struct e1000_mac_info {int mta_reg_count; scalar_t__ type; TYPE_1__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct e1000_hw {int device_id; TYPE_2__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  E1000_DEV_ID_82543GC_FIBER 129 
#define  E1000_DEV_ID_82544EI_FIBER 128 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ e1000_82543 ; 
 int /*<<< orphan*/  e1000_check_for_copper_link_82543 ; 
 int /*<<< orphan*/  e1000_check_for_fiber_link_82543 ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82543 ; 
 int /*<<< orphan*/  e1000_clear_vfta_generic ; 
 int /*<<< orphan*/  e1000_get_bus_info_pci_generic ; 
 int /*<<< orphan*/  e1000_get_speed_and_duplex_copper_generic ; 
 int /*<<< orphan*/  e1000_get_speed_and_duplex_fiber_serdes_generic ; 
 int /*<<< orphan*/  e1000_init_hw_82543 ; 
 int /*<<< orphan*/  e1000_led_off_82543 ; 
 int /*<<< orphan*/  e1000_led_on_82543 ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_read_mac_addr_82543 ; 
 int /*<<< orphan*/  e1000_reset_hw_82543 ; 
 int /*<<< orphan*/  e1000_set_lan_id_multi_port_pci ; 
 int /*<<< orphan*/  e1000_set_tbi_compatibility_82543 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_setup_copper_link_82543 ; 
 int /*<<< orphan*/  e1000_setup_fiber_link_82543 ; 
 int /*<<< orphan*/  e1000_setup_link_82543 ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_82543 ; 

__attribute__((used)) static s32 e1000_init_mac_params_82543(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	DEBUGFUNC("e1000_init_mac_params_82543");

	/* Set media type */
	switch (hw->device_id) {
	case E1000_DEV_ID_82543GC_FIBER:
	case E1000_DEV_ID_82544EI_FIBER:
		hw->phy.media_type = e1000_media_type_fiber;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		break;
	}

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_pci_generic;
	/* function id */
	mac->ops.set_lan_id = e1000_set_lan_id_multi_port_pci;
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_82543;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_82543;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_82543;
	/* physical interface setup */
	mac->ops.setup_physical_interface =
		(hw->phy.media_type == e1000_media_type_copper)
		 ? e1000_setup_copper_link_82543 : e1000_setup_fiber_link_82543;
	/* check for link */
	mac->ops.check_for_link =
		(hw->phy.media_type == e1000_media_type_copper)
		 ? e1000_check_for_copper_link_82543
		 : e1000_check_for_fiber_link_82543;
	/* link info */
	mac->ops.get_link_up_info =
		(hw->phy.media_type == e1000_media_type_copper)
		 ? e1000_get_speed_and_duplex_copper_generic
		 : e1000_get_speed_and_duplex_fiber_serdes_generic;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	/* writing VFTA */
	mac->ops.write_vfta = e1000_write_vfta_82543;
	/* clearing VFTA */
	mac->ops.clear_vfta = e1000_clear_vfta_generic;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_82543;
	/* turn on/off LED */
	mac->ops.led_on = e1000_led_on_82543;
	mac->ops.led_off = e1000_led_off_82543;
	/* clear hardware counters */
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_82543;

	/* Set tbi compatibility */
	if ((hw->mac.type != e1000_82543) ||
	    (hw->phy.media_type == e1000_media_type_fiber))
		e1000_set_tbi_compatibility_82543(hw, FALSE);

	return E1000_SUCCESS;
}