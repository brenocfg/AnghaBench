#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_rlpml; int /*<<< orphan*/  set_vfta; int /*<<< orphan*/ * clear_vfta; int /*<<< orphan*/ * disable_mc; int /*<<< orphan*/ * enable_mc; int /*<<< orphan*/  update_xcast_mode; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/ * init_rx_addrs; int /*<<< orphan*/  set_uc_addr; int /*<<< orphan*/  set_rar; int /*<<< orphan*/ * get_link_capabilities; int /*<<< orphan*/  check_link; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  negotiate_api_version; int /*<<< orphan*/ * get_bus_info; int /*<<< orphan*/  stop_adapter; int /*<<< orphan*/  get_mac_addr; int /*<<< orphan*/ * get_media_type; int /*<<< orphan*/ * clear_hw_cntrs; int /*<<< orphan*/  start_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  init_hw; } ;
struct TYPE_6__ {int max_tx_queues; int max_rx_queues; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ mbx; TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_check_mac_link_vf ; 
 int /*<<< orphan*/  ixgbe_get_mac_addr_vf ; 
 int /*<<< orphan*/  ixgbe_init_hw_vf ; 
 int /*<<< orphan*/  ixgbe_init_mbx_params_vf ; 
 int /*<<< orphan*/  ixgbe_reset_hw_vf ; 
 int /*<<< orphan*/  ixgbe_set_rar_vf ; 
 int /*<<< orphan*/  ixgbe_set_vfta_vf ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_vf ; 
 int /*<<< orphan*/  ixgbe_start_hw_vf ; 
 int /*<<< orphan*/  ixgbe_stop_adapter_vf ; 
 int /*<<< orphan*/  ixgbe_update_mc_addr_list_vf ; 
 int /*<<< orphan*/  ixgbevf_negotiate_api_version ; 
 int /*<<< orphan*/  ixgbevf_rlpml_set_vf ; 
 int /*<<< orphan*/  ixgbevf_set_uc_addr_vf ; 
 int /*<<< orphan*/  ixgbevf_update_xcast_mode ; 

s32 ixgbe_init_ops_vf(struct ixgbe_hw *hw)
{
	/* MAC */
	hw->mac.ops.init_hw = ixgbe_init_hw_vf;
	hw->mac.ops.reset_hw = ixgbe_reset_hw_vf;
	hw->mac.ops.start_hw = ixgbe_start_hw_vf;
	/* Cannot clear stats on VF */
	hw->mac.ops.clear_hw_cntrs = NULL;
	hw->mac.ops.get_media_type = NULL;
	hw->mac.ops.get_mac_addr = ixgbe_get_mac_addr_vf;
	hw->mac.ops.stop_adapter = ixgbe_stop_adapter_vf;
	hw->mac.ops.get_bus_info = NULL;
	hw->mac.ops.negotiate_api_version = ixgbevf_negotiate_api_version;

	/* Link */
	hw->mac.ops.setup_link = ixgbe_setup_mac_link_vf;
	hw->mac.ops.check_link = ixgbe_check_mac_link_vf;
	hw->mac.ops.get_link_capabilities = NULL;

	/* RAR, Multicast, VLAN */
	hw->mac.ops.set_rar = ixgbe_set_rar_vf;
	hw->mac.ops.set_uc_addr = ixgbevf_set_uc_addr_vf;
	hw->mac.ops.init_rx_addrs = NULL;
	hw->mac.ops.update_mc_addr_list = ixgbe_update_mc_addr_list_vf;
	hw->mac.ops.update_xcast_mode = ixgbevf_update_xcast_mode;
	hw->mac.ops.enable_mc = NULL;
	hw->mac.ops.disable_mc = NULL;
	hw->mac.ops.clear_vfta = NULL;
	hw->mac.ops.set_vfta = ixgbe_set_vfta_vf;
	hw->mac.ops.set_rlpml = ixgbevf_rlpml_set_vf;

	hw->mac.max_tx_queues = 1;
	hw->mac.max_rx_queues = 1;

	hw->mbx.ops.init_params = ixgbe_init_mbx_params_vf;

	return IXGBE_SUCCESS;
}