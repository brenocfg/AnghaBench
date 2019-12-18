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
struct sockaddr_dl {int /*<<< orphan*/  sdl_type; } ;
struct ifaddrs {int ifa_flags; TYPE_3__* ifa_addr; TYPE_3__* ifa_netmask; int /*<<< orphan*/  ifa_name; } ;
struct if_info {char* ii_ifname; int ii_fd; scalar_t__ ii_ipaddr; scalar_t__ ii_netmask; int /*<<< orphan*/  ii_eaddr; struct if_info* ii_next; } ;
struct TYPE_6__ {int sa_family; } ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_LINK 130 
 int IFF_LOOPBACK ; 
 int IFF_POINTOPOINT ; 
 int IFF_UP ; 
#define  IFT_ETHER 129 
#define  IFT_L2VLAN 128 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 TYPE_2__* SATOSIN (TYPE_3__*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct if_info*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct if_info* iflist ; 
 scalar_t__ ipaddrtonetmask (scalar_t__) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct if_info*,struct if_info*,int) ; 
 int /*<<< orphan*/  pidfile_fh ; 
 int /*<<< orphan*/  pidfile_remove (int /*<<< orphan*/ ) ; 
 int rarp_open (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_one(struct ifaddrs *ifa, char *target, int pass1)
{
	struct if_info *ii, *ii2;
	struct sockaddr_dl *ll;
	int family;

	family = ifa->ifa_addr->sa_family;
	switch (family) {
	case AF_INET:
		if (pass1)
			/* Consider only AF_LINK during pass1. */
			return;
		/* FALLTHROUGH */
	case AF_LINK:
		if (!(ifa->ifa_flags & IFF_UP) ||
		    (ifa->ifa_flags & (IFF_LOOPBACK | IFF_POINTOPOINT)))
			return;
		break;
	default:
		return;
	}

	/* Don't bother going any further if not the target interface */
	if (target != NULL && strcmp(ifa->ifa_name, target) != 0)
		return;

	/* Look for interface in list */
	for (ii = iflist; ii != NULL; ii = ii->ii_next)
		if (strcmp(ifa->ifa_name, ii->ii_ifname) == 0)
			break;

	if (pass1 && ii != NULL)
		/* We've already seen that interface once. */
		return;

	/* Allocate a new one if not found */
	if (ii == NULL) {
		ii = (struct if_info *)malloc(sizeof(*ii));
		if (ii == NULL) {
			logmsg(LOG_ERR, "malloc: %m");
			pidfile_remove(pidfile_fh);
			exit(1);
		}
		bzero(ii, sizeof(*ii));
		ii->ii_fd = -1;
		strlcpy(ii->ii_ifname, ifa->ifa_name, sizeof(ii->ii_ifname));
		ii->ii_next = iflist;
		iflist = ii;
	} else if (!pass1 && ii->ii_ipaddr != 0) {
		/*
		 * Second AF_INET definition for that interface: clone
		 * the existing one, and work on that cloned one.
		 * This must be another IP address for this interface,
		 * so avoid killing the previous configuration.
		 */
		ii2 = (struct if_info *)malloc(sizeof(*ii2));
		if (ii2 == NULL) {
			logmsg(LOG_ERR, "malloc: %m");
			pidfile_remove(pidfile_fh);
			exit(1);
		}
		memcpy(ii2, ii, sizeof(*ii2));
		ii2->ii_fd = -1;
		ii2->ii_next = iflist;
		iflist = ii2;

		ii = ii2;
	}

	switch (family) {
	case AF_INET:
		ii->ii_ipaddr = SATOSIN(ifa->ifa_addr)->sin_addr.s_addr;
		ii->ii_netmask = SATOSIN(ifa->ifa_netmask)->sin_addr.s_addr;
		if (ii->ii_netmask == 0)
			ii->ii_netmask = ipaddrtonetmask(ii->ii_ipaddr);
		if (ii->ii_fd < 0)
			ii->ii_fd = rarp_open(ii->ii_ifname);
		break;

	case AF_LINK:
		ll = (struct sockaddr_dl *)ifa->ifa_addr;
		switch (ll->sdl_type) {
		case IFT_ETHER:
		case IFT_L2VLAN:
			bcopy(LLADDR(ll), ii->ii_eaddr, 6);
		}
		break;
	}
}