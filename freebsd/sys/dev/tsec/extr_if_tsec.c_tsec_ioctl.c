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
struct tsec_softc {int tsec_if_flags; int /*<<< orphan*/  is_etsec; TYPE_1__* tsec_mii; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_mtu; struct tsec_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  mii_media; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_POLLING ; 
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
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_GLOBAL_UNLOCK (struct tsec_softc*) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tsec_init_locked (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_intrs_ctl (struct tsec_softc*,int) ; 
 int /*<<< orphan*/  tsec_offload_setup (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_poll ; 
 int /*<<< orphan*/  tsec_set_mtu (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsec_setfilter (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_setup_multicast (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_start (struct ifnet*) ; 
 int /*<<< orphan*/  tsec_stop (struct tsec_softc*) ; 

__attribute__((used)) static int
tsec_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct tsec_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int mask, error = 0;

	switch (command) {
	case SIOCSIFMTU:
		TSEC_GLOBAL_LOCK(sc);
		if (tsec_set_mtu(sc, ifr->ifr_mtu))
			ifp->if_mtu = ifr->ifr_mtu;
		else
			error = EINVAL;
		TSEC_GLOBAL_UNLOCK(sc);
		break;
	case SIOCSIFFLAGS:
		TSEC_GLOBAL_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if ((sc->tsec_if_flags ^ ifp->if_flags) &
				    IFF_PROMISC)
					tsec_setfilter(sc);

				if ((sc->tsec_if_flags ^ ifp->if_flags) &
				    IFF_ALLMULTI)
					tsec_setup_multicast(sc);
			} else
				tsec_init_locked(sc);
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			tsec_stop(sc);

		sc->tsec_if_flags = ifp->if_flags;
		TSEC_GLOBAL_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			TSEC_GLOBAL_LOCK(sc);
			tsec_setup_multicast(sc);
			TSEC_GLOBAL_UNLOCK(sc);
		}
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->tsec_mii->mii_media,
		    command);
		break;
	case SIOCSIFCAP:
		mask = ifp->if_capenable ^ ifr->ifr_reqcap;
		if ((mask & IFCAP_HWCSUM) && sc->is_etsec) {
			TSEC_GLOBAL_LOCK(sc);
			ifp->if_capenable &= ~IFCAP_HWCSUM;
			ifp->if_capenable |= IFCAP_HWCSUM & ifr->ifr_reqcap;
			tsec_offload_setup(sc);
			TSEC_GLOBAL_UNLOCK(sc);
		}
#ifdef DEVICE_POLLING
		if (mask & IFCAP_POLLING) {
			if (ifr->ifr_reqcap & IFCAP_POLLING) {
				error = ether_poll_register(tsec_poll, ifp);
				if (error)
					return (error);

				TSEC_GLOBAL_LOCK(sc);
				/* Disable interrupts */
				tsec_intrs_ctl(sc, 0);
				ifp->if_capenable |= IFCAP_POLLING;
				TSEC_GLOBAL_UNLOCK(sc);
			} else {
				error = ether_poll_deregister(ifp);
				TSEC_GLOBAL_LOCK(sc);
				/* Enable interrupts */
				tsec_intrs_ctl(sc, 1);
				ifp->if_capenable &= ~IFCAP_POLLING;
				TSEC_GLOBAL_UNLOCK(sc);
			}
		}
#endif
		break;

	default:
		error = ether_ioctl(ifp, command, data);
	}

	/* Flush buffers if not empty */
	if (ifp->if_flags & IFF_UP)
		tsec_start(ifp);
	return (error);
}