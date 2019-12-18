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
struct ifnet {int if_flags; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int ND6_IFF_IFDISABLED ; 
 int ND6_IFF_NO_DAD ; 
 TYPE_1__* ND_IFINFO (struct ifnet*) ; 

int
in6if_do_dad(struct ifnet *ifp)
{

	if ((ifp->if_flags & IFF_LOOPBACK) != 0)
		return (0);
	if ((ifp->if_flags & IFF_MULTICAST) == 0)
		return (0);
	if ((ND_IFINFO(ifp)->flags &
	    (ND6_IFF_IFDISABLED | ND6_IFF_NO_DAD)) != 0)
		return (0);
	return (1);
}