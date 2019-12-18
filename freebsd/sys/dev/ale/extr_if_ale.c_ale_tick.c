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
struct ale_softc {int /*<<< orphan*/  ale_tick_ch; int /*<<< orphan*/  ale_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_LOCK_ASSERT (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_stats_update (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_txeof (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_watchdog (struct ale_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ale_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
ale_tick(void *arg)
{
	struct ale_softc *sc;
	struct mii_data *mii;

	sc = (struct ale_softc *)arg;

	ALE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->ale_miibus);
	mii_tick(mii);
	ale_stats_update(sc);
	/*
	 * Reclaim Tx buffers that have been transferred. It's not
	 * needed here but it would release allocated mbuf chains
	 * faster and limit the maximum delay to a hz.
	 */
	ale_txeof(sc);
	ale_watchdog(sc);
	callout_reset(&sc->ale_tick_ch, hz, ale_tick, sc);
}