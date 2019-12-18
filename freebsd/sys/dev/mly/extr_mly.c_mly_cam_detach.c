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
struct mly_softc {int mly_cam_channels; int /*<<< orphan*/ * mly_cam_devq; int /*<<< orphan*/ ** mly_cam_sim; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLY_LOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  MLY_UNLOCK (struct mly_softc*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mly_cam_detach(struct mly_softc *sc)
{
    int		i;
    
    debug_called(1);

    MLY_LOCK(sc);
    for (i = 0; i < sc->mly_cam_channels; i++) {
	if (sc->mly_cam_sim[i] != NULL) {
	    xpt_bus_deregister(cam_sim_path(sc->mly_cam_sim[i]));
	    cam_sim_free(sc->mly_cam_sim[i], 0);
	}
    }
    MLY_UNLOCK(sc);
    if (sc->mly_cam_devq != NULL)
	cam_simq_free(sc->mly_cam_devq);
}