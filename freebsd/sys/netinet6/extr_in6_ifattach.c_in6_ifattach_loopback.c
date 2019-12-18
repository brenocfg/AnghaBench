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
struct sockaddr_in6 {int dummy; } ;
struct TYPE_3__ {void* ia6t_pltime; void* ia6t_vltime; } ;
struct TYPE_4__ {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct in6_aliasreq {TYPE_1__ ifra_lifetime; TYPE_2__ ifra_dstaddr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LOG_ERR ; 
 void* ND6_INFINITE_LIFETIME ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  in6_prepare_ifra (struct in6_aliasreq*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int in6_update_ifa (struct ifnet*,struct in6_aliasreq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int /*<<< orphan*/  in6mask128 ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
in6_ifattach_loopback(struct ifnet *ifp)
{
	struct in6_aliasreq ifra;
	int error;

	in6_prepare_ifra(&ifra, &in6addr_loopback, &in6mask128);

	/*
	 * Always initialize ia_dstaddr (= broadcast address) to loopback
	 * address.  Follows IPv4 practice - see in_ifinit().
	 */
	ifra.ifra_dstaddr.sin6_len = sizeof(struct sockaddr_in6);
	ifra.ifra_dstaddr.sin6_family = AF_INET6;
	ifra.ifra_dstaddr.sin6_addr = in6addr_loopback;

	/* the loopback  address should NEVER expire. */
	ifra.ifra_lifetime.ia6t_vltime = ND6_INFINITE_LIFETIME;
	ifra.ifra_lifetime.ia6t_pltime = ND6_INFINITE_LIFETIME;

	/*
	 * We are sure that this is a newly assigned address, so we can set
	 * NULL to the 3rd arg.
	 */
	if ((error = in6_update_ifa(ifp, &ifra, NULL, 0)) != 0) {
		nd6log((LOG_ERR, "in6_ifattach_loopback: failed to configure "
		    "the loopback address on %s (errno=%d)\n",
		    if_name(ifp), error));
		return (-1);
	}

	return 0;
}