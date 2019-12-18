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
struct vte_softc {int vte_if_flags; int /*<<< orphan*/  vte_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; struct vte_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 132 
#define  SIOCDELMULTI 131 
#define  SIOCGIFMEDIA 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int /*<<< orphan*/  VTE_LOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_UNLOCK (struct vte_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vte_init_locked (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_rxfilter (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_stop (struct vte_softc*) ; 

__attribute__((used)) static int
vte_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct vte_softc *sc;
	struct ifreq *ifr;
	struct mii_data *mii;
	int error;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;
	error = 0;
	switch (cmd) {
	case SIOCSIFFLAGS:
		VTE_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->vte_if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI)) != 0)
				vte_rxfilter(sc);
			else
				vte_init_locked(sc);
		} else if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			vte_stop(sc);
		sc->vte_if_flags = ifp->if_flags;
		VTE_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		VTE_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			vte_rxfilter(sc);
		VTE_UNLOCK(sc);
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		mii = device_get_softc(sc->vte_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}