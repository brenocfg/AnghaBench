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
struct msk_if_softc {int msk_flags; int /*<<< orphan*/  msk_tick_ch; int /*<<< orphan*/  msk_softc; int /*<<< orphan*/  msk_if_dev; int /*<<< orphan*/  msk_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int MSK_FLAG_LINK ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct msk_if_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  msk_handle_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msk_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msk_watchdog (struct msk_if_softc*) ; 

__attribute__((used)) static void
msk_tick(void *xsc_if)
{
	struct msk_if_softc *sc_if;
	struct mii_data *mii;

	sc_if = xsc_if;

	MSK_IF_LOCK_ASSERT(sc_if);

	mii = device_get_softc(sc_if->msk_miibus);

	mii_tick(mii);
	if ((sc_if->msk_flags & MSK_FLAG_LINK) == 0)
		msk_miibus_statchg(sc_if->msk_if_dev);
	msk_handle_events(sc_if->msk_softc);
	msk_watchdog(sc_if);
	callout_reset(&sc_if->msk_tick_ch, hz, msk_tick, sc_if);
}