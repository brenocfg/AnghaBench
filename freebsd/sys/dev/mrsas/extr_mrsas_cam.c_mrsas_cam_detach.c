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
struct mrsas_softc {int /*<<< orphan*/  sim_lock; scalar_t__ sim_1; scalar_t__ path_1; scalar_t__ sim_0; scalar_t__ path_0; int /*<<< orphan*/ * ev_tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (scalar_t__) ; 

void
mrsas_cam_detach(struct mrsas_softc *sc)
{
	if (sc->ev_tq != NULL)
		taskqueue_free(sc->ev_tq);
	mtx_lock(&sc->sim_lock);
	if (sc->path_0)
		xpt_free_path(sc->path_0);
	if (sc->sim_0) {
		xpt_bus_deregister(cam_sim_path(sc->sim_0));
		cam_sim_free(sc->sim_0, FALSE);
	}
	if (sc->path_1)
		xpt_free_path(sc->path_1);
	if (sc->sim_1) {
		xpt_bus_deregister(cam_sim_path(sc->sim_1));
		cam_sim_free(sc->sim_1, TRUE);
	}
	mtx_unlock(&sc->sim_lock);
}