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
struct ifnet {int /*<<< orphan*/  if_flags; struct bridge_softc* if_softc; } ;
struct bridge_softc {int /*<<< orphan*/  sc_stp; int /*<<< orphan*/  sc_brcallout; int /*<<< orphan*/  sc_spanlist; int /*<<< orphan*/  sc_iflist; } ;
struct bridge_iflist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LIST_LOCK () ; 
 int /*<<< orphan*/  BRIDGE_LIST_UNLOCK () ; 
 int /*<<< orphan*/  BRIDGE_LOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  BRIDGE_LOCK_DESTROY (struct bridge_softc*) ; 
 int /*<<< orphan*/  BRIDGE_UNLOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  IFF_UP ; 
 struct bridge_iflist* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bridge_delete_member (struct bridge_softc*,struct bridge_iflist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_delete_span (struct bridge_softc*,struct bridge_iflist*) ; 
 int /*<<< orphan*/  bridge_rtable_fini (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_stop (struct ifnet*,int) ; 
 int /*<<< orphan*/  bstp_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct bridge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  sc_list ; 

__attribute__((used)) static void
bridge_clone_destroy(struct ifnet *ifp)
{
	struct bridge_softc *sc = ifp->if_softc;
	struct bridge_iflist *bif;

	BRIDGE_LOCK(sc);

	bridge_stop(ifp, 1);
	ifp->if_flags &= ~IFF_UP;

	while ((bif = LIST_FIRST(&sc->sc_iflist)) != NULL)
		bridge_delete_member(sc, bif, 0);

	while ((bif = LIST_FIRST(&sc->sc_spanlist)) != NULL) {
		bridge_delete_span(sc, bif);
	}

	/* Tear down the routing table. */
	bridge_rtable_fini(sc);

	BRIDGE_UNLOCK(sc);

	callout_drain(&sc->sc_brcallout);

	BRIDGE_LIST_LOCK();
	LIST_REMOVE(sc, sc_list);
	BRIDGE_LIST_UNLOCK();

	bstp_detach(&sc->sc_stp);
	ether_ifdetach(ifp);
	if_free(ifp);

	BRIDGE_LOCK_DESTROY(sc);
	free(sc, M_DEVBUF);
}