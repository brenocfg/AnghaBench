#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct TYPE_11__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {TYPE_6__ sa; struct sockaddr_in sin; } ;
struct sctp_ifa {TYPE_1__ address; scalar_t__ ifa; } ;
struct in_addr {int s_addr; } ;
struct ifaddr {scalar_t__ ifa_netmask; } ;
struct TYPE_10__ {TYPE_3__* ro_rt; } ;
typedef  TYPE_4__ sctp_route_t ;
struct TYPE_9__ {TYPE_6__* rt_gateway; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SCTPDBG_ADDR (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SCTP_DEBUG_OUTPUT1 ; 
 int /*<<< orphan*/  SCTP_DEBUG_OUTPUT2 ; 

int
sctp_v4src_match_nexthop(struct sctp_ifa *sifa, sctp_route_t *ro)
{
#ifdef INET
	struct sockaddr_in *sin, *mask;
	struct ifaddr *ifa;
	struct in_addr srcnetaddr, gwnetaddr;

	if (ro == NULL || ro->ro_rt == NULL ||
	    sifa->address.sa.sa_family != AF_INET) {
		return (0);
	}
	ifa = (struct ifaddr *)sifa->ifa;
	mask = (struct sockaddr_in *)(ifa->ifa_netmask);
	sin = &sifa->address.sin;
	srcnetaddr.s_addr = (sin->sin_addr.s_addr & mask->sin_addr.s_addr);
	SCTPDBG(SCTP_DEBUG_OUTPUT1, "match_nexthop4: src address is ");
	SCTPDBG_ADDR(SCTP_DEBUG_OUTPUT2, &sifa->address.sa);
	SCTPDBG(SCTP_DEBUG_OUTPUT1, "network address is %x\n", srcnetaddr.s_addr);

	sin = (struct sockaddr_in *)ro->ro_rt->rt_gateway;
	gwnetaddr.s_addr = (sin->sin_addr.s_addr & mask->sin_addr.s_addr);
	SCTPDBG(SCTP_DEBUG_OUTPUT1, "match_nexthop4: nexthop is ");
	SCTPDBG_ADDR(SCTP_DEBUG_OUTPUT2, ro->ro_rt->rt_gateway);
	SCTPDBG(SCTP_DEBUG_OUTPUT1, "network address is %x\n", gwnetaddr.s_addr);
	if (srcnetaddr.s_addr == gwnetaddr.s_addr) {
		return (1);
	}
#endif
	return (0);
}