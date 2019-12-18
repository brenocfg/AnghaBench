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
struct vte_softc {int /*<<< orphan*/  vte_tick_ch; int /*<<< orphan*/  vte_miibus; } ;
struct mii_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTE_LOCK_ASSERT (struct vte_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct vte_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  vte_stats_update (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_txeof (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_watchdog (struct vte_softc*) ; 

__attribute__((used)) static void
vte_tick(void *arg)
{
	struct vte_softc *sc;
	struct mii_data *mii;

	sc = (struct vte_softc *)arg;

	VTE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->vte_miibus);
	mii_tick(mii);
	vte_stats_update(sc);
	vte_txeof(sc);
	vte_watchdog(sc);
	callout_reset(&sc->vte_tick_ch, hz, vte_tick, sc);
}