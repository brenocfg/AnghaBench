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
struct ifvlan {int /*<<< orphan*/  lladdr_task; } ;
struct ifnet {int if_dunit; struct ifvlan* if_softc; } ;
struct if_clone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VLAN ; 
 int /*<<< orphan*/  NET_EPOCH_WAIT () ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct ifvlan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifc_free_unit (struct if_clone*,int) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  vlan_unconfig (struct ifnet*) ; 

__attribute__((used)) static int
vlan_clone_destroy(struct if_clone *ifc, struct ifnet *ifp)
{
	struct ifvlan *ifv = ifp->if_softc;
	int unit = ifp->if_dunit;

	ether_ifdetach(ifp);	/* first, remove it from system-wide lists */
	vlan_unconfig(ifp);	/* now it can be unconfigured and freed */
	/*
	 * We should have the only reference to the ifv now, so we can now
	 * drain any remaining lladdr task before freeing the ifnet and the
	 * ifvlan.
	 */
	taskqueue_drain(taskqueue_thread, &ifv->lladdr_task);
	NET_EPOCH_WAIT();
	if_free(ifp);
	free(ifv, M_VLAN);
	ifc_free_unit(ifc, unit);

	return (0);
}