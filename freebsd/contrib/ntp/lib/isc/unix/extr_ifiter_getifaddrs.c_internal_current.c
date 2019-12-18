#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ifaddrs {int ifa_flags; int /*<<< orphan*/ * ifa_name; TYPE_7__* ifa_broadaddr; TYPE_7__* ifa_dstaddr; TYPE_7__* ifa_netmask; TYPE_7__* ifa_addr; } ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_10__ {int flags; int af; struct TYPE_10__* name; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dstaddress; int /*<<< orphan*/  netmask; int /*<<< orphan*/  address; } ;
struct TYPE_9__ {TYPE_2__ current; struct ifaddrs* pos; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;
struct TYPE_11__ {int sa_family; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int IFF_BROADCAST ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int INTERFACE_F_BROADCAST ; 
 int INTERFACE_F_LOOPBACK ; 
 int INTERFACE_F_MULTICAST ; 
 int INTERFACE_F_POINTTOPOINT ; 
 int INTERFACE_F_UP ; 
 int /*<<< orphan*/  ISC_R_IGNORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_IFITER (TYPE_1__*) ; 
 int /*<<< orphan*/  get_addr (int,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_nametoindex (TYPE_2__*) ; 
 int /*<<< orphan*/  linux_if_inet6_current (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seenv6 ; 
 unsigned int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_result_t
internal_current(isc_interfaceiter_t *iter) {
	struct ifaddrs *ifa;
	int family;
	unsigned int namelen;

	REQUIRE(VALID_IFITER(iter));

	ifa = iter->pos;

#ifdef __linux
	/*
	 * [Bug 2792]
	 * burnicki: iter->pos is usually never NULL here (anymore?),
	 * so linux_if_inet6_current(iter) is never called here.
	 * However, that routine would check (under Linux), if the
	 * interface is in a tentative state, e.g. if there's no link
	 * yet but an IPv6 address has already be assigned.
	 */
	if (iter->pos == NULL)
		return (linux_if_inet6_current(iter));
#endif

	INSIST(ifa != NULL);
	INSIST(ifa->ifa_name != NULL);


#ifdef IFF_RUNNING
	/*
	 * [Bug 2792]
	 * burnicki: if the interface is not running then
	 * it may be in a tentative state. See above.
	 */
	if ((ifa->ifa_flags & IFF_RUNNING) == 0)
		return (ISC_R_IGNORE);
#endif

	if (ifa->ifa_addr == NULL)
		return (ISC_R_IGNORE);

	family = ifa->ifa_addr->sa_family;
	if (family != AF_INET && family != AF_INET6)
		return (ISC_R_IGNORE);

#ifdef __linux
	if (family == AF_INET6)
		seenv6 = ISC_TRUE;
#endif

	memset(&iter->current, 0, sizeof(iter->current));

	namelen = strlen(ifa->ifa_name);
	if (namelen > sizeof(iter->current.name) - 1)
		namelen = sizeof(iter->current.name) - 1;

	memset(iter->current.name, 0, sizeof(iter->current.name));
	memcpy(iter->current.name, ifa->ifa_name, namelen);

	iter->current.flags = 0;

	if ((ifa->ifa_flags & IFF_UP) != 0)
		iter->current.flags |= INTERFACE_F_UP;

	if ((ifa->ifa_flags & IFF_POINTOPOINT) != 0)
		iter->current.flags |= INTERFACE_F_POINTTOPOINT;

	if ((ifa->ifa_flags & IFF_LOOPBACK) != 0)
		iter->current.flags |= INTERFACE_F_LOOPBACK;

	if ((ifa->ifa_flags & IFF_BROADCAST) != 0)
		iter->current.flags |= INTERFACE_F_BROADCAST;

#ifdef IFF_MULTICAST
	if ((ifa->ifa_flags & IFF_MULTICAST) != 0)
		iter->current.flags |= INTERFACE_F_MULTICAST;
#endif

	iter->current.af = family;

	get_addr(family, &iter->current.address, ifa->ifa_addr, ifa->ifa_name);

	if (ifa->ifa_netmask != NULL)
		get_addr(family, &iter->current.netmask, ifa->ifa_netmask,
			 ifa->ifa_name);

	if (ifa->ifa_dstaddr != NULL &&
	    (iter->current.flags & INTERFACE_F_POINTTOPOINT) != 0)
		get_addr(family, &iter->current.dstaddress, ifa->ifa_dstaddr,
			 ifa->ifa_name);

	if (ifa->ifa_broadaddr != NULL &&
	    (iter->current.flags & INTERFACE_F_BROADCAST) != 0)
		get_addr(family, &iter->current.broadcast, ifa->ifa_broadaddr,
			 ifa->ifa_name);

#ifdef ISC_PLATFORM_HAVEIFNAMETOINDEX
	iter->current.ifindex = if_nametoindex(iter->current.name);
#endif
	return (ISC_R_SUCCESS);
}