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
struct ifnet {int if_flags; int if_drv_flags; struct emac_softc* if_softc; } ;
struct emac_softc {int emac_if_flags; int /*<<< orphan*/  emac_miibus; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_LOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  EMAC_UNLOCK (struct emac_softc*) ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 132 
#define  SIOCDELMULTI 131 
#define  SIOCGIFMEDIA 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_init_locked (struct emac_softc*) ; 
 int /*<<< orphan*/  emac_set_rx_mode (struct emac_softc*) ; 
 int /*<<< orphan*/  emac_stop_locked (struct emac_softc*) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
emac_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct emac_softc *sc;
	struct mii_data *mii;
	struct ifreq *ifr;
	int error = 0;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;

	switch (command) {
	case SIOCSIFFLAGS:
		EMAC_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
				if ((ifp->if_flags ^ sc->emac_if_flags) &
				    (IFF_PROMISC | IFF_ALLMULTI))
					emac_set_rx_mode(sc);
			} else
				emac_init_locked(sc);
		} else {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
				emac_stop_locked(sc);
		}
		sc->emac_if_flags = ifp->if_flags;
		EMAC_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		EMAC_LOCK(sc);
		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			emac_set_rx_mode(sc);
		}
		EMAC_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->emac_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}
	return (error);
}