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
struct lance_softc {int sc_flags; int /*<<< orphan*/  sc_media; } ;
struct ifreq {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; struct lance_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_DEBUG ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int LE_ALLMULTI ; 
 int LE_DEBUG ; 
 int /*<<< orphan*/  LE_LOCK (struct lance_softc*) ; 
 int LE_PROMISC ; 
 int /*<<< orphan*/  LE_UNLOCK (struct lance_softc*) ; 
#define  SIOCADDMULTI 132 
#define  SIOCDELMULTI 131 
#define  SIOCGIFMEDIA 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lance_init_locked (struct lance_softc*) ; 
 int /*<<< orphan*/  lance_stop (struct lance_softc*) ; 

__attribute__((used)) static int
lance_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct lance_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int error = 0;

	switch (cmd) {
	case SIOCSIFFLAGS:
		LE_LOCK(sc);
		if (ifp->if_flags & IFF_PROMISC) {
			if (!(sc->sc_flags & LE_PROMISC)) {
				sc->sc_flags |= LE_PROMISC;
				lance_init_locked(sc);
			}
		} else if (sc->sc_flags & LE_PROMISC) {
			sc->sc_flags &= ~LE_PROMISC;
			lance_init_locked(sc);
		}

		if ((ifp->if_flags & IFF_ALLMULTI) &&
		    !(sc->sc_flags & LE_ALLMULTI)) {
			sc->sc_flags |= LE_ALLMULTI;
			lance_init_locked(sc);
		} else if (!(ifp->if_flags & IFF_ALLMULTI) &&
		    (sc->sc_flags & LE_ALLMULTI)) {
			sc->sc_flags &= ~LE_ALLMULTI;
			lance_init_locked(sc);
		}

		if (!(ifp->if_flags & IFF_UP) &&
		    ifp->if_drv_flags & IFF_DRV_RUNNING) {
			/*
			 * If interface is marked down and it is running, then
			 * stop it.
			 */
			lance_stop(sc);
		} else if (ifp->if_flags & IFF_UP &&
		    !(ifp->if_drv_flags & IFF_DRV_RUNNING)) {
			/*
			 * If interface is marked up and it is stopped, then
			 * start it.
			 */
			lance_init_locked(sc);
		}
#ifdef LEDEBUG
		if (ifp->if_flags & IFF_DEBUG)
			sc->sc_flags |= LE_DEBUG;
		else
			sc->sc_flags &= ~LE_DEBUG;
#endif
		LE_UNLOCK(sc);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		/*
		 * Multicast list has changed; set the hardware filter
		 * accordingly.
		 */
		LE_LOCK(sc);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			lance_init_locked(sc);
		LE_UNLOCK(sc);
		break;

	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->sc_media, cmd);
		break;

	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}