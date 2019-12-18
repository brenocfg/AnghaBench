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
struct ifreq {scalar_t__ ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; scalar_t__ if_hdrlen; struct gx_softc* if_softc; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
struct gx_softc {int sc_flags; int /*<<< orphan*/  sc_ifmedia; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOTSUP ; 
 scalar_t__ GXEMUL_ETHER_DEV_MTU ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFADDR 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  gx_init (struct gx_softc*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
gx_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct gx_softc *sc;
	struct ifreq *ifr;
#ifdef INET
	struct ifaddr *ifa;
#endif
	int error;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;
#ifdef INET
	ifa = (struct ifaddr *)data;
#endif

	switch (cmd) {
	case SIOCSIFADDR:
#ifdef INET
		/*
		 * Avoid reinitialization unless it's necessary.
		 */
		if (ifa->ifa_addr->sa_family == AF_INET) {
			ifp->if_flags |= IFF_UP;
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
				gx_init(sc);
			arp_ifinit(ifp, ifa);

			return (0);
		}
#endif
		error = ether_ioctl(ifp, cmd, data);
		if (error != 0)
			return (error);
		return (0);

	case SIOCSIFFLAGS:
		if (ifp->if_flags == sc->sc_flags)
			return (0);
		if ((ifp->if_flags & IFF_UP) != 0) {
			gx_init(sc);
		} else {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			}
		}
		sc->sc_flags = ifp->if_flags;
		return (0);

	case SIOCSIFMTU:
		if (ifr->ifr_mtu + ifp->if_hdrlen > GXEMUL_ETHER_DEV_MTU)
			return (ENOTSUP);
		return (0);

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->sc_ifmedia, cmd);
		if (error != 0)
			return (error);
		return (0);
	
	default:
		error = ether_ioctl(ifp, cmd, data);
		if (error != 0)
			return (error);
		return (0);
	}
}