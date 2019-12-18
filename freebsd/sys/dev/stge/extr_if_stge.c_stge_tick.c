#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ stge_tx_cnt; } ;
struct stge_softc {int /*<<< orphan*/  sc_tick_ch; TYPE_1__ sc_cdata; int /*<<< orphan*/  sc_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct stge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  stge_stats_update (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_txeof (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_watchdog (struct stge_softc*) ; 

__attribute__((used)) static void
stge_tick(void *arg)
{
	struct stge_softc *sc;
	struct mii_data *mii;

	sc = (struct stge_softc *)arg;

	STGE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->sc_miibus);
	mii_tick(mii);

	/* Update statistics counters. */
	stge_stats_update(sc);

	/*
	 * Relcaim any pending Tx descriptors to release mbufs in a
	 * timely manner as we don't generate Tx completion interrupts
	 * for every frame. This limits the delay to a maximum of one
	 * second.
	 */
	if (sc->sc_cdata.stge_tx_cnt != 0)
		stge_txeof(sc);

	stge_watchdog(sc);

	callout_reset(&sc->sc_tick_ch, hz, stge_tick, sc);
}