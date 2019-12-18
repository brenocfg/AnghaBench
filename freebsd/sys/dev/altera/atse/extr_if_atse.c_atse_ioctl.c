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
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; struct atse_softc* if_softc; } ;
struct atse_softc {int atse_if_flags; int /*<<< orphan*/  atse_miibus; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_LOCK (struct atse_softc*) ; 
 int /*<<< orphan*/  ATSE_UNLOCK (struct atse_softc*) ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int /*<<< orphan*/  atse_init_locked (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_rxfilter_locked (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_stop_locked (struct atse_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
atse_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct atse_softc *sc;
	struct ifreq *ifr;
	int error, mask;

	error = 0;
	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;

	switch (command) {
	case SIOCSIFFLAGS:
		ATSE_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->atse_if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI)) != 0)
				atse_rxfilter_locked(sc);
			else
				atse_init_locked(sc);
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			atse_stop_locked(sc);
		sc->atse_if_flags = ifp->if_flags;
		ATSE_UNLOCK(sc);
		break;
	case SIOCSIFCAP:
		ATSE_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		ATSE_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ATSE_LOCK(sc);
		atse_rxfilter_locked(sc);
		ATSE_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
	{
		struct mii_data *mii;
		struct ifreq *ifr;

		mii = device_get_softc(sc->atse_miibus);
		ifr = (struct ifreq *)data;
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	}
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}