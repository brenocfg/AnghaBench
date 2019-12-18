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
struct sfxge_softc {scalar_t__ init_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  enp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_UNLOCK (struct sfxge_softc*) ; 
 scalar_t__ SFXGE_STARTED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  efx_nic_reset (int /*<<< orphan*/ ) ; 
 unsigned int sfxge_restart_attempts ; 
 int sfxge_start (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_stop (struct sfxge_softc*) ; 

__attribute__((used)) static void
sfxge_reset(void *arg, int npending)
{
	struct sfxge_softc *sc;
	int rc;
	unsigned attempt;

	(void)npending;

	sc = (struct sfxge_softc *)arg;

	SFXGE_ADAPTER_LOCK(sc);

	if (sc->init_state != SFXGE_STARTED)
		goto done;

	sfxge_stop(sc);
	efx_nic_reset(sc->enp);
	for (attempt = 0; attempt < sfxge_restart_attempts; ++attempt) {
		if ((rc = sfxge_start(sc)) == 0)
			goto done;

		device_printf(sc->dev, "start on reset failed (%d)\n", rc);
		DELAY(100000);
	}

	device_printf(sc->dev, "reset failed; interface is now stopped\n");

done:
	SFXGE_ADAPTER_UNLOCK(sc);
}