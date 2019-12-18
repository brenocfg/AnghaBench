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
struct alc_softc {int /*<<< orphan*/  alc_tick_ch; int /*<<< orphan*/  alc_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_LOCK_ASSERT (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_stats_update (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_txeof (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_watchdog (struct alc_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct alc_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
alc_tick(void *arg)
{
	struct alc_softc *sc;
	struct mii_data *mii;

	sc = (struct alc_softc *)arg;

	ALC_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->alc_miibus);
	mii_tick(mii);
	alc_stats_update(sc);
	/*
	 * alc(4) does not rely on Tx completion interrupts to reclaim
	 * transferred buffers. Instead Tx completion interrupts are
	 * used to hint for scheduling Tx task. So it's necessary to
	 * release transmitted buffers by kicking Tx completion
	 * handler. This limits the maximum reclamation delay to a hz.
	 */
	alc_txeof(sc);
	alc_watchdog(sc);
	callout_reset(&sc->alc_tick_ch, hz, alc_tick, sc);
}