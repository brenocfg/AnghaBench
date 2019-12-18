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
struct nf10bmac_softc {int nf10bmac_if_flags; int /*<<< orphan*/  nf10bmac_media; int /*<<< orphan*/ * nf10bmac_rx_irq_res; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_capabilities; struct nf10bmac_softc* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int IFCAP_POLLING ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NF10BMAC_LOCK (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_CLEAR_DIS (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_ENABLE (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_UNLOCK (struct nf10bmac_softc*) ; 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nf10bmac_init_locked (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_poll ; 
 int /*<<< orphan*/  nf10bmac_stop_locked (struct nf10bmac_softc*) ; 

__attribute__((used)) static int
nf10bmac_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct nf10bmac_softc *sc;
	struct ifreq *ifr;
	int error, mask;

	error = 0;
	sc = ifp->if_softc;
	ifr = (struct ifreq *)data;

	switch (command) {
	case SIOCSIFFLAGS:
		NF10BMAC_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
			    ((ifp->if_flags ^ sc->nf10bmac_if_flags) &
			    (IFF_PROMISC | IFF_ALLMULTI)) != 0)
				/* Nothing we can do. */ ;
			else
				nf10bmac_init_locked(sc);
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			nf10bmac_stop_locked(sc);  
		sc->nf10bmac_if_flags = ifp->if_flags;
		NF10BMAC_UNLOCK(sc);
		break;
	case SIOCSIFCAP:
		NF10BMAC_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
#ifdef DEVICE_POLLING
		if ((mask & IFCAP_POLLING) != 0 &&
		    (IFCAP_POLLING & ifp->if_capabilities) != 0) {
			ifp->if_capenable ^= IFCAP_POLLING;
			if ((IFCAP_POLLING & ifp->if_capenable) != 0) {

				error = ether_poll_register(nf10bmac_poll, ifp);
				if (error != 0) {
					NF10BMAC_UNLOCK(sc);
					break;
				}

				NF10BMAC_RX_INTR_CLEAR_DIS(sc);

			/*
			 * Do not allow disabling of polling if we do
			 * not have interrupts.
			 */
			} else if (sc->nf10bmac_rx_irq_res != NULL) {
				error = ether_poll_deregister(ifp);
				/* Enable interrupts. */
				NF10BMAC_RX_INTR_ENABLE(sc);
			} else {
				ifp->if_capenable ^= IFCAP_POLLING;
				error = EINVAL;
			}
		}
#endif /* DEVICE_POLLING */
                NF10BMAC_UNLOCK(sc);
                break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
                error = ifmedia_ioctl(ifp, ifr, &sc->nf10bmac_media, command);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}