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
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; struct dc_softc* if_softc; } ;
struct dc_softc {int dc_if_flags; int /*<<< orphan*/  dc_miibus; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_IMR ; 
 int DC_INTRS ; 
 int /*<<< orphan*/  DC_LOCK (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_UNLOCK (struct dc_softc*) ; 
 int IFCAP_POLLING ; 
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
 int /*<<< orphan*/  dc_init_locked (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_poll ; 
 int /*<<< orphan*/  dc_setfilt (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_stop (struct dc_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
dc_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct dc_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	struct mii_data *mii;
	int error = 0;

	switch (command) {
	case SIOCSIFFLAGS:
		DC_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			int need_setfilt = (ifp->if_flags ^ sc->dc_if_flags) &
				(IFF_PROMISC | IFF_ALLMULTI);

			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				if (need_setfilt)
					dc_setfilt(sc);
			} else {
				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
				dc_init_locked(sc);
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				dc_stop(sc);
		}
		sc->dc_if_flags = ifp->if_flags;
		DC_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		DC_LOCK(sc);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			dc_setfilt(sc);
		DC_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->dc_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
#ifdef DEVICE_POLLING
		if (ifr->ifr_reqcap & IFCAP_POLLING &&
		    !(ifp->if_capenable & IFCAP_POLLING)) {
			error = ether_poll_register(dc_poll, ifp);
			if (error)
				return(error);
			DC_LOCK(sc);
			/* Disable interrupts */
			CSR_WRITE_4(sc, DC_IMR, 0x00000000);
			ifp->if_capenable |= IFCAP_POLLING;
			DC_UNLOCK(sc);
			return (error);
		}
		if (!(ifr->ifr_reqcap & IFCAP_POLLING) &&
		    ifp->if_capenable & IFCAP_POLLING) {
			error = ether_poll_deregister(ifp);
			/* Enable interrupts. */
			DC_LOCK(sc);
			CSR_WRITE_4(sc, DC_IMR, DC_INTRS);
			ifp->if_capenable &= ~IFCAP_POLLING;
			DC_UNLOCK(sc);
			return (error);
		}
#endif /* DEVICE_POLLING */
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}