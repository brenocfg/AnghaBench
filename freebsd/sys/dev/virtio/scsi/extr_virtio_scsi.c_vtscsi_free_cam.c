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
struct vtscsi_softc {int /*<<< orphan*/ * vtscsi_sim; int /*<<< orphan*/ * vtscsi_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtscsi_deregister_async (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtscsi_free_cam(struct vtscsi_softc *sc)
{

	VTSCSI_LOCK(sc);

	if (sc->vtscsi_path != NULL) {
		vtscsi_deregister_async(sc);

		xpt_free_path(sc->vtscsi_path);
		sc->vtscsi_path = NULL;

		xpt_bus_deregister(cam_sim_path(sc->vtscsi_sim));
	}

	if (sc->vtscsi_sim != NULL) {
		cam_sim_free(sc->vtscsi_sim, 1);
		sc->vtscsi_sim = NULL;
	}

	VTSCSI_UNLOCK(sc);
}