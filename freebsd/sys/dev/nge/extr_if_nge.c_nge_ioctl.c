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
struct nge_softc {int nge_if_flags; int nge_flags; int /*<<< orphan*/  nge_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_mtu; int ifr_reqcap; } ;
struct ifnet {int if_mtu; int if_capenable; int if_flags; int if_drv_flags; int if_capabilities; int /*<<< orphan*/  if_hwassist; struct nge_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ETHERMIN ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_MCAST ; 
 int IFCAP_WOL_UCAST ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NGE_CLRBIT (struct nge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGE_CSUM_FEATURES ; 
 int NGE_FLAG_DETACH ; 
 int /*<<< orphan*/  NGE_IER ; 
 int NGE_JUMBO_MTU ; 
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_SETBIT (struct nge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_VIPRXCTL_TAG_STRIP_ENB ; 
 int /*<<< orphan*/  NGE_VLAN_IP_RXCTL ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nge_init_locked (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_poll ; 
 int /*<<< orphan*/  nge_rxfilter (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_stop (struct nge_softc*) ; 

__attribute__((used)) static int
nge_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct nge_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *) data;
	struct mii_data *mii;
	int error = 0, mask;

	switch (command) {
	case SIOCSIFMTU:
		if (ifr->ifr_mtu < ETHERMIN || ifr->ifr_mtu > NGE_JUMBO_MTU)
			error = EINVAL;
		else {
			NGE_LOCK(sc);
			ifp->if_mtu = ifr->ifr_mtu;
			/*
			 * Workaround: if the MTU is larger than
			 * 8152 (TX FIFO size minus 64 minus 18), turn off
			 * TX checksum offloading.
			 */
			if (ifr->ifr_mtu >= 8152) {
				ifp->if_capenable &= ~IFCAP_TXCSUM;
				ifp->if_hwassist &= ~NGE_CSUM_FEATURES;
			} else {
				ifp->if_capenable |= IFCAP_TXCSUM;
				ifp->if_hwassist |= NGE_CSUM_FEATURES;
			}
			NGE_UNLOCK(sc);
			VLAN_CAPABILITIES(ifp);
		}
		break;
	case SIOCSIFFLAGS:
		NGE_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				if ((ifp->if_flags ^ sc->nge_if_flags) &
				    (IFF_PROMISC | IFF_ALLMULTI))
					nge_rxfilter(sc);
			} else {
				if ((sc->nge_flags & NGE_FLAG_DETACH) == 0)
					nge_init_locked(sc);
			}
		} else {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
				nge_stop(sc);
		}
		sc->nge_if_flags = ifp->if_flags;
		NGE_UNLOCK(sc);
		error = 0;
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		NGE_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			nge_rxfilter(sc);
		NGE_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->nge_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
		NGE_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
#ifdef DEVICE_POLLING
		if ((mask & IFCAP_POLLING) != 0 &&
		    (IFCAP_POLLING & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_POLLING;
			if ((IFCAP_POLLING & ifp->if_capenable) != 0) {
				error = ether_poll_register(nge_poll, ifp);
				if (error != 0) {
					NGE_UNLOCK(sc);
					break;
				}
				/* Disable interrupts. */
				CSR_WRITE_4(sc, NGE_IER, 0);
			} else {
				error = ether_poll_deregister(ifp);
				/* Enable interrupts. */
				CSR_WRITE_4(sc, NGE_IER, 1);
			}
		}
#endif /* DEVICE_POLLING */
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (IFCAP_TXCSUM & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_TXCSUM;
			if ((IFCAP_TXCSUM & ifp->if_capenable) != 0)
				ifp->if_hwassist |= NGE_CSUM_FEATURES;
			else
				ifp->if_hwassist &= ~NGE_CSUM_FEATURES;
		}
		if ((mask & IFCAP_RXCSUM) != 0 &&
		    (IFCAP_RXCSUM & ifp->if_capabilities) != 0)
			ifp->if_capenable ^= IFCAP_RXCSUM;

		if ((mask & IFCAP_WOL) != 0 &&
		    (ifp->if_capabilities & IFCAP_WOL) != 0) {
			if ((mask & IFCAP_WOL_UCAST) != 0)
				ifp->if_capenable ^= IFCAP_WOL_UCAST;
			if ((mask & IFCAP_WOL_MCAST) != 0)
				ifp->if_capenable ^= IFCAP_WOL_MCAST;
			if ((mask & IFCAP_WOL_MAGIC) != 0)
				ifp->if_capenable ^= IFCAP_WOL_MAGIC;
		}

		if ((mask & IFCAP_VLAN_HWCSUM) != 0 &&
		    (ifp->if_capabilities & IFCAP_VLAN_HWCSUM) != 0)
			ifp->if_capenable ^= IFCAP_VLAN_HWCSUM;
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (ifp->if_capabilities & IFCAP_VLAN_HWTAGGING) != 0) {
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				if ((ifp->if_capenable &
				    IFCAP_VLAN_HWTAGGING) != 0)
					NGE_SETBIT(sc,
					    NGE_VLAN_IP_RXCTL,
					    NGE_VIPRXCTL_TAG_STRIP_ENB);
				else
					NGE_CLRBIT(sc,
					    NGE_VLAN_IP_RXCTL,
					    NGE_VIPRXCTL_TAG_STRIP_ENB);
			}
		}
		/*
		 * Both VLAN hardware tagging and checksum offload is
		 * required to do checksum offload on VLAN interface.
		 */
		if ((ifp->if_capenable & IFCAP_TXCSUM) == 0)
			ifp->if_capenable &= ~IFCAP_VLAN_HWCSUM;
		if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) == 0)
			ifp->if_capenable &= ~IFCAP_VLAN_HWCSUM;
		NGE_UNLOCK(sc);
		VLAN_CAPABILITIES(ifp);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}