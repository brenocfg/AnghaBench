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
struct nge_softc {int nge_flags; int /*<<< orphan*/  nge_stat_ch; int /*<<< orphan*/  nge_dev; int /*<<< orphan*/  nge_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int NGE_FLAG_LINK ; 
 int /*<<< orphan*/  NGE_LOCK_ASSERT (struct nge_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct nge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  nge_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nge_stats_update (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_watchdog (struct nge_softc*) ; 

__attribute__((used)) static void
nge_tick(void *xsc)
{
	struct nge_softc *sc;
	struct mii_data *mii;

	sc = xsc;
	NGE_LOCK_ASSERT(sc);
	mii = device_get_softc(sc->nge_miibus);
	mii_tick(mii);
	/*
	 * For PHYs that does not reset established link, it is
	 * necessary to check whether driver still have a valid
	 * link(e.g link state change callback is not called).
	 * Otherwise, driver think it lost link because driver
	 * initialization routine clears link state flag.
	 */
	if ((sc->nge_flags & NGE_FLAG_LINK) == 0)
		nge_miibus_statchg(sc->nge_dev);
	nge_stats_update(sc);
	nge_watchdog(sc);
	callout_reset(&sc->nge_stat_ch, hz, nge_tick, sc);
}