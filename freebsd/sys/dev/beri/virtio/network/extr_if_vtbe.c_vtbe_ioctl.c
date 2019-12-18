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
struct vtbe_softc {int if_flags; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; struct vtbe_softc* if_softc; } ;
struct ifmediareq {int ifm_count; int ifm_status; int ifm_active; int ifm_current; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFCAP_VLAN_MTU ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int IFM_10G_T ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFADDR 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int /*<<< orphan*/  VTBE_LOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  VTBE_UNLOCK (struct vtbe_softc*) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  pio_enable_irq (struct vtbe_softc*,int) ; 
 int /*<<< orphan*/  vtbe_init_locked (struct vtbe_softc*) ; 
 int /*<<< orphan*/  vtbe_stop_locked (struct vtbe_softc*) ; 

__attribute__((used)) static int
vtbe_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifmediareq *ifmr;
	struct vtbe_softc *sc;
	struct ifreq *ifr;
	int mask, error;

	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;

	error = 0;
	switch (cmd) {
	case SIOCSIFFLAGS:
		VTBE_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			pio_enable_irq(sc, 1);

			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
				vtbe_init_locked(sc);
			}
		} else {
			pio_enable_irq(sc, 0);

			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				vtbe_stop_locked(sc);
			}
		}
		sc->if_flags = ifp->if_flags;
		VTBE_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		ifmr = (struct ifmediareq *)data;
		ifmr->ifm_count = 1;
		ifmr->ifm_status = (IFM_AVALID | IFM_ACTIVE);
		ifmr->ifm_active = (IFM_ETHER | IFM_10G_T | IFM_FDX);
		ifmr->ifm_current = ifmr->ifm_active;
		break;
	case SIOCSIFCAP:
		mask = ifp->if_capenable ^ ifr->ifr_reqcap;
		if (mask & IFCAP_VLAN_MTU) {
			ifp->if_capenable ^= IFCAP_VLAN_MTU;
		}
		break;

	case SIOCSIFADDR:
		pio_enable_irq(sc, 1);
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}