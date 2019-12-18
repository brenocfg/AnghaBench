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
struct vtscsi_softc {int vtscsi_frozen; int /*<<< orphan*/  vtscsi_sim; } ;

/* Variables and functions */
 int VTSCSI_FROZEN_NO_REQUESTS ; 
 int VTSCSI_FROZEN_REQUEST_VQ_FULL ; 
 int /*<<< orphan*/  VTSCSI_INFO ; 
 int VTSCSI_REQUEST ; 
 int VTSCSI_REQUEST_VQ ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vtscsi_freeze_simq(struct vtscsi_softc *sc, int reason)
{
	int frozen;

	frozen = sc->vtscsi_frozen;

	if (reason & VTSCSI_REQUEST &&
	    (sc->vtscsi_frozen & VTSCSI_FROZEN_NO_REQUESTS) == 0)
		sc->vtscsi_frozen |= VTSCSI_FROZEN_NO_REQUESTS;

	if (reason & VTSCSI_REQUEST_VQ &&
	    (sc->vtscsi_frozen & VTSCSI_FROZEN_REQUEST_VQ_FULL) == 0)
		sc->vtscsi_frozen |= VTSCSI_FROZEN_REQUEST_VQ_FULL;

	/* Freeze the SIMQ if transitioned to frozen. */
	if (frozen == 0 && sc->vtscsi_frozen != 0) {
		vtscsi_dprintf(sc, VTSCSI_INFO, "SIMQ frozen\n");
		xpt_freeze_simq(sc->vtscsi_sim, 1);
	}
}