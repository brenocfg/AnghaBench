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
struct age_softc {int /*<<< orphan*/  age_tick_ch; int /*<<< orphan*/  age_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int /*<<< orphan*/  age_watchdog (struct age_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct age_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
age_tick(void *arg)
{
	struct age_softc *sc;
	struct mii_data *mii;

	sc = (struct age_softc *)arg;

	AGE_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->age_miibus);
	mii_tick(mii);
	age_watchdog(sc);
	callout_reset(&sc->age_tick_ch, hz, age_tick, sc);
}