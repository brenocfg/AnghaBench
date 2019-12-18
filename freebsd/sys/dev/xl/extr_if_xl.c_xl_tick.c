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
struct xl_softc {int /*<<< orphan*/  xl_tick_callout; int /*<<< orphan*/ * xl_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ EJUSTRETURN ; 
 int /*<<< orphan*/  XL_LOCK_ASSERT (struct xl_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct xl_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  xl_stats_update (struct xl_softc*) ; 
 scalar_t__ xl_watchdog (struct xl_softc*) ; 

__attribute__((used)) static void
xl_tick(void *xsc)
{
	struct xl_softc *sc = xsc;
	struct mii_data *mii;

	XL_LOCK_ASSERT(sc);

	if (sc->xl_miibus != NULL) {
		mii = device_get_softc(sc->xl_miibus);
		mii_tick(mii);
	}

	xl_stats_update(sc);
	if (xl_watchdog(sc) == EJUSTRETURN)
		return;

	callout_reset(&sc->xl_tick_callout, hz, xl_tick, sc);
}