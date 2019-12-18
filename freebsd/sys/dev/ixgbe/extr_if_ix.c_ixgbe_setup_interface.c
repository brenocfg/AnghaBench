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
struct ifnet {scalar_t__ if_mtu; } ;
struct adapter {int /*<<< orphan*/  media; int /*<<< orphan*/  hw; int /*<<< orphan*/  phy_layer; scalar_t__ max_frame_size; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  if_setbaudrate (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_add_media_types (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_get_supported_physical_layer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ixgbe_setup_interface(if_ctx_t ctx)
{
	struct ifnet   *ifp = iflib_get_ifp(ctx);
	struct adapter *adapter = iflib_get_softc(ctx);

	INIT_DEBUGOUT("ixgbe_setup_interface: begin");

	if_setbaudrate(ifp, IF_Gbps(10));

	adapter->max_frame_size = ifp->if_mtu + ETHER_HDR_LEN + ETHER_CRC_LEN;

	adapter->phy_layer = ixgbe_get_supported_physical_layer(&adapter->hw);

	ixgbe_add_media_types(ctx);

	/* Autoselect media by default */
	ifmedia_set(adapter->media, IFM_ETHER | IFM_AUTO);

	return (0);
}