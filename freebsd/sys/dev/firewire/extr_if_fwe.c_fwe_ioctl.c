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
struct ifstat {int /*<<< orphan*/  ascii; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; scalar_t__ if_softc; } ;
struct TYPE_2__ {struct firewire_comm* fc; } ;
struct fwe_softc {int stream_ch; int dma_ch; TYPE_1__ fd; int /*<<< orphan*/  eth_softc; } ;
struct fwe_eth_softc {struct fwe_softc* fwe; } ;
struct firewire_comm {int /*<<< orphan*/  (* set_intr ) (struct firewire_comm*,int) ;} ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 132 
#define  SIOCDELMULTI 131 
#define  SIOCGIFSTATUS 130 
#define  SIOCSIFCAP 129 
#define  SIOCSIFFLAGS 128 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int /*<<< orphan*/  fwe_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwe_poll ; 
 int /*<<< orphan*/  fwe_stop (struct fwe_softc*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  stub1 (struct firewire_comm*,int) ; 
 int /*<<< orphan*/  stub2 (struct firewire_comm*,int) ; 

__attribute__((used)) static int
fwe_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct fwe_softc *fwe = ((struct fwe_eth_softc *)ifp->if_softc)->fwe;
	struct ifstat *ifs = NULL;
	int s, error;

	switch (cmd) {
		case SIOCSIFFLAGS:
			s = splimp();
			if (ifp->if_flags & IFF_UP) {
				if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
					fwe_init(&fwe->eth_softc);
			} else {
				if (ifp->if_drv_flags & IFF_DRV_RUNNING)
					fwe_stop(fwe);
			}
			/* XXX keep promiscoud mode */
			ifp->if_flags |= IFF_PROMISC;
			splx(s);
			break;
		case SIOCADDMULTI:
		case SIOCDELMULTI:
			break;

		case SIOCGIFSTATUS:
			s = splimp();
			ifs = (struct ifstat *)data;
			snprintf(ifs->ascii, sizeof(ifs->ascii),
			    "\tch %d dma %d\n",	fwe->stream_ch, fwe->dma_ch);
			splx(s);
			break;
		case SIOCSIFCAP:
#ifdef DEVICE_POLLING
		    {
			struct ifreq *ifr = (struct ifreq *) data;
			struct firewire_comm *fc = fwe->fd.fc;

			if (ifr->ifr_reqcap & IFCAP_POLLING &&
			    !(ifp->if_capenable & IFCAP_POLLING)) {
				error = ether_poll_register(fwe_poll, ifp);
				if (error)
					return (error);
				/* Disable interrupts */
				fc->set_intr(fc, 0);
				ifp->if_capenable |= IFCAP_POLLING;
				return (error);
			}
			if (!(ifr->ifr_reqcap & IFCAP_POLLING) &&
			    ifp->if_capenable & IFCAP_POLLING) {
				error = ether_poll_deregister(ifp);
				/* Enable interrupts. */
				fc->set_intr(fc, 1);
				ifp->if_capenable &= ~IFCAP_POLLING;
				return (error);
			}
		    }
#endif /* DEVICE_POLLING */
			break;
		default:
			s = splimp();
			error = ether_ioctl(ifp, cmd, data);
			splx(s);
			return (error);
	}

	return (0);
}