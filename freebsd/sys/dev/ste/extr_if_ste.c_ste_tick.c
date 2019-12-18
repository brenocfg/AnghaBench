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
struct ste_softc {int ste_flags; int /*<<< orphan*/  ste_callout; int /*<<< orphan*/  ste_dev; int /*<<< orphan*/  ste_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int STE_FLAG_LINK ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ste_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  ste_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ste_stats_update (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_txeoc (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_txeof (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_watchdog (struct ste_softc*) ; 

__attribute__((used)) static void
ste_tick(void *arg)
{
	struct ste_softc *sc;
	struct mii_data *mii;

	sc = (struct ste_softc *)arg;

	STE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->ste_miibus);
	mii_tick(mii);
	/*
	 * ukphy(4) does not seem to generate CB that reports
	 * resolved link state so if we know we lost a link,
	 * explicitly check the link state.
	 */
	if ((sc->ste_flags & STE_FLAG_LINK) == 0)
		ste_miibus_statchg(sc->ste_dev);
	/*
	 * Because we are not generating Tx completion
	 * interrupt for every frame, reclaim transmitted
	 * buffers here.
	 */
	ste_txeof(sc);
	ste_txeoc(sc);
	ste_stats_update(sc);
	ste_watchdog(sc);
	callout_reset(&sc->ste_callout, hz, ste_tick, sc);
}