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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct in_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;
struct ifreq {int ifr_mtu; TYPE_2__ ifr_addr; } ;
struct ifnet {int if_mtu; int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_flags; } ;
struct ifaddr {TYPE_1__* ifa_addr; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  GET_V4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IF_MAXMTU ; 
 int /*<<< orphan*/  IN6_IS_ADDR_6TO4 (int /*<<< orphan*/ *) ; 
 int IPV6_MINMTU ; 
#define  SIOCADDMULTI 132 
#define  SIOCDELMULTI 131 
#define  SIOCGIFMTU 130 
#define  SIOCSIFADDR 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct in_addr*,int) ; 
 int /*<<< orphan*/  isrfc1918addr (struct in_addr*) ; 

__attribute__((used)) static int
stf_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct ifaddr *ifa;
	struct ifreq *ifr;
	struct sockaddr_in6 *sin6;
	struct in_addr addr;
	int error, mtu;

	error = 0;
	switch (cmd) {
	case SIOCSIFADDR:
		ifa = (struct ifaddr *)data;
		if (ifa == NULL || ifa->ifa_addr->sa_family != AF_INET6) {
			error = EAFNOSUPPORT;
			break;
		}
		sin6 = (struct sockaddr_in6 *)ifa->ifa_addr;
		if (!IN6_IS_ADDR_6TO4(&sin6->sin6_addr)) {
			error = EINVAL;
			break;
		}
		bcopy(GET_V4(&sin6->sin6_addr), &addr, sizeof(addr));
		if (isrfc1918addr(&addr)) {
			error = EINVAL;
			break;
		}

		ifp->if_flags |= IFF_UP;
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ifr = (struct ifreq *)data;
		if (ifr && ifr->ifr_addr.sa_family == AF_INET6)
			;
		else
			error = EAFNOSUPPORT;
		break;

	case SIOCGIFMTU:
		break;

	case SIOCSIFMTU:
		ifr = (struct ifreq *)data;
		mtu = ifr->ifr_mtu;
		/* RFC 4213 3.2 ideal world MTU */
		if (mtu < IPV6_MINMTU || mtu > IF_MAXMTU - 20)
			return (EINVAL);
		ifp->if_mtu = mtu;
		break;

	default:
		error = EINVAL;
		break;
	}

	return error;
}