#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_dl {int dummy; } ;
struct ifnet {int /*<<< orphan*/ * if_l2com; TYPE_1__* if_addr; } ;
struct TYPE_2__ {scalar_t__ ifa_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  ng_ether_detach_p (struct ifnet*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 
 int /*<<< orphan*/  uuid_ether_del (int /*<<< orphan*/ ) ; 

void
ether_ifdetach(struct ifnet *ifp)
{
	struct sockaddr_dl *sdl;

	sdl = (struct sockaddr_dl *)(ifp->if_addr->ifa_addr);
	uuid_ether_del(LLADDR(sdl));

	if (ifp->if_l2com != NULL) {
		KASSERT(ng_ether_detach_p != NULL,
		    ("ng_ether_detach_p is NULL"));
		(*ng_ether_detach_p)(ifp);
	}

	bpfdetach(ifp);
	if_detach(ifp);
}