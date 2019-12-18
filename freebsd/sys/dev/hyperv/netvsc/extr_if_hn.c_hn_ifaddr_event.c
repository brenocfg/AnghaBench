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
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  hn_rxvf_change (void*,struct ifnet*,int) ; 

__attribute__((used)) static void
hn_ifaddr_event(void *arg, struct ifnet *ifp)
{

	hn_rxvf_change(arg, ifp, ifp->if_flags & IFF_UP);
}