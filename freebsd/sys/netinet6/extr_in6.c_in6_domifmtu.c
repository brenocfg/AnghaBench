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
struct ifnet {int if_mtu; int /*<<< orphan*/ ** if_afdata; } ;

/* Variables and functions */
 size_t AF_INET6 ; 
 int IN6_LINKMTU (struct ifnet*) ; 

int
in6_domifmtu(struct ifnet *ifp)
{
	if (ifp->if_afdata[AF_INET6] == NULL)
		return ifp->if_mtu;

	return (IN6_LINKMTU(ifp));
}