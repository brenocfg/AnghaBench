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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ multispeed_fiber; } ;
struct ixgbe_hw {scalar_t__ device_id; TYPE_1__ phy; } ;
struct adapter {int phy_layer; int /*<<< orphan*/  media; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFM_1000_CX ; 
 int IFM_1000_KX ; 
 int IFM_1000_LX ; 
 int IFM_1000_SX ; 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10G_CX4 ; 
 int IFM_10G_KR ; 
 int IFM_10G_KX4 ; 
 int IFM_10G_LR ; 
 int IFM_10G_SR ; 
 int IFM_10G_T ; 
 int IFM_10G_TWINAX ; 
 int IFM_10_T ; 
 int IFM_2500_KX ; 
 int IFM_2500_SX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 scalar_t__ IXGBE_DEV_ID_82598AT ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_BX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_KX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_SX ; 
 int IXGBE_PHYSICAL_LAYER_1000BASE_T ; 
 int IXGBE_PHYSICAL_LAYER_100BASE_TX ; 
 int IXGBE_PHYSICAL_LAYER_10BASE_T ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_CX4 ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_KR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_KX4 ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_LR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_SR ; 
 int IXGBE_PHYSICAL_LAYER_10GBASE_T ; 
 int IXGBE_PHYSICAL_LAYER_2500BASE_KX ; 
 int IXGBE_PHYSICAL_LAYER_SFP_ACTIVE_DA ; 
 int IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ixgbe_get_supported_physical_layer (struct ixgbe_hw*) ; 

__attribute__((used)) static void
ixgbe_add_media_types(if_ctx_t ctx)
{
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	device_t        dev = iflib_get_dev(ctx);
	u64             layer;

	layer = adapter->phy_layer = ixgbe_get_supported_physical_layer(hw);

	/* Media types with matching FreeBSD media defines */
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_T)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_T, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_1000BASE_T)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_T, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_100BASE_TX)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_100_TX, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_10BASE_T)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10_T, 0, NULL);

	if (layer & IXGBE_PHYSICAL_LAYER_SFP_PLUS_CU ||
	    layer & IXGBE_PHYSICAL_LAYER_SFP_ACTIVE_DA)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_TWINAX, 0,
		    NULL);

	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_LR) {
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_LR, 0, NULL);
		if (hw->phy.multispeed_fiber)
			ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_LX, 0,
			    NULL);
	}
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_SR) {
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_SR, 0, NULL);
		if (hw->phy.multispeed_fiber)
			ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_SX, 0,
			    NULL);
	} else if (layer & IXGBE_PHYSICAL_LAYER_1000BASE_SX)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_SX, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_CX4)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_CX4, 0, NULL);

#ifdef IFM_ETH_XTYPE
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_KR)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_KR, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_KX4)
		ifmedia_add( adapter->media, IFM_ETHER | IFM_10G_KX4, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_1000BASE_KX)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_KX, 0, NULL);
	if (layer & IXGBE_PHYSICAL_LAYER_2500BASE_KX)
		ifmedia_add(adapter->media, IFM_ETHER | IFM_2500_KX, 0, NULL);
#else
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_KR) {
		device_printf(dev, "Media supported: 10GbaseKR\n");
		device_printf(dev, "10GbaseKR mapped to 10GbaseSR\n");
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_SR, 0, NULL);
	}
	if (layer & IXGBE_PHYSICAL_LAYER_10GBASE_KX4) {
		device_printf(dev, "Media supported: 10GbaseKX4\n");
		device_printf(dev, "10GbaseKX4 mapped to 10GbaseCX4\n");
		ifmedia_add(adapter->media, IFM_ETHER | IFM_10G_CX4, 0, NULL);
	}
	if (layer & IXGBE_PHYSICAL_LAYER_1000BASE_KX) {
		device_printf(dev, "Media supported: 1000baseKX\n");
		device_printf(dev, "1000baseKX mapped to 1000baseCX\n");
		ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_CX, 0, NULL);
	}
	if (layer & IXGBE_PHYSICAL_LAYER_2500BASE_KX) {
		device_printf(dev, "Media supported: 2500baseKX\n");
		device_printf(dev, "2500baseKX mapped to 2500baseSX\n");
		ifmedia_add(adapter->media, IFM_ETHER | IFM_2500_SX, 0, NULL);
	}
#endif
	if (layer & IXGBE_PHYSICAL_LAYER_1000BASE_BX)
		device_printf(dev, "Media supported: 1000baseBX\n");

	if (hw->device_id == IXGBE_DEV_ID_82598AT) {
		ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_T | IFM_FDX,
		    0, NULL);
		ifmedia_add(adapter->media, IFM_ETHER | IFM_1000_T, 0, NULL);
	}

	ifmedia_add(adapter->media, IFM_ETHER | IFM_AUTO, 0, NULL);
}