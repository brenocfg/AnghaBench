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
struct ste_softc {int ste_if_flags; int /*<<< orphan*/  ste_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_capabilities; struct ste_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct ste_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_POLLING ; 
 int IFCAP_WOL_MAGIC ; 
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
 int /*<<< orphan*/  STE_IMR ; 
 int /*<<< orphan*/  STE_INTRS ; 
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ste_init_locked (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_poll ; 
 int /*<<< orphan*/  ste_rxfilter (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_stop (struct ste_softc*) ; 

__attribute__((used)) static int
ste_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct ste_softc *sc;
	struct ifreq *ifr;
	struct mii_data *mii;
	int error = 0, mask;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;

	switch (command) {
	case SIOCSIFFLAGS:
		STE_LOCK(sc);
		if ((ifp->if_flags & IFF_UP) != 0) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->ste_if_flags) &
			     (IFF_PROMISC | IFF_ALLMULTI)) != 0)
				ste_rxfilter(sc);
			else
				ste_init_locked(sc);
		} else if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			ste_stop(sc);
		sc->ste_if_flags = ifp->if_flags;
		STE_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		STE_LOCK(sc);
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
			ste_rxfilter(sc);
		STE_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->ste_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
		STE_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
#ifdef DEVICE_POLLING
		if ((mask & IFCAP_POLLING) != 0 &&
		    (IFCAP_POLLING & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_POLLING;
			if ((IFCAP_POLLING & ifp->if_capenable) != 0) {
				error = ether_poll_register(ste_poll, ifp);
				if (error != 0) {
					STE_UNLOCK(sc);
					break;
				}
				/* Disable interrupts. */
				CSR_WRITE_2(sc, STE_IMR, 0);
			} else {
				error = ether_poll_deregister(ifp);
				/* Enable interrupts. */
				CSR_WRITE_2(sc, STE_IMR, STE_INTRS);
			}
		}
#endif /* DEVICE_POLLING */
		if ((mask & IFCAP_WOL_MAGIC) != 0 &&
		    (ifp->if_capabilities & IFCAP_WOL_MAGIC) != 0)
			ifp->if_capenable ^= IFCAP_WOL_MAGIC;
		STE_UNLOCK(sc);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}