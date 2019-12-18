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
typedef  int /*<<< orphan*/  u_short ;
struct ifnet {struct ifaddr* if_addr; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int /*<<< orphan*/  ifa_ref (struct ifaddr*) ; 
 struct ifnet* ifnet_byindex (int /*<<< orphan*/ ) ; 

struct ifaddr *
ifaddr_byindex(u_short idx)
{
	struct ifnet *ifp;
	struct ifaddr *ifa = NULL;

	NET_EPOCH_ASSERT();

	ifp = ifnet_byindex(idx);
	if (ifp != NULL && (ifa = ifp->if_addr) != NULL)
		ifa_ref(ifa);
	return (ifa);
}