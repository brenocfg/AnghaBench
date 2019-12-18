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
struct ifreq {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; struct are_softc* if_softc; } ;
struct are_softc {int are_if_flags; int /*<<< orphan*/  are_ifmedia; int /*<<< orphan*/  are_miibus; int /*<<< orphan*/  are_detach; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
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
 int /*<<< orphan*/  are_init_locked (struct are_softc*) ; 
 int /*<<< orphan*/  are_set_filter (struct are_softc*) ; 
 int /*<<< orphan*/  are_stop (struct are_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
are_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct are_softc		*sc = ifp->if_softc;
	struct ifreq		*ifr = (struct ifreq *) data;
#ifdef ARE_MII
	struct mii_data		*mii;
#endif
	int			error;

	switch (command) {
	case SIOCSIFFLAGS:
		ARE_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if ((ifp->if_flags ^ sc->are_if_flags) &
				    (IFF_PROMISC | IFF_ALLMULTI))
					are_set_filter(sc);
			} else {
				if (sc->are_detach == 0)
					are_init_locked(sc);
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				are_stop(sc);
		}
		sc->are_if_flags = ifp->if_flags;
		ARE_UNLOCK(sc);
		error = 0;
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ARE_LOCK(sc);
		are_set_filter(sc);
		ARE_UNLOCK(sc);
		error = 0;
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
#ifdef ARE_MII
		mii = device_get_softc(sc->are_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
#else
		error = ifmedia_ioctl(ifp, ifr, &sc->are_ifmedia, command);
#endif
		break;
	case SIOCSIFCAP:
		error = 0;
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}