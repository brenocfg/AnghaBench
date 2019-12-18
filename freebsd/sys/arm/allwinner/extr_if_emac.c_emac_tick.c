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
struct emac_softc {int /*<<< orphan*/  emac_tick_ch; int /*<<< orphan*/  emac_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct emac_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_watchdog (struct emac_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
emac_tick(void *arg)
{
	struct emac_softc *sc;
	struct mii_data *mii;

	sc = (struct emac_softc *)arg;
	mii = device_get_softc(sc->emac_miibus);
	mii_tick(mii);

	emac_watchdog(sc);
	callout_reset(&sc->emac_tick_ch, hz, emac_tick, sc);
}