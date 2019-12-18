#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ rar_used_count; int /*<<< orphan*/  overflow_promisc; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ num_rar_entries; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ addr_ctrl; TYPE_3__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  DEBUGOUT6 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RAH_AV ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void ixgbe_add_uc_addr(struct ixgbe_hw *hw, u8 *addr, u32 vmdq)
{
	u32 rar_entries = hw->mac.num_rar_entries;
	u32 rar;

	DEBUGFUNC("ixgbe_add_uc_addr");

	DEBUGOUT6(" UC Addr = %.2X %.2X %.2X %.2X %.2X %.2X\n",
		  addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	/*
	 * Place this address in the RAR if there is room,
	 * else put the controller into promiscuous mode
	 */
	if (hw->addr_ctrl.rar_used_count < rar_entries) {
		rar = hw->addr_ctrl.rar_used_count;
		hw->mac.ops.set_rar(hw, rar, addr, vmdq, IXGBE_RAH_AV);
		DEBUGOUT1("Added a secondary address to RAR[%d]\n", rar);
		hw->addr_ctrl.rar_used_count++;
	} else {
		hw->addr_ctrl.overflow_promisc++;
	}

	DEBUGOUT("ixgbe_add_uc_addr Complete\n");
}