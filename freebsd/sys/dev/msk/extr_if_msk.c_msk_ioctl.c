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
struct msk_if_softc {int msk_flags; int msk_if_flags; int /*<<< orphan*/  msk_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_hwassist; int if_capenable; int if_drv_flags; int if_flags; int if_capabilities; int /*<<< orphan*/  if_mtu; struct msk_if_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CSUM_TSO ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHERMIN ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int MSK_CSUM_FEATURES ; 
 int MSK_FLAG_DESCV2 ; 
 int MSK_FLAG_DETACH ; 
 int MSK_FLAG_JUMBO ; 
 int MSK_FLAG_JUMBO_NOCSUM ; 
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_JUMBO_MTU ; 
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
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msk_init_locked (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_rxfilter (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_setvlan (struct msk_if_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  msk_stop (struct msk_if_softc*) ; 

__attribute__((used)) static int
msk_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct msk_if_softc *sc_if;
	struct ifreq *ifr;
	struct mii_data	*mii;
	int error, mask, reinit;

	sc_if = ifp->if_softc;
	ifr = (struct ifreq *)data;
	error = 0;

	switch(command) {
	case SIOCSIFMTU:
		MSK_IF_LOCK(sc_if);
		if (ifr->ifr_mtu > MSK_JUMBO_MTU || ifr->ifr_mtu < ETHERMIN)
			error = EINVAL;
		else if (ifp->if_mtu != ifr->ifr_mtu) {
			if (ifr->ifr_mtu > ETHERMTU) {
				if ((sc_if->msk_flags & MSK_FLAG_JUMBO) == 0) {
					error = EINVAL;
					MSK_IF_UNLOCK(sc_if);
					break;
				}
				if ((sc_if->msk_flags &
				    MSK_FLAG_JUMBO_NOCSUM) != 0) {
					ifp->if_hwassist &=
					    ~(MSK_CSUM_FEATURES | CSUM_TSO);
					ifp->if_capenable &=
					    ~(IFCAP_TSO4 | IFCAP_TXCSUM);
					VLAN_CAPABILITIES(ifp);
				}
			}
			ifp->if_mtu = ifr->ifr_mtu;
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
				msk_init_locked(sc_if);
			}
		}
		MSK_IF_UNLOCK(sc_if);
		break;
	case SIOCSIFFLAGS:
		MSK_IF_LOCK(sc_if);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc_if->msk_if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI)) != 0)
				msk_rxfilter(sc_if);
			else if ((sc_if->msk_flags & MSK_FLAG_DETACH) == 0)
				msk_init_locked(sc_if);
		} else if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			msk_stop(sc_if);
		sc_if->msk_if_flags = ifp->if_flags;
		MSK_IF_UNLOCK(sc_if);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		MSK_IF_LOCK(sc_if);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			msk_rxfilter(sc_if);
		MSK_IF_UNLOCK(sc_if);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc_if->msk_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
		reinit = 0;
		MSK_IF_LOCK(sc_if);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		if ((mask & IFCAP_TXCSUM) != 0 &&
		    (IFCAP_TXCSUM & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_TXCSUM;
			if ((IFCAP_TXCSUM & ifp->if_capenable) != 0)
				ifp->if_hwassist |= MSK_CSUM_FEATURES;
			else
				ifp->if_hwassist &= ~MSK_CSUM_FEATURES;
		}
		if ((mask & IFCAP_RXCSUM) != 0 &&
		    (IFCAP_RXCSUM & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_RXCSUM;
			if ((sc_if->msk_flags & MSK_FLAG_DESCV2) == 0)
				reinit = 1;
		}
		if ((mask & IFCAP_VLAN_HWCSUM) != 0 &&
		    (IFCAP_VLAN_HWCSUM & ifp->if_capabilities) != 0)
			ifp->if_capenable ^= IFCAP_VLAN_HWCSUM;
		if ((mask & IFCAP_TSO4) != 0 &&
		    (IFCAP_TSO4 & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_TSO4;
			if ((IFCAP_TSO4 & ifp->if_capenable) != 0)
				ifp->if_hwassist |= CSUM_TSO;
			else
				ifp->if_hwassist &= ~CSUM_TSO;
		}
		if ((mask & IFCAP_VLAN_HWTSO) != 0 &&
		    (IFCAP_VLAN_HWTSO & ifp->if_capabilities) != 0)
			ifp->if_capenable ^= IFCAP_VLAN_HWTSO;
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (IFCAP_VLAN_HWTAGGING & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;
			if ((IFCAP_VLAN_HWTAGGING & ifp->if_capenable) == 0)
				ifp->if_capenable &=
				    ~(IFCAP_VLAN_HWTSO | IFCAP_VLAN_HWCSUM);
			msk_setvlan(sc_if, ifp);
		}
		if (ifp->if_mtu > ETHERMTU &&
		    (sc_if->msk_flags & MSK_FLAG_JUMBO_NOCSUM) != 0) {
			ifp->if_hwassist &= ~(MSK_CSUM_FEATURES | CSUM_TSO);
			ifp->if_capenable &= ~(IFCAP_TSO4 | IFCAP_TXCSUM);
		}
		VLAN_CAPABILITIES(ifp);
		if (reinit > 0 && (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			msk_init_locked(sc_if);
		}
		MSK_IF_UNLOCK(sc_if);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}