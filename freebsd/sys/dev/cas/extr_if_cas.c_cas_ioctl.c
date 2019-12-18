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
typedef  int u_long ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_hwassist; struct cas_softc* if_softc; } ;
struct cas_softc {int sc_ifflags; int sc_flags; TYPE_1__* sc_mii; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  mii_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_CSUM_FEATURES ; 
 int /*<<< orphan*/  CAS_LOCK (struct cas_softc*) ; 
 int CAS_NO_CSUM ; 
 int /*<<< orphan*/  CAS_UNLOCK (struct cas_softc*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHERMIN ; 
 int /*<<< orphan*/  ETHERMTU_JUMBO ; 
 int IFCAP_TXCSUM ; 
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
 int /*<<< orphan*/  cas_init_locked (struct cas_softc*) ; 
 int /*<<< orphan*/  cas_setladrf (struct cas_softc*) ; 
 int /*<<< orphan*/  cas_stop (struct ifnet*) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
cas_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct cas_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int error;

	error = 0;
	switch (cmd) {
	case SIOCSIFFLAGS:
		CAS_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->sc_ifflags) &
			    (IFF_ALLMULTI | IFF_PROMISC)) != 0)
				cas_setladrf(sc);
			else
				cas_init_locked(sc);
		} else if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			cas_stop(ifp);
		sc->sc_ifflags = ifp->if_flags;
		CAS_UNLOCK(sc);
		break;
	case SIOCSIFCAP:
		CAS_LOCK(sc);
		if ((sc->sc_flags & CAS_NO_CSUM) != 0) {
			error = EINVAL;
			CAS_UNLOCK(sc);
			break;
		}
		ifp->if_capenable = ifr->ifr_reqcap;
		if ((ifp->if_capenable & IFCAP_TXCSUM) != 0)
			ifp->if_hwassist = CAS_CSUM_FEATURES;
		else
			ifp->if_hwassist = 0;
		CAS_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		CAS_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			cas_setladrf(sc);
		CAS_UNLOCK(sc);
		break;
	case SIOCSIFMTU:
		if ((ifr->ifr_mtu < ETHERMIN) ||
		    (ifr->ifr_mtu > ETHERMTU_JUMBO))
			error = EINVAL;
		else
			ifp->if_mtu = ifr->ifr_mtu;
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->sc_mii->mii_media, cmd);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}