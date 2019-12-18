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
struct TYPE_2__ {int /*<<< orphan*/  sa_family; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; TYPE_1__ ifr_addr; } ;
struct ifnet {int if_flags; int if_capenable; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_drv_flags; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  AF_INET 135 
#define  AF_INET6 134 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  LO_CSUM_FEATURES ; 
 int /*<<< orphan*/  LO_CSUM_FEATURES6 ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCSIFADDR 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 

int
loioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifreq *ifr = (struct ifreq *)data;
	int error = 0, mask;

	switch (cmd) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		if_link_state_change(ifp, LINK_STATE_UP);
		/*
		 * Everything else is done at a higher level.
		 */
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		if (ifr == NULL) {
			error = EAFNOSUPPORT;		/* XXX */
			break;
		}
		switch (ifr->ifr_addr.sa_family) {

#ifdef INET
		case AF_INET:
			break;
#endif
#ifdef INET6
		case AF_INET6:
			break;
#endif

		default:
			error = EAFNOSUPPORT;
			break;
		}
		break;

	case SIOCSIFMTU:
		ifp->if_mtu = ifr->ifr_mtu;
		break;

	case SIOCSIFFLAGS:
		if_link_state_change(ifp, (ifp->if_flags & IFF_UP) ?
		    LINK_STATE_UP: LINK_STATE_DOWN);
		break;

	case SIOCSIFCAP:
		mask = ifp->if_capenable ^ ifr->ifr_reqcap;
		if ((mask & IFCAP_RXCSUM) != 0)
			ifp->if_capenable ^= IFCAP_RXCSUM;
		if ((mask & IFCAP_TXCSUM) != 0)
			ifp->if_capenable ^= IFCAP_TXCSUM;
		if ((mask & IFCAP_RXCSUM_IPV6) != 0) {
#if 0
			ifp->if_capenable ^= IFCAP_RXCSUM_IPV6;
#else
			error = EOPNOTSUPP;
			break;
#endif
		}
		if ((mask & IFCAP_TXCSUM_IPV6) != 0) {
#if 0
			ifp->if_capenable ^= IFCAP_TXCSUM_IPV6;
#else
			error = EOPNOTSUPP;
			break;
#endif
		}
		ifp->if_hwassist = 0;
		if (ifp->if_capenable & IFCAP_TXCSUM)
			ifp->if_hwassist = LO_CSUM_FEATURES;
#if 0
		if (ifp->if_capenable & IFCAP_TXCSUM_IPV6)
			ifp->if_hwassist |= LO_CSUM_FEATURES6;
#endif
		break;

	default:
		error = EINVAL;
	}
	return (error);
}