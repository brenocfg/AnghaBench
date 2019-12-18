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
struct ifnet {struct emac_softc* if_softc; } ;
struct emac_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_LOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  EMAC_UNLOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  emac_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
emac_start(struct ifnet *ifp)
{
	struct emac_softc *sc;

	sc = ifp->if_softc;
	EMAC_LOCK(sc);
	emac_start_locked(ifp);
	EMAC_UNLOCK(sc);
}