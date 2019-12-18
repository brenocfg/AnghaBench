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
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_hwassist; struct gem_softc* if_softc; } ;
struct gem_softc {int sc_ifflags; int /*<<< orphan*/  sc_csum_features; TYPE_1__* sc_mii; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  mii_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_UDP ; 
 int /*<<< orphan*/  GEM_LOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  GEM_UNLOCK (struct gem_softc*) ; 
 int IFCAP_TXCSUM ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_LINK0 ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  gem_init_locked (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_setladrf (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_stop (struct ifnet*,int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
gem_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct gem_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int error;

	error = 0;
	switch (cmd) {
	case SIOCSIFFLAGS:
		GEM_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->sc_ifflags) &
			    (IFF_ALLMULTI | IFF_PROMISC)) != 0)
				gem_setladrf(sc);
			else
				gem_init_locked(sc);
		} else if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			gem_stop(ifp, 0);
		if ((ifp->if_flags & IFF_LINK0) != 0)
			sc->sc_csum_features |= CSUM_UDP;
		else
			sc->sc_csum_features &= ~CSUM_UDP;
		if ((ifp->if_capenable & IFCAP_TXCSUM) != 0)
			ifp->if_hwassist = sc->sc_csum_features;
		sc->sc_ifflags = ifp->if_flags;
		GEM_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		GEM_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			gem_setladrf(sc);
		GEM_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->sc_mii->mii_media, cmd);
		break;
	case SIOCSIFCAP:
		GEM_LOCK(sc);
		ifp->if_capenable = ifr->ifr_reqcap;
		if ((ifp->if_capenable & IFCAP_TXCSUM) != 0)
			ifp->if_hwassist = sc->sc_csum_features;
		else
			ifp->if_hwassist = 0;
		GEM_UNLOCK(sc);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}