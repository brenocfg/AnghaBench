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
struct TYPE_3__ {int /*<<< orphan*/  (* dmac_config ) (struct ixgbe_hw*) ;} ;
struct ixgbe_dmac_config {int watchdog_timer; int link_speed; int num_tcs; int /*<<< orphan*/  fcoe_en; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; struct ixgbe_dmac_config dmac_config; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct adapter {int dmac; int link_speed; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INIT_DEBUGOUT2 (char*,int,int) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static void
ixgbe_config_dmac(struct adapter *adapter)
{
	struct ixgbe_hw          *hw = &adapter->hw;
	struct ixgbe_dmac_config *dcfg = &hw->mac.dmac_config;

	if (hw->mac.type < ixgbe_mac_X550 || !hw->mac.ops.dmac_config)
		return;

	if (dcfg->watchdog_timer ^ adapter->dmac ||
	    dcfg->link_speed ^ adapter->link_speed) {
		dcfg->watchdog_timer = adapter->dmac;
		dcfg->fcoe_en = FALSE;
		dcfg->link_speed = adapter->link_speed;
		dcfg->num_tcs = 1;

		INIT_DEBUGOUT2("dmac settings: watchdog %d, link speed %d\n",
		    dcfg->watchdog_timer, dcfg->link_speed);

		hw->mac.ops.dmac_config(hw);
	}
}