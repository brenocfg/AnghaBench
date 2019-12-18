#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_5__ {int /*<<< orphan*/ * sa_data; } ;
struct ifreq {int ifr_mtu; TYPE_2__ ifr_addr; } ;
struct ifnet {int if_mtu; int /*<<< orphan*/  if_softc; int /*<<< orphan*/  (* if_init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_flags; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
struct fw_hwaddr {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  fc_hwaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
#define  AF_INET 131 
 int EINVAL ; 
 int /*<<< orphan*/  IFF_UP ; 
 TYPE_3__* IFP2FWC (struct ifnet*) ; 
#define  SIOCGIFADDR 130 
#define  SIOCSIFADDR 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int
firewire_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	struct ifaddr *ifa = (struct ifaddr *) data;
	struct ifreq *ifr = (struct ifreq *) data;
	int error = 0;

	switch (command) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;

		switch (ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			ifp->if_init(ifp->if_softc);	/* before arpwhohas */
			arp_ifinit(ifp, ifa);
			break;
#endif
		default:
			ifp->if_init(ifp->if_softc);
			break;
		}
		break;

	case SIOCGIFADDR:
		bcopy(&IFP2FWC(ifp)->fc_hwaddr, &ifr->ifr_addr.sa_data[0],
		    sizeof(struct fw_hwaddr));
		break;

	case SIOCSIFMTU:
		/*
		 * Set the interface MTU.
		 */
		if (ifr->ifr_mtu > 1500) {
			error = EINVAL;
		} else {
			ifp->if_mtu = ifr->ifr_mtu;
		}
		break;
	default:
		error = EINVAL;			/* XXX netbsd has ENOTTY??? */
		break;
	}
	return (error);
}