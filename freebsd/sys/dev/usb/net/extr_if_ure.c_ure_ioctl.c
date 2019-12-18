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
typedef  scalar_t__ u_long ;
struct usb_ether {int dummy; } ;
struct ure_softc {int dummy; } ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_capenable; int if_drv_flags; struct usb_ether* if_softc; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 scalar_t__ SIOCSIFCAP ; 
 int /*<<< orphan*/  URE_LOCK (struct ure_softc*) ; 
 int /*<<< orphan*/  URE_UNLOCK (struct ure_softc*) ; 
 struct ure_softc* uether_getsc (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_init (struct usb_ether*) ; 
 int uether_ioctl (struct ifnet*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
ure_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct usb_ether *ue = ifp->if_softc;
	struct ure_softc *sc;
	struct ifreq *ifr;
	int error, mask, reinit;

	sc = uether_getsc(ue);
	ifr = (struct ifreq *)data;
	error = 0;
	reinit = 0;
	if (cmd == SIOCSIFCAP) {
		URE_LOCK(sc);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		if (reinit > 0 && ifp->if_drv_flags & IFF_DRV_RUNNING)
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		else
			reinit = 0;
		URE_UNLOCK(sc);
		if (reinit > 0)
			uether_init(ue);
	} else
		error = uether_ioctl(ifp, cmd, data);

	return (error);
}