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
struct mii_data {int dummy; } ;
struct ifnet {int dummy; } ;
struct et_softc {int /*<<< orphan*/  sc_tick; int /*<<< orphan*/  sc_miibus; struct ifnet* ifp; } ;

/* Variables and functions */
 scalar_t__ EJUSTRETURN ; 
 int /*<<< orphan*/  ET_LOCK_ASSERT (struct et_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct et_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et_stats_update (struct et_softc*) ; 
 scalar_t__ et_watchdog (struct et_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
et_tick(void *xsc)
{
	struct et_softc *sc;
	struct ifnet *ifp;
	struct mii_data *mii;

	sc = xsc;
	ET_LOCK_ASSERT(sc);
	ifp = sc->ifp;
	mii = device_get_softc(sc->sc_miibus);

	mii_tick(mii);
	et_stats_update(sc);
	if (et_watchdog(sc) == EJUSTRETURN)
		return;
	callout_reset(&sc->sc_tick, hz, et_tick, sc);
}