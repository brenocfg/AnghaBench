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
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; struct ffec_softc* if_softc; } ;
struct ffec_softc {int if_flags; struct mii_data* mii_softc; int /*<<< orphan*/  is_detaching; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FFEC_LOCK (struct ffec_softc*) ; 
 int /*<<< orphan*/  FFEC_UNLOCK (struct ffec_softc*) ; 
 int IFCAP_VLAN_MTU ; 
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
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  ffec_init_locked (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_setup_rxfilter (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_stop_locked (struct ffec_softc*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ffec_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ffec_softc *sc;
	struct mii_data *mii;
	struct ifreq *ifr;
	int mask, error;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;

	error = 0;
	switch (cmd) {
	case SIOCSIFFLAGS:
		FFEC_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if ((ifp->if_flags ^ sc->if_flags) &
				    (IFF_PROMISC | IFF_ALLMULTI))
					ffec_setup_rxfilter(sc);
			} else {
				if (!sc->is_detaching)
					ffec_init_locked(sc);
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				ffec_stop_locked(sc);
		}
		sc->if_flags = ifp->if_flags;
		FFEC_UNLOCK(sc);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			FFEC_LOCK(sc);
			ffec_setup_rxfilter(sc);
			FFEC_UNLOCK(sc);
		}
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		mii = sc->mii_softc;
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;

	case SIOCSIFCAP:
		mask = ifp->if_capenable ^ ifr->ifr_reqcap;
		if (mask & IFCAP_VLAN_MTU) {
			/* No work to do except acknowledge the change took. */
			ifp->if_capenable ^= IFCAP_VLAN_MTU;
		}
		break;

	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}       

	return (error);
}