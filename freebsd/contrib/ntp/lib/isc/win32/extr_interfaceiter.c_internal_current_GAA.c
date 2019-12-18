#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_sockaddr_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_14__ {char* name; int flags; int /*<<< orphan*/  netmask; int /*<<< orphan*/  address; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  af; int /*<<< orphan*/  ifindex; } ;
struct TYPE_11__ {TYPE_6__ current; TYPE_4__* ipuaCur; TYPE_5__* ipaaCur; } ;
typedef  TYPE_3__ isc_interfaceiter_t ;
struct TYPE_13__ {scalar_t__ OperStatus; scalar_t__ IfType; int Flags; int /*<<< orphan*/  FriendlyName; int /*<<< orphan*/  Ipv6IfIndex; } ;
struct TYPE_10__ {TYPE_1__* lpSockaddr; } ;
struct TYPE_12__ {scalar_t__ DadState; scalar_t__ SuffixOrigin; TYPE_2__ Address; } ;
struct TYPE_9__ {int /*<<< orphan*/  sa_family; } ;
typedef  TYPE_4__ IP_ADAPTER_UNICAST_ADDRESS ;
typedef  TYPE_5__ IP_ADAPTER_ADDRESSES ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CP_ACP ; 
 unsigned char GAA_find_prefix (TYPE_3__*) ; 
 scalar_t__ IF_TYPE_PPP ; 
 scalar_t__ IF_TYPE_SOFTWARE_LOOPBACK ; 
 int INTERFACE_F_BROADCAST ; 
 int INTERFACE_F_LOOPBACK ; 
 int INTERFACE_F_MULTICAST ; 
 int INTERFACE_F_POINTTOPOINT ; 
 int INTERFACE_F_PRIVACY ; 
 int INTERFACE_F_UP ; 
 int IP_ADAPTER_NO_MULTICAST ; 
 int /*<<< orphan*/  ISC_R_IGNORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ IfOperStatusUp ; 
 scalar_t__ IpDadStatePreferred ; 
 scalar_t__ IpSuffixOriginRandom ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_broadcastaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static isc_result_t
internal_current_GAA(isc_interfaceiter_t *iter) {
	IP_ADAPTER_ADDRESSES *adap;
	IP_ADAPTER_UNICAST_ADDRESS *addr;
	unsigned char prefix_len;

	REQUIRE(iter->ipaaCur != NULL);
	REQUIRE(iter->ipuaCur != NULL);
	adap = iter->ipaaCur;
	addr = iter->ipuaCur;
	if (IpDadStatePreferred != addr->DadState)
		return (ISC_R_IGNORE);
	memset(&iter->current, 0, sizeof(iter->current));
	iter->current.af = addr->Address.lpSockaddr->sa_family;
	isc_netaddr_fromsockaddr(&iter->current.address,
	    (isc_sockaddr_t *)addr->Address.lpSockaddr);
	if (AF_INET6 == iter->current.af)
		iter->current.ifindex = adap->Ipv6IfIndex;
	iter->current.name[0] = '\0';
	WideCharToMultiByte(
		CP_ACP, 
		0, 
		adap->FriendlyName,
		-1,
		iter->current.name,
		sizeof(iter->current.name),
		NULL,
		NULL);
	iter->current.name[sizeof(iter->current.name) - 1] = '\0';
	if (IfOperStatusUp == adap->OperStatus)
		iter->current.flags |= INTERFACE_F_UP;
	if (IF_TYPE_PPP == adap->IfType)
		iter->current.flags |= INTERFACE_F_POINTTOPOINT;
	else if (IF_TYPE_SOFTWARE_LOOPBACK == adap->IfType)
		iter->current.flags |= INTERFACE_F_LOOPBACK;
	if ((IP_ADAPTER_NO_MULTICAST & adap->Flags) == 0)
		iter->current.flags |= INTERFACE_F_MULTICAST;
	if (IpSuffixOriginRandom == addr->SuffixOrigin)
		iter->current.flags |= INTERFACE_F_PRIVACY;

	prefix_len = GAA_find_prefix(iter);
	/* I'm failing to see a broadcast flag via GAA */
	if (AF_INET == iter->current.af && prefix_len < 32 &&
	    (INTERFACE_F_LOOPBACK & iter->current.flags) == 0) {
		iter->current.flags |= INTERFACE_F_BROADCAST;
		get_broadcastaddr(&iter->current.broadcast,
				  &iter->current.address,
				  &iter->current.netmask);
	}
	return (ISC_R_SUCCESS);
}