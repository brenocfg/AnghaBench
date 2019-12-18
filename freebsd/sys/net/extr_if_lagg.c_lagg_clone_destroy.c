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
struct lagg_softc {int sc_destroying; int /*<<< orphan*/  sc_media; int /*<<< orphan*/  sc_ports; int /*<<< orphan*/  vlan_detach; int /*<<< orphan*/  vlan_attach; } ;
struct lagg_port {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_flags; scalar_t__ if_softc; } ;

/* Variables and functions */
 struct lagg_port* CK_SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  LAGG_LIST_LOCK () ; 
 int /*<<< orphan*/  LAGG_LIST_UNLOCK () ; 
 int /*<<< orphan*/  LAGG_SX_DESTROY (struct lagg_softc*) ; 
 int /*<<< orphan*/  LAGG_XLOCK (struct lagg_softc*) ; 
 int /*<<< orphan*/  LAGG_XUNLOCK (struct lagg_softc*) ; 
 int /*<<< orphan*/  M_LAGG ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct lagg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_lagg_list ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct lagg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lagg_port_destroy (struct lagg_port*,int) ; 
 int /*<<< orphan*/  lagg_proto_detach (struct lagg_softc*) ; 
 int /*<<< orphan*/  lagg_softc ; 
 int /*<<< orphan*/  lagg_stop (struct lagg_softc*) ; 
 int /*<<< orphan*/  sc_entries ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static void
lagg_clone_destroy(struct ifnet *ifp)
{
	struct lagg_softc *sc = (struct lagg_softc *)ifp->if_softc;
	struct lagg_port *lp;

	LAGG_XLOCK(sc);
	sc->sc_destroying = 1;
	lagg_stop(sc);
	ifp->if_flags &= ~IFF_UP;

	EVENTHANDLER_DEREGISTER(vlan_config, sc->vlan_attach);
	EVENTHANDLER_DEREGISTER(vlan_unconfig, sc->vlan_detach);

	/* Shutdown and remove lagg ports */
	while ((lp = CK_SLIST_FIRST(&sc->sc_ports)) != NULL)
		lagg_port_destroy(lp, 1);

	/* Unhook the aggregation protocol */
	lagg_proto_detach(sc);
	LAGG_XUNLOCK(sc);

	ifmedia_removeall(&sc->sc_media);
	ether_ifdetach(ifp);
	if_free(ifp);

	LAGG_LIST_LOCK();
	SLIST_REMOVE(&V_lagg_list, sc, lagg_softc, sc_entries);
	LAGG_LIST_UNLOCK();

	LAGG_SX_DESTROY(sc);
	free(sc, M_LAGG);
}