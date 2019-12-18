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
struct rl_softc {int rl_if_flags; int /*<<< orphan*/  rl_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_capabilities; struct rl_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFCAP_WOL ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_MCAST ; 
 int IFCAP_WOL_UCAST ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  RL_IMR ; 
 int RL_INTRS ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rl_init_locked (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_poll ; 
 int /*<<< orphan*/  rl_rxfilter (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_stop (struct rl_softc*) ; 

__attribute__((used)) static int
rl_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct ifreq		*ifr = (struct ifreq *)data;
	struct mii_data		*mii;
	struct rl_softc		*sc = ifp->if_softc;
	int			error = 0, mask;

	switch (command) {
	case SIOCSIFFLAGS:
		RL_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING &&
			    ((ifp->if_flags ^ sc->rl_if_flags) &
                            (IFF_PROMISC | IFF_ALLMULTI)))
				rl_rxfilter(sc);
                        else
				rl_init_locked(sc);
                } else if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			rl_stop(sc);
		sc->rl_if_flags = ifp->if_flags;
		RL_UNLOCK(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		RL_LOCK(sc);
		rl_rxfilter(sc);
		RL_UNLOCK(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		mii = device_get_softc(sc->rl_miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, command);
		break;
	case SIOCSIFCAP:
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
#ifdef DEVICE_POLLING
		if (ifr->ifr_reqcap & IFCAP_POLLING &&
		    !(ifp->if_capenable & IFCAP_POLLING)) {
			error = ether_poll_register(rl_poll, ifp);
			if (error)
				return(error);
			RL_LOCK(sc);
			/* Disable interrupts */
			CSR_WRITE_2(sc, RL_IMR, 0x0000);
			ifp->if_capenable |= IFCAP_POLLING;
			RL_UNLOCK(sc);
			return (error);
			
		}
		if (!(ifr->ifr_reqcap & IFCAP_POLLING) &&
		    ifp->if_capenable & IFCAP_POLLING) {
			error = ether_poll_deregister(ifp);
			/* Enable interrupts. */
			RL_LOCK(sc);
			CSR_WRITE_2(sc, RL_IMR, RL_INTRS);
			ifp->if_capenable &= ~IFCAP_POLLING;
			RL_UNLOCK(sc);
			return (error);
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
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}