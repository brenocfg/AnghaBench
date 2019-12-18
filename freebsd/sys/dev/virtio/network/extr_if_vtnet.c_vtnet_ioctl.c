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
typedef  int u_long ;
struct vtnet_softc {int vtnet_if_flags; int vtnet_flags; int /*<<< orphan*/  vtnet_media; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_mtu; struct vtnet_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTSUP ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK_ASSERT_NOTOWNED (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_UNLOCK (struct vtnet_softc*) ; 
 int VTNET_FLAG_CTRL_RX ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int vtnet_change_mtu (struct vtnet_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_init_locked (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_rx_filter (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_rx_filter_mac (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_stop (struct vtnet_softc*) ; 

__attribute__((used)) static int
vtnet_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct vtnet_softc *sc;
	struct ifreq *ifr;
	int reinit, mask, error;

	sc = ifp->if_softc;
	ifr = (struct ifreq *) data;
	error = 0;

	switch (cmd) {
	case SIOCSIFMTU:
		if (ifp->if_mtu != ifr->ifr_mtu) {
			VTNET_CORE_LOCK(sc);
			error = vtnet_change_mtu(sc, ifr->ifr_mtu);
			VTNET_CORE_UNLOCK(sc);
		}
		break;

	case SIOCSIFFLAGS:
		VTNET_CORE_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) == 0) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				vtnet_stop(sc);
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			if ((ifp->if_flags ^ sc->vtnet_if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI)) {
				if (sc->vtnet_flags & VTNET_FLAG_CTRL_RX)
					vtnet_rx_filter(sc);
				else {
					ifp->if_flags |= IFF_PROMISC;
					if ((ifp->if_flags ^ sc->vtnet_if_flags)
					    & IFF_ALLMULTI)
						error = ENOTSUP;
				}
			}
		} else
			vtnet_init_locked(sc);

		if (error == 0)
			sc->vtnet_if_flags = ifp->if_flags;
		VTNET_CORE_UNLOCK(sc);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if ((sc->vtnet_flags & VTNET_FLAG_CTRL_RX) == 0)
			break;
		VTNET_CORE_LOCK(sc);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			vtnet_rx_filter_mac(sc);
		VTNET_CORE_UNLOCK(sc);
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->vtnet_media, cmd);
		break;

	case SIOCSIFCAP:
		VTNET_CORE_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;

		if (mask & IFCAP_TXCSUM)
			ifp->if_capenable ^= IFCAP_TXCSUM;
		if (mask & IFCAP_TXCSUM_IPV6)
			ifp->if_capenable ^= IFCAP_TXCSUM_IPV6;
		if (mask & IFCAP_TSO4)
			ifp->if_capenable ^= IFCAP_TSO4;
		if (mask & IFCAP_TSO6)
			ifp->if_capenable ^= IFCAP_TSO6;

		if (mask & (IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6 | IFCAP_LRO |
		    IFCAP_VLAN_HWFILTER)) {
			/* These Rx features require us to renegotiate. */
			reinit = 1;

			if (mask & IFCAP_RXCSUM)
				ifp->if_capenable ^= IFCAP_RXCSUM;
			if (mask & IFCAP_RXCSUM_IPV6)
				ifp->if_capenable ^= IFCAP_RXCSUM_IPV6;
			if (mask & IFCAP_LRO)
				ifp->if_capenable ^= IFCAP_LRO;
			if (mask & IFCAP_VLAN_HWFILTER)
				ifp->if_capenable ^= IFCAP_VLAN_HWFILTER;
		} else
			reinit = 0;

		if (mask & IFCAP_VLAN_HWTSO)
			ifp->if_capenable ^= IFCAP_VLAN_HWTSO;
		if (mask & IFCAP_VLAN_HWTAGGING)
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;

		if (reinit && (ifp->if_drv_flags & IFF_DRV_RUNNING)) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			vtnet_init_locked(sc);
		}

		VTNET_CORE_UNLOCK(sc);
		VLAN_CAPABILITIES(ifp);

		break;

	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	VTNET_CORE_LOCK_ASSERT_NOTOWNED(sc);

	return (error);
}