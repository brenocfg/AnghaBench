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
typedef  int u16 ;
struct adapter {int* shadow_vfta; int /*<<< orphan*/  num_vlans; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_setup_vlan_hw_support (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgbe_if_vlan_register(if_ctx_t ctx, u16 vtag)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	u16            index, bit;

	index = (vtag >> 5) & 0x7F;
	bit = vtag & 0x1F;
	adapter->shadow_vfta[index] |= (1 << bit);
	++adapter->num_vlans;
	ixgbe_setup_vlan_hw_support(ctx);
}