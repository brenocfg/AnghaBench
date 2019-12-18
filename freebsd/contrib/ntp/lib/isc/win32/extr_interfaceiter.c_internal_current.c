#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_sockaddr_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  netmask; int /*<<< orphan*/  address; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dstaddress; int /*<<< orphan*/  af; } ;
struct TYPE_6__ {unsigned long iiFlags; int /*<<< orphan*/  iiNetmask; int /*<<< orphan*/  iiBroadcastAddress; int /*<<< orphan*/  iiAddress; } ;
struct TYPE_7__ {scalar_t__ numIF; TYPE_3__ current; TYPE_1__ IFData; } ;
typedef  TYPE_2__ isc_interfaceiter_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ FALSE ; 
 unsigned long IFF_BROADCAST ; 
 unsigned long IFF_LOOPBACK ; 
 unsigned long IFF_MULTICAST ; 
 unsigned long IFF_POINTTOPOINT ; 
 unsigned long IFF_UP ; 
 int INTERFACE_F_BROADCAST ; 
 int INTERFACE_F_LOOPBACK ; 
 int INTERFACE_F_MULTICAST ; 
 int INTERFACE_F_POINTTOPOINT ; 
 int INTERFACE_F_UP ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ TRUE ; 
 int VALID_IFITER (TYPE_2__*) ; 
 int /*<<< orphan*/  get_broadcastaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 

__attribute__((used)) static isc_result_t
internal_current(isc_interfaceiter_t *iter) {
	BOOL ifNamed = FALSE;
	unsigned long flags;

	REQUIRE(VALID_IFITER(iter));
	REQUIRE(iter->numIF >= 0);

	memset(&iter->current, 0, sizeof(iter->current));
	iter->current.af = AF_INET;

	isc_netaddr_fromsockaddr(&iter->current.address,
	    (isc_sockaddr_t *)&(iter->IFData.iiAddress));

	/*
	 * Get interface flags.
	 */

	iter->current.flags = 0;
	flags = iter->IFData.iiFlags;

	if ((flags & IFF_UP) != 0)
		iter->current.flags |= INTERFACE_F_UP;

	if ((flags & IFF_BROADCAST) != 0)
		iter->current.flags |= INTERFACE_F_BROADCAST;

	if ((flags & IFF_MULTICAST) != 0)
		iter->current.flags |= INTERFACE_F_MULTICAST;

	if ((flags & IFF_POINTTOPOINT) != 0) {
		iter->current.flags |= INTERFACE_F_POINTTOPOINT;
		snprintf(iter->current.name, sizeof(iter->current.name),
			 "PPP %d", iter->numIF);
		ifNamed = TRUE;
	}

	if ((flags & IFF_LOOPBACK) != 0) {
		iter->current.flags |= INTERFACE_F_LOOPBACK;
		snprintf(iter->current.name, sizeof(iter->current.name),
			"v4loop %d", iter->numIF);
		ifNamed = TRUE;
	}

	/*
	 * If the interface is point-to-point, get the destination address.
	 */
	if ((iter->current.flags & INTERFACE_F_POINTTOPOINT) != 0)
		isc_netaddr_fromsockaddr(&iter->current.dstaddress,
		    (isc_sockaddr_t *)&(iter->IFData.iiBroadcastAddress));

	/*
	 * Get the network mask.
	 */
	isc_netaddr_fromsockaddr(&iter->current.netmask,
	    (isc_sockaddr_t *)&(iter->IFData.iiNetmask));

	/*
	 * If the interface is broadcast, get the broadcast address,
	 * based on the unicast address and network mask.
	 */
	if ((iter->current.flags & INTERFACE_F_BROADCAST) != 0)
		get_broadcastaddr(&iter->current.broadcast,
				  &iter->current.address,
				  &iter->current.netmask);

	if (ifNamed == FALSE)
		snprintf(iter->current.name, sizeof(iter->current.name),
			"IPv4 %d", iter->numIF);

	return (ISC_R_SUCCESS);
}