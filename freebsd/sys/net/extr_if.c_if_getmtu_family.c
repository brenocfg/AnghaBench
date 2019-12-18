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
struct ifnet {int if_mtu; } ;
struct domain {int dom_family; int (* dom_ifmtu ) (struct ifnet*) ;struct domain* dom_next; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */
 struct domain* domains ; 
 int stub1 (struct ifnet*) ; 

int
if_getmtu_family(if_t ifp, int family)
{
	struct domain *dp;

	for (dp = domains; dp; dp = dp->dom_next) {
		if (dp->dom_family == family && dp->dom_ifmtu != NULL)
			return (dp->dom_ifmtu((struct ifnet *)ifp));
	}

	return (((struct ifnet *)ifp)->if_mtu);
}