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
struct jme_softc {int /*<<< orphan*/  jme_tick_ch; int /*<<< orphan*/  jme_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct jme_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  jme_stats_update (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_txeof (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_watchdog (struct jme_softc*) ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
jme_tick(void *arg)
{
	struct jme_softc *sc;
	struct mii_data *mii;

	sc = (struct jme_softc *)arg;

	JME_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->jme_miibus);
	mii_tick(mii);
	/*
	 * Reclaim Tx buffers that have been completed. It's not
	 * needed here but it would release allocated mbuf chains
	 * faster and limit the maximum delay to a hz.
	 */
	jme_txeof(sc);
	jme_stats_update(sc);
	jme_watchdog(sc);
	callout_reset(&sc->jme_tick_ch, hz, jme_tick, sc);
}