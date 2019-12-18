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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* setup_link ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_link_capabilities ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg_advertised; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct adapter {int /*<<< orphan*/  media; int /*<<< orphan*/  ctx; int /*<<< orphan*/  phy_layer; struct ixgbe_hw hw; } ;
typedef  void* if_ctx_t ;

/* Variables and functions */
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  TRUE ; 
 struct adapter* iflib_get_softc (void*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_add_media_types (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_get_supported_physical_layer (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgbe_handle_msf(void *context)
{
	if_ctx_t        ctx = context;
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	u32             autoneg;
	bool            negotiate;

	/* get_supported_phy_layer will call hw->phy.ops.identify_sfp() */
	adapter->phy_layer = ixgbe_get_supported_physical_layer(hw);

	autoneg = hw->phy.autoneg_advertised;
	if ((!autoneg) && (hw->mac.ops.get_link_capabilities))
		hw->mac.ops.get_link_capabilities(hw, &autoneg, &negotiate);
	if (hw->mac.ops.setup_link)
		hw->mac.ops.setup_link(hw, autoneg, TRUE);

	/* Adjust media types shown in ifconfig */
	ifmedia_removeall(adapter->media);
	ixgbe_add_media_types(adapter->ctx);
	ifmedia_set(adapter->media, IFM_ETHER | IFM_AUTO);
}