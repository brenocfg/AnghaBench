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
struct bfe_softc {int /*<<< orphan*/  bfe_stat_co; int /*<<< orphan*/  bfe_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK_ASSERT (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_stats_update (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_watchdog (struct bfe_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct bfe_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
bfe_tick(void *xsc)
{
	struct bfe_softc *sc = xsc;
	struct mii_data *mii;

	BFE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->bfe_miibus);
	mii_tick(mii);
	bfe_stats_update(sc);
	bfe_watchdog(sc);
	callout_reset(&sc->bfe_stat_co, hz, bfe_tick, sc);
}