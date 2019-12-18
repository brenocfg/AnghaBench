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
struct tws_softc {int /*<<< orphan*/  sim_lock; scalar_t__ sim; scalar_t__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (scalar_t__) ; 

void
tws_cam_detach(struct tws_softc *sc)
{
    TWS_TRACE_DEBUG(sc, "entry", 0, 0);
    mtx_lock(&sc->sim_lock);
    if (sc->path)
        xpt_free_path(sc->path);
    if (sc->sim) {
        xpt_bus_deregister(cam_sim_path(sc->sim));
        cam_sim_free(sc->sim, TRUE);
    }
    mtx_unlock(&sc->sim_lock);
}