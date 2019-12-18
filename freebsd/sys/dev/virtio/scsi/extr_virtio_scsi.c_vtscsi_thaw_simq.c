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
struct vtscsi_softc {int vtscsi_frozen; } ;

/* Variables and functions */
 int VTSCSI_FROZEN_NO_REQUESTS ; 
 int VTSCSI_FROZEN_REQUEST_VQ_FULL ; 
 int /*<<< orphan*/  VTSCSI_INFO ; 
 int VTSCSI_REQUEST ; 
 int VTSCSI_REQUEST_VQ ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
vtscsi_thaw_simq(struct vtscsi_softc *sc, int reason)
{
	int thawed;

	if (sc->vtscsi_frozen == 0 || reason == 0)
		return (0);

	if (reason & VTSCSI_REQUEST &&
	    sc->vtscsi_frozen & VTSCSI_FROZEN_NO_REQUESTS)
		sc->vtscsi_frozen &= ~VTSCSI_FROZEN_NO_REQUESTS;

	if (reason & VTSCSI_REQUEST_VQ &&
	    sc->vtscsi_frozen & VTSCSI_FROZEN_REQUEST_VQ_FULL)
		sc->vtscsi_frozen &= ~VTSCSI_FROZEN_REQUEST_VQ_FULL;

	thawed = sc->vtscsi_frozen == 0;
	if (thawed != 0)
		vtscsi_dprintf(sc, VTSCSI_INFO, "SIMQ thawed\n");

	return (thawed);
}