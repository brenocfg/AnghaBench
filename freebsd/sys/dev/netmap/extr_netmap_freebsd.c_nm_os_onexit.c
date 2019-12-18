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
struct netmap_adapter {int /*<<< orphan*/  if_transmit; } ;
struct ifnet {int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_transmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCAP_NETMAP ; 
 struct netmap_adapter* NA (struct ifnet*) ; 

void
nm_os_onexit(struct ifnet *ifp)
{
	struct netmap_adapter *na = NA(ifp);

	ifp->if_transmit = na->if_transmit;
	ifp->if_capenable &= ~IFCAP_NETMAP;
}