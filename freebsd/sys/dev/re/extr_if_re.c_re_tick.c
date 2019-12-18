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
struct rl_softc {int rl_flags; int /*<<< orphan*/  rl_stat_callout; int /*<<< orphan*/  rl_dev; int /*<<< orphan*/  rl_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int RL_FLAG_LINK ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct rl_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  re_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_txeof (struct rl_softc*) ; 
 int /*<<< orphan*/  re_watchdog (struct rl_softc*) ; 

__attribute__((used)) static void
re_tick(void *xsc)
{
	struct rl_softc		*sc;
	struct mii_data		*mii;

	sc = xsc;

	RL_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->rl_miibus);
	mii_tick(mii);
	if ((sc->rl_flags & RL_FLAG_LINK) == 0)
		re_miibus_statchg(sc->rl_dev);
	/*
	 * Reclaim transmitted frames here. Technically it is not
	 * necessary to do here but it ensures periodic reclamation
	 * regardless of Tx completion interrupt which seems to be
	 * lost on PCIe based controllers under certain situations.
	 */
	re_txeof(sc);
	re_watchdog(sc);
	callout_reset(&sc->rl_stat_callout, hz, re_tick, sc);
}