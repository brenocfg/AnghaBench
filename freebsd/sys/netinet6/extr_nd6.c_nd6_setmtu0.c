#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct nd_ifinfo {scalar_t__ maxmtu; } ;
struct ifnet {scalar_t__ if_mtu; } ;

/* Variables and functions */
 scalar_t__ IPV6_MMTU ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ V_in6_maxmtu ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  in6_setmaxmtu () ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long) ; 

void
nd6_setmtu0(struct ifnet *ifp, struct nd_ifinfo *ndi)
{
	u_int32_t omaxmtu;

	omaxmtu = ndi->maxmtu;
	ndi->maxmtu = ifp->if_mtu;

	/*
	 * Decreasing the interface MTU under IPV6 minimum MTU may cause
	 * undesirable situation.  We thus notify the operator of the change
	 * explicitly.  The check for omaxmtu is necessary to restrict the
	 * log to the case of changing the MTU, not initializing it.
	 */
	if (omaxmtu >= IPV6_MMTU && ndi->maxmtu < IPV6_MMTU) {
		log(LOG_NOTICE, "nd6_setmtu0: "
		    "new link MTU on %s (%lu) is too small for IPv6\n",
		    if_name(ifp), (unsigned long)ndi->maxmtu);
	}

	if (ndi->maxmtu > V_in6_maxmtu)
		in6_setmaxmtu(); /* check all interfaces just in case */

}