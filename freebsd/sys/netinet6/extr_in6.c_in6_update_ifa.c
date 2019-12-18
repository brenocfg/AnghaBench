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
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; } ;
struct in6_aliasreq {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  ifa_free (int /*<<< orphan*/ *) ; 
 struct in6_ifaddr* in6_alloc_ifa (struct ifnet*,struct in6_aliasreq*,int) ; 
 int in6_broadcast_ifa (struct ifnet*,struct in6_aliasreq*,struct in6_ifaddr*,int) ; 
 int /*<<< orphan*/  in6_unlink_ifa (struct in6_ifaddr*,struct ifnet*) ; 
 int in6_update_ifa_internal (struct ifnet*,struct in6_aliasreq*,struct in6_ifaddr*,int,int) ; 
 int in6_validate_ifra (struct ifnet*,struct in6_aliasreq*,struct in6_ifaddr*,int) ; 

int
in6_update_ifa(struct ifnet *ifp, struct in6_aliasreq *ifra,
    struct in6_ifaddr *ia, int flags)
{
	int error, hostIsNew = 0;

	if ((error = in6_validate_ifra(ifp, ifra, ia, flags)) != 0)
		return (error);

	if (ia == NULL) {
		hostIsNew = 1;
		if ((ia = in6_alloc_ifa(ifp, ifra, flags)) == NULL)
			return (ENOBUFS);
	}

	error = in6_update_ifa_internal(ifp, ifra, ia, hostIsNew, flags);
	if (error != 0) {
		if (hostIsNew != 0) {
			in6_unlink_ifa(ia, ifp);
			ifa_free(&ia->ia_ifa);
		}
		return (error);
	}

	if (hostIsNew)
		error = in6_broadcast_ifa(ifp, ifra, ia, flags);

	return (error);
}