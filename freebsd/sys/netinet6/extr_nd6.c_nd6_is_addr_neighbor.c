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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct llentry {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_AFDATA_UNLOCK_ASSERT (struct ifnet*) ; 
 int /*<<< orphan*/  LLE_RUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 scalar_t__ nd6_is_new_addr_neighbor (struct sockaddr_in6 const*,struct ifnet*) ; 
 struct llentry* nd6_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifnet*) ; 

int
nd6_is_addr_neighbor(const struct sockaddr_in6 *addr, struct ifnet *ifp)
{
	struct llentry *lle;
	int rc = 0;

	NET_EPOCH_ASSERT();
	IF_AFDATA_UNLOCK_ASSERT(ifp);
	if (nd6_is_new_addr_neighbor(addr, ifp))
		return (1);

	/*
	 * Even if the address matches none of our addresses, it might be
	 * in the neighbor cache.
	 */
	if ((lle = nd6_lookup(&addr->sin6_addr, 0, ifp)) != NULL) {
		LLE_RUNLOCK(lle);
		rc = 1;
	}
	return (rc);
}