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
struct TYPE_4__ {int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  rar_set; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  check_for_link; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  set_lan_id; int /*<<< orphan*/  get_bus_info; } ;
struct e1000_mac_info {int mta_reg_count; TYPE_2__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {TYPE_1__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_check_for_fiber_link_generic ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82542 ; 
 int /*<<< orphan*/  e1000_clear_vfta_generic ; 
 int /*<<< orphan*/  e1000_get_bus_info_82542 ; 
 int /*<<< orphan*/  e1000_get_speed_and_duplex_fiber_serdes_generic ; 
 int /*<<< orphan*/  e1000_init_hw_82542 ; 
 int /*<<< orphan*/  e1000_led_off_82542 ; 
 int /*<<< orphan*/  e1000_led_on_82542 ; 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_rar_set_82542 ; 
 int /*<<< orphan*/  e1000_read_mac_addr_82542 ; 
 int /*<<< orphan*/  e1000_reset_hw_82542 ; 
 int /*<<< orphan*/  e1000_set_lan_id_multi_port_pci ; 
 int /*<<< orphan*/  e1000_setup_fiber_serdes_link_generic ; 
 int /*<<< orphan*/  e1000_setup_link_82542 ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_generic ; 

__attribute__((used)) static s32 e1000_init_mac_params_82542(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	DEBUGFUNC("e1000_init_mac_params_82542");

	/* Set media type */
	hw->phy.media_type = e1000_media_type_fiber;

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_82542;
	/* function id */
	mac->ops.set_lan_id = e1000_set_lan_id_multi_port_pci;
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_82542;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_82542;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_82542;
	/* phy/fiber/serdes setup */
	mac->ops.setup_physical_interface =
					e1000_setup_fiber_serdes_link_generic;
	/* check for link */
	mac->ops.check_for_link = e1000_check_for_fiber_link_generic;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	/* writing VFTA */
	mac->ops.write_vfta = e1000_write_vfta_generic;
	/* clearing VFTA */
	mac->ops.clear_vfta = e1000_clear_vfta_generic;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_82542;
	/* set RAR */
	mac->ops.rar_set = e1000_rar_set_82542;
	/* turn on/off LED */
	mac->ops.led_on = e1000_led_on_82542;
	mac->ops.led_off = e1000_led_off_82542;
	/* clear hardware counters */
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_82542;
	/* link info */
	mac->ops.get_link_up_info =
				e1000_get_speed_and_duplex_fiber_serdes_generic;

	return E1000_SUCCESS;
}