#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_4__ {int /*<<< orphan*/ * sa_data; } ;
struct ifreq {int ifr_lan_pcp; int /*<<< orphan*/  ifr_mtu; TYPE_2__ ifr_addr; } ;
struct ifnet {int if_pcp; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_softc; int /*<<< orphan*/  (* if_init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_flags; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
#define  AF_INET 133 
 int EINVAL ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IFNET_EVENT_PCP ; 
 int IFNET_PCP_NONE ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  PRIV_NET_SETLANPCP ; 
#define  SIOCGIFADDR 132 
#define  SIOCGLANPCP 131 
#define  SIOCSIFADDR 130 
#define  SIOCSIFMTU 129 
#define  SIOCSLANPCP 128 
 int /*<<< orphan*/  arp_ifinit (struct ifnet*,struct ifaddr*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  ifnet_event ; 
 int priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int
ether_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
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
		bcopy(IF_LLADDR(ifp), &ifr->ifr_addr.sa_data[0],
		    ETHER_ADDR_LEN);
		break;

	case SIOCSIFMTU:
		/*
		 * Set the interface MTU.
		 */
		if (ifr->ifr_mtu > ETHERMTU) {
			error = EINVAL;
		} else {
			ifp->if_mtu = ifr->ifr_mtu;
		}
		break;

	case SIOCSLANPCP:
		error = priv_check(curthread, PRIV_NET_SETLANPCP);
		if (error != 0)
			break;
		if (ifr->ifr_lan_pcp > 7 &&
		    ifr->ifr_lan_pcp != IFNET_PCP_NONE) {
			error = EINVAL;
		} else {
			ifp->if_pcp = ifr->ifr_lan_pcp;
			/* broadcast event about PCP change */
			EVENTHANDLER_INVOKE(ifnet_event, ifp, IFNET_EVENT_PCP);
		}
		break;

	case SIOCGLANPCP:
		ifr->ifr_lan_pcp = ifp->if_pcp;
		break;

	default:
		error = EINVAL;			/* XXX netbsd has ENOTTY??? */
		break;
	}
	return (error);
}