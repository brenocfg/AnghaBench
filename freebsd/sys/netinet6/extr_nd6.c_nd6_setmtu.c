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
struct ifnet {int /*<<< orphan*/ ** if_afdata; } ;

/* Variables and functions */
 size_t AF_INET6 ; 
 int /*<<< orphan*/  ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  nd6_setmtu0 (struct ifnet*,int /*<<< orphan*/ ) ; 

void
nd6_setmtu(struct ifnet *ifp)
{
	if (ifp->if_afdata[AF_INET6] == NULL)
		return;

	nd6_setmtu0(ifp, ND_IFINFO(ifp));
}