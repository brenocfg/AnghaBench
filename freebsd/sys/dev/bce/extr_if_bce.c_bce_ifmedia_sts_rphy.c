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
typedef  int u32 ;
struct ifnet {void* if_baudrate; } ;
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct bce_softc {int bce_phy_flags; struct ifnet* bce_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_LINK_STATUS ; 
#define  BCE_LINK_STATUS_1000FULL 135 
#define  BCE_LINK_STATUS_1000HALF 134 
#define  BCE_LINK_STATUS_100FULL 133 
#define  BCE_LINK_STATUS_100HALF 132 
#define  BCE_LINK_STATUS_10FULL 131 
#define  BCE_LINK_STATUS_10HALF 130 
#define  BCE_LINK_STATUS_2500FULL 129 
#define  BCE_LINK_STATUS_2500HALF 128 
 int BCE_LINK_STATUS_LINK_UP ; 
 int BCE_LINK_STATUS_RX_FC_ENABLED ; 
 int BCE_LINK_STATUS_SPEED_MASK ; 
 int BCE_LINK_STATUS_TX_FC_ENABLED ; 
 int /*<<< orphan*/  BCE_LOCK_ASSERT (struct bce_softc*) ; 
 int BCE_PHY_REMOTE_PORT_FIBER_FLAG ; 
 int IFM_1000_SX ; 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int IFM_2500_SX ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int IFM_NONE ; 
 void* IF_Mbps (unsigned long) ; 
 int bce_shmem_rd (struct bce_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bce_ifmedia_sts_rphy(struct bce_softc *sc, struct ifmediareq *ifmr)
{
	struct ifnet *ifp;
	u32 link;

	ifp = sc->bce_ifp;
	BCE_LOCK_ASSERT(sc);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;
	link = bce_shmem_rd(sc, BCE_LINK_STATUS);
	/* XXX Handle heart beat status? */
	if ((link & BCE_LINK_STATUS_LINK_UP) != 0)
		ifmr->ifm_status |= IFM_ACTIVE;
	else {
		ifmr->ifm_active |= IFM_NONE;
		ifp->if_baudrate = 0;
		return;
	}
	switch (link & BCE_LINK_STATUS_SPEED_MASK) {
	case BCE_LINK_STATUS_10HALF:
		ifmr->ifm_active |= IFM_10_T | IFM_HDX;
		ifp->if_baudrate = IF_Mbps(10UL);
		break;
	case BCE_LINK_STATUS_10FULL:
		ifmr->ifm_active |= IFM_10_T | IFM_FDX;
		ifp->if_baudrate = IF_Mbps(10UL);
		break;
	case BCE_LINK_STATUS_100HALF:
		ifmr->ifm_active |= IFM_100_TX | IFM_HDX;
		ifp->if_baudrate = IF_Mbps(100UL);
		break;
	case BCE_LINK_STATUS_100FULL:
		ifmr->ifm_active |= IFM_100_TX | IFM_FDX;
		ifp->if_baudrate = IF_Mbps(100UL);
		break;
	case BCE_LINK_STATUS_1000HALF:
		if ((sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG) == 0)
			ifmr->ifm_active |= IFM_1000_T | IFM_HDX;
		else
			ifmr->ifm_active |= IFM_1000_SX | IFM_HDX;
		ifp->if_baudrate = IF_Mbps(1000UL);
		break;
	case BCE_LINK_STATUS_1000FULL:
		if ((sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG) == 0)
			ifmr->ifm_active |= IFM_1000_T | IFM_FDX;
		else
			ifmr->ifm_active |= IFM_1000_SX | IFM_FDX;
		ifp->if_baudrate = IF_Mbps(1000UL);
		break;
	case BCE_LINK_STATUS_2500HALF:
		if ((sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG) == 0) {
			ifmr->ifm_active |= IFM_NONE;
			return;
		} else
			ifmr->ifm_active |= IFM_2500_SX | IFM_HDX;
		ifp->if_baudrate = IF_Mbps(2500UL);
		break;
	case BCE_LINK_STATUS_2500FULL:
		if ((sc->bce_phy_flags & BCE_PHY_REMOTE_PORT_FIBER_FLAG) == 0) {
			ifmr->ifm_active |= IFM_NONE;
			return;
		} else
			ifmr->ifm_active |= IFM_2500_SX | IFM_FDX;
		ifp->if_baudrate = IF_Mbps(2500UL);
		break;
	default:
		ifmr->ifm_active |= IFM_NONE;
		return;
	}

	if ((link & BCE_LINK_STATUS_RX_FC_ENABLED) != 0)
		ifmr->ifm_active |= IFM_ETH_RXPAUSE;
	if ((link & BCE_LINK_STATUS_TX_FC_ENABLED) != 0)
		ifmr->ifm_active |= IFM_ETH_TXPAUSE;
}