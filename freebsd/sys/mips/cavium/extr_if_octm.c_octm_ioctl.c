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
struct octm_softc {int sc_flags; int /*<<< orphan*/  sc_ifmedia; int /*<<< orphan*/  sc_port; } ;
struct ifreq {scalar_t__ ifr_mtu; int /*<<< orphan*/  ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; scalar_t__ if_hdrlen; int /*<<< orphan*/  if_capenable; struct octm_softc* if_softc; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
#define  SIOCGIFMEDIA 133 
#define  SIOCSIFADDR 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_set_max_packet_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octm_init (struct octm_softc*) ; 

__attribute__((used)) static int
octm_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct octm_softc *sc;
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
				octm_init(sc);
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
			octm_init(sc);
		} else {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				cvmx_mgmt_port_disable(sc->sc_port);

				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			}
		}
		sc->sc_flags = ifp->if_flags;
		return (0);
	
	case SIOCSIFCAP:
		/*
		 * Just change the capabilities in software, currently none
		 * require reprogramming hardware, they just toggle whether we
		 * make use of already-present facilities in software.
		 */
		ifp->if_capenable = ifr->ifr_reqcap;
		return (0);

	case SIOCSIFMTU:
		cvmx_mgmt_port_set_max_packet_size(sc->sc_port, ifr->ifr_mtu + ifp->if_hdrlen);
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