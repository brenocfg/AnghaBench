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
struct smc_softc {int /*<<< orphan*/  smc_mii_tick_ch; int /*<<< orphan*/ * smc_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct smc_softc*) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smc_mii_tick(void *context)
{
	struct smc_softc	*sc;

	sc = (struct smc_softc *)context;

	if (sc->smc_miibus == NULL)
		return;

	SMC_UNLOCK(sc);

	mii_tick(device_get_softc(sc->smc_miibus));
	callout_reset(&sc->smc_mii_tick_ch, hz, smc_mii_tick, sc);
}