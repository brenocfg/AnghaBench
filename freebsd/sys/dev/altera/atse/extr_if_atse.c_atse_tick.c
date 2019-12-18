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
struct atse_softc {int atse_flags; int /*<<< orphan*/  atse_tick; int /*<<< orphan*/  atse_dev; int /*<<< orphan*/  atse_miibus; struct ifnet* atse_ifp; } ;

/* Variables and functions */
 int ATSE_FLAGS_LINK ; 
 int /*<<< orphan*/  ATSE_LOCK_ASSERT (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct atse_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
atse_tick(void *xsc)
{
	struct atse_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;

	sc = (struct atse_softc *)xsc;
	ATSE_LOCK_ASSERT(sc);
	ifp = sc->atse_ifp;

	mii = device_get_softc(sc->atse_miibus);
	mii_tick(mii);
	if ((sc->atse_flags & ATSE_FLAGS_LINK) == 0) {
		atse_miibus_statchg(sc->atse_dev);
	}

	callout_reset(&sc->atse_tick, hz, atse_tick, sc);
}