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
struct TYPE_3__ {scalar_t__ ia6t_vltime; scalar_t__ ia6t_pltime; void* ia6t_preferred; void* ia6t_expire; } ;
struct in6_ifaddr {int ia6_flags; TYPE_1__ ia6_lifetime; void* ia6_updatetime; } ;
struct in6_aliasreq {int ifra_flags; TYPE_1__ ifra_lifetime; } ;
struct ifnet {int dummy; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IN6_IFF_DEPRECATED ; 
 int IN6_IFF_DUPLICATED ; 
 int IN6_IFF_TENTATIVE ; 
 int ND6_IFF_IFDISABLED ; 
 scalar_t__ ND6_INFINITE_LIFETIME ; 
 TYPE_2__* ND_IFINFO (struct ifnet*) ; 
 int in6_notify_ifa (struct ifnet*,struct in6_ifaddr*,struct in6_aliasreq*,int) ; 
 scalar_t__ in6if_do_dad (struct ifnet*) ; 
 void* time_uptime ; 

__attribute__((used)) static int
in6_update_ifa_internal(struct ifnet *ifp, struct in6_aliasreq *ifra,
    struct in6_ifaddr *ia, int hostIsNew, int flags)
{
	int error;

	/* update timestamp */
	ia->ia6_updatetime = time_uptime;

	/*
	 * Set lifetimes.  We do not refer to ia6t_expire and ia6t_preferred
	 * to see if the address is deprecated or invalidated, but initialize
	 * these members for applications.
	 */
	ia->ia6_lifetime = ifra->ifra_lifetime;
	if (ia->ia6_lifetime.ia6t_vltime != ND6_INFINITE_LIFETIME) {
		ia->ia6_lifetime.ia6t_expire =
		    time_uptime + ia->ia6_lifetime.ia6t_vltime;
	} else
		ia->ia6_lifetime.ia6t_expire = 0;
	if (ia->ia6_lifetime.ia6t_pltime != ND6_INFINITE_LIFETIME) {
		ia->ia6_lifetime.ia6t_preferred =
		    time_uptime + ia->ia6_lifetime.ia6t_pltime;
	} else
		ia->ia6_lifetime.ia6t_preferred = 0;

	/*
	 * backward compatibility - if IN6_IFF_DEPRECATED is set from the
	 * userland, make it deprecated.
	 */
	if ((ifra->ifra_flags & IN6_IFF_DEPRECATED) != 0) {
		ia->ia6_lifetime.ia6t_pltime = 0;
		ia->ia6_lifetime.ia6t_preferred = time_uptime;
	}

	/*
	 * configure address flags.
	 */
	ia->ia6_flags = ifra->ifra_flags;

	/*
	 * Make the address tentative before joining multicast addresses,
	 * so that corresponding MLD responses would not have a tentative
	 * source address.
	 */
	ia->ia6_flags &= ~IN6_IFF_DUPLICATED;	/* safety */

	/*
	 * DAD should be performed for an new address or addresses on
	 * an interface with ND6_IFF_IFDISABLED.
	 */
	if (in6if_do_dad(ifp) &&
	    (hostIsNew || (ND_IFINFO(ifp)->flags & ND6_IFF_IFDISABLED)))
		ia->ia6_flags |= IN6_IFF_TENTATIVE;

	/* notify other subsystems */
	error = in6_notify_ifa(ifp, ia, ifra, hostIsNew);

	return (error);
}