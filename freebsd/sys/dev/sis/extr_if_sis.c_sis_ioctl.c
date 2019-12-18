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
struct sis_softc {int sis_if_flags; int /*<<< orphan*/  sis_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_capabilities; struct sis_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_MCAST ; 
 int IFCAP_WOL_UCAST ; 
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
 int /*<<< orphan*/  SIS_IER ; 
 int /*<<< orphan*/  SIS_LOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_UNLOCK (struct sis_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sis_initl (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_poll ; 
 int /*<<< orphan*/  sis_rxfilter (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_stop (struct sis_softc*) ; 

__attribute__((used)) static int
sis_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct sis_softc	*sc = ifp->if_softc;
	struct ifreq		*ifr = (struct ifreq *) data;
	struct mii_data		*mii;
	int			error = 0, mask;

	switch (command) {
	case SIOCSIFFLAGS:
		SIS_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->sis_if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI)) != 0)
				sis_rxfilter(sc);
			else
				sis_initl(sc);
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			sis_stop(sc);
		sc->sis_if_flags = ifp->if_flags;
		SIS_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		SIS_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			sis_rxfilter(sc);
		SIS_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->sis_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
		SIS_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
#ifdef DEVICE_POLLING
		if ((mask & IFCAP_POLLING) != 0 &&
		    (IFCAP_POLLING & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_POLLING;
			if ((IFCAP_POLLING & ifp->if_capenable) != 0) {
				error = ether_poll_register(sis_poll, ifp);
				if (error != 0) {
					SIS_UNLOCK(sc);
					break;
				}
				/* Disable interrupts. */
				CSR_WRITE_4(sc, SIS_IER, 0);
                        } else {
                                error = ether_poll_deregister(ifp);
                                /* Enable interrupts. */
				CSR_WRITE_4(sc, SIS_IER, 1);
                        }
		}
#endif /* DEVICE_POLLING */
		if ((mask & IFCAP_WOL) != 0 &&
		    (ifp->if_capabilities & IFCAP_WOL) != 0) {
			if ((mask & IFCAP_WOL_UCAST) != 0)
				ifp->if_capenable ^= IFCAP_WOL_UCAST;
			if ((mask & IFCAP_WOL_MCAST) != 0)
				ifp->if_capenable ^= IFCAP_WOL_MCAST;
			if ((mask & IFCAP_WOL_MAGIC) != 0)
				ifp->if_capenable ^= IFCAP_WOL_MAGIC;
		}
		SIS_UNLOCK(sc);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}