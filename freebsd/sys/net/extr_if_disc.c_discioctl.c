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
struct ifreq {int /*<<< orphan*/  ifr_mtu; TYPE_1__ ifr_addr; } ;
struct ifnet {int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_flags; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  AF_INET 133 
#define  AF_INET6 132 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFF_UP ; 
#define  SIOCADDMULTI 131 
#define  SIOCDELMULTI 130 
#define  SIOCSIFADDR 129 
#define  SIOCSIFMTU 128 

__attribute__((used)) static int
discioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifreq *ifr = (struct ifreq *)data;
	int error = 0;

	switch (cmd) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;

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
	default:
		error = EINVAL;
	}
	return (error);
}