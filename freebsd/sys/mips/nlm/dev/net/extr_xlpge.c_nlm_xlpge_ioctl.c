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
struct nlm_xlpge_softc {int if_flags; int /*<<< orphan*/ * mii_bus; int /*<<< orphan*/  link; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; struct nlm_xlpge_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NLM_LINK_DOWN ; 
 int /*<<< orphan*/  NLM_LINK_UP ; 
#define  SIOCGIFMEDIA 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int /*<<< orphan*/  XLPGE_LOCK (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  XLPGE_UNLOCK (struct nlm_xlpge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ *) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nlm_xlpge_init (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_mac_set_rx_mode (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_port_disable (struct nlm_xlpge_softc*) ; 
 int /*<<< orphan*/  nlm_xlpge_port_enable (struct nlm_xlpge_softc*) ; 

__attribute__((used)) static int
nlm_xlpge_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct mii_data		*mii;
	struct nlm_xlpge_softc	*sc;
	struct ifreq		*ifr;
	int			error;

	sc = ifp->if_softc;
	error = 0;
	ifr = (struct ifreq *)data;

	switch (command) {
	case SIOCSIFFLAGS:
		XLPGE_LOCK(sc);
		sc->if_flags = ifp->if_flags;
		if (ifp->if_flags & IFF_UP) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
				nlm_xlpge_init(sc);
			else
				nlm_xlpge_port_enable(sc);
			nlm_xlpge_mac_set_rx_mode(sc);
			sc->link = NLM_LINK_UP;
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				nlm_xlpge_port_disable(sc);
			sc->link = NLM_LINK_DOWN;
		}
		XLPGE_UNLOCK(sc);
		error = 0;
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		if (sc->mii_bus != NULL) {
			mii = device_get_softc(sc->mii_bus);
			error = ifmedia_ioctl(ifp, ifr, &mii->mii_media,
			    command);
		}
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}