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
struct rt_softc {int if_flags; int /*<<< orphan*/  rt_ifmedia; int /*<<< orphan*/  rt_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; struct rt_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
#define  SIOCGIFMEDIA 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt_init_locked (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_stop_locked (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_update_promisc (struct ifnet*) ; 

__attribute__((used)) static int
rt_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct rt_softc *sc;
	struct ifreq *ifr;
#ifdef IF_RT_PHY_SUPPORT
	struct mii_data *mii;
#endif /* IF_RT_PHY_SUPPORT */
	int error, startall;

	sc = ifp->if_softc;
	ifr = (struct ifreq *) data;

	error = 0;

	switch (cmd) {
	case SIOCSIFFLAGS:
		startall = 0;
		RT_SOFTC_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if ((ifp->if_flags ^ sc->if_flags) &
				    IFF_PROMISC)
					rt_update_promisc(ifp);
			} else {
				rt_init_locked(sc);
				startall = 1;
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				rt_stop_locked(sc);
		}
		sc->if_flags = ifp->if_flags;
		RT_SOFTC_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
#ifdef IF_RT_PHY_SUPPORT
		mii = device_get_softc(sc->rt_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
#else
		error = ifmedia_ioctl(ifp, ifr, &sc->rt_ifmedia, cmd);
#endif /* IF_RT_PHY_SUPPORT */
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}
	return (error);
}