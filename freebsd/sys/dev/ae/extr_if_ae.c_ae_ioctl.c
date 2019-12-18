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
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_drv_flags; int if_flags; int if_capenable; int if_capabilities; int /*<<< orphan*/  if_mtu; struct ae_softc* if_softc; } ;
struct ae_softc {int if_flags; int flags; int /*<<< orphan*/  miibus; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int AE_FLAG_DETACH ; 
 int /*<<< orphan*/  AE_LOCK (struct ae_softc*) ; 
 int /*<<< orphan*/  AE_UNLOCK (struct ae_softc*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHERMIN ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int IFCAP_VLAN_HWTAGGING ; 
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
 int /*<<< orphan*/  ae_init_locked (struct ae_softc*) ; 
 int /*<<< orphan*/  ae_rxfilter (struct ae_softc*) ; 
 int /*<<< orphan*/  ae_rxvlan (struct ae_softc*) ; 
 int /*<<< orphan*/  ae_stop (struct ae_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ae_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ae_softc *sc;
	struct ifreq *ifr;
	struct mii_data *mii;
	int error, mask;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;
	error = 0;

	switch (cmd) {
	case SIOCSIFMTU:
		if (ifr->ifr_mtu < ETHERMIN || ifr->ifr_mtu > ETHERMTU)
			error = EINVAL;
		else if (ifp->if_mtu != ifr->ifr_mtu) {
			AE_LOCK(sc);
			ifp->if_mtu = ifr->ifr_mtu;
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
				ae_init_locked(sc);
			}
			AE_UNLOCK(sc);
		}
		break;
	case SIOCSIFFLAGS:
		AE_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				if (((ifp->if_flags ^ sc->if_flags)
				    & (IFF_PROMISC | IFF_ALLMULTI)) != 0)
					ae_rxfilter(sc);
			} else {
				if ((sc->flags & AE_FLAG_DETACH) == 0)
					ae_init_locked(sc);
			}
		} else {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
				ae_stop(sc);
		}
		sc->if_flags = ifp->if_flags;
		AE_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		AE_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			ae_rxfilter(sc);
		AE_UNLOCK(sc);
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		mii = device_get_softc(sc->miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;
	case SIOCSIFCAP:
		AE_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		if ((mask & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (ifp->if_capabilities & IFCAP_VLAN_HWTAGGING) != 0) {
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;
			ae_rxvlan(sc);
		}
		VLAN_CAPABILITIES(ifp);
		AE_UNLOCK(sc);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}
	return (error);
}