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
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; scalar_t__ if_softc; } ;
struct TYPE_2__ {struct firewire_comm* fc; } ;
struct fwip_softc {TYPE_1__ fd; int /*<<< orphan*/  fw_softc; } ;
struct fwip_eth_softc {struct fwip_softc* fwip; } ;
struct firewire_comm {int /*<<< orphan*/  (* set_intr ) (struct firewire_comm*,int) ;} ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 131 
#define  SIOCDELMULTI 130 
#define  SIOCSIFCAP 129 
#define  SIOCSIFFLAGS 128 
 int ether_poll_deregister (struct ifnet*) ; 
 int ether_poll_register (int /*<<< orphan*/ ,struct ifnet*) ; 
 int firewire_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  fwip_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwip_poll ; 
 int /*<<< orphan*/  fwip_stop (struct fwip_softc*) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  stub1 (struct firewire_comm*,int) ; 
 int /*<<< orphan*/  stub2 (struct firewire_comm*,int) ; 

__attribute__((used)) static int
fwip_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct fwip_softc *fwip = ((struct fwip_eth_softc *)ifp->if_softc)->fwip;
	int s, error;

	switch (cmd) {
	case SIOCSIFFLAGS:
		s = splimp();
		if (ifp->if_flags & IFF_UP) {
			if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
				fwip_init(&fwip->fw_softc);
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				fwip_stop(fwip);
		}
		splx(s);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;
	case SIOCSIFCAP:
#ifdef DEVICE_POLLING
	    {
		struct ifreq *ifr = (struct ifreq *) data;
		struct firewire_comm *fc = fwip->fd.fc;

		if (ifr->ifr_reqcap & IFCAP_POLLING &&
		    !(ifp->if_capenable & IFCAP_POLLING)) {
			error = ether_poll_register(fwip_poll, ifp);
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
		error = firewire_ioctl(ifp, cmd, data);
		splx(s);
		return (error);
	}

	return (0);
}