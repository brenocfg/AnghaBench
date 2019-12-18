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
struct ifreq {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; struct glc_softc* if_softc; } ;
struct glc_softc {int sc_ifpflags; int /*<<< orphan*/  sc_media; int /*<<< orphan*/  sc_mtx; } ;
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
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  glc_init_locked (struct glc_softc*) ; 
 int /*<<< orphan*/  glc_set_multicast (struct glc_softc*) ; 
 int /*<<< orphan*/  glc_stop (struct glc_softc*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
glc_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct glc_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int err = 0;

	switch (cmd) {
	case SIOCSIFFLAGS:
                mtx_lock(&sc->sc_mtx);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			   ((ifp->if_flags ^ sc->sc_ifpflags) &
			    (IFF_ALLMULTI | IFF_PROMISC)) != 0)
				glc_set_multicast(sc);
			else
				glc_init_locked(sc);
		}
		else if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			glc_stop(sc);
		sc->sc_ifpflags = ifp->if_flags;
		mtx_unlock(&sc->sc_mtx);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
                mtx_lock(&sc->sc_mtx);
		glc_set_multicast(sc);
                mtx_unlock(&sc->sc_mtx);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		err = ifmedia_ioctl(ifp, ifr, &sc->sc_media, cmd);
		break;
	default:
		err = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (err);
}