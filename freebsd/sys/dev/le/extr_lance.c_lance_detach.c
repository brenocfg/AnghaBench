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
struct lance_softc {int /*<<< orphan*/  sc_wdog_ch; struct ifnet* sc_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_LOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_UNLOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  lance_stop (struct lance_softc*) ; 

void
lance_detach(struct lance_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	LE_LOCK(sc);
	lance_stop(sc);
	LE_UNLOCK(sc);
	callout_drain(&sc->sc_wdog_ch);
	ether_ifdetach(ifp);
	if_free(ifp);
}