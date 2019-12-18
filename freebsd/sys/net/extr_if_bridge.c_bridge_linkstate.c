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
struct ifnet {struct bridge_softc* if_bridge; } ;
struct bridge_softc {int dummy; } ;
struct bridge_iflist {int /*<<< orphan*/  bif_stp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  BRIDGE_UNLOCK (struct bridge_softc*) ; 
 int /*<<< orphan*/  bridge_linkcheck (struct bridge_softc*) ; 
 struct bridge_iflist* bridge_lookup_member_if (struct bridge_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  bstp_linkstate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bridge_linkstate(struct ifnet *ifp)
{
	struct bridge_softc *sc = ifp->if_bridge;
	struct bridge_iflist *bif;

	BRIDGE_LOCK(sc);
	bif = bridge_lookup_member_if(sc, ifp);
	if (bif == NULL) {
		BRIDGE_UNLOCK(sc);
		return;
	}
	bridge_linkcheck(sc);
	BRIDGE_UNLOCK(sc);

	bstp_linkstate(&bif->bif_stp);
}