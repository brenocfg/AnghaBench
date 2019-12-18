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
struct vscsi_softc {int /*<<< orphan*/  io_lock; int /*<<< orphan*/ * devq; int /*<<< orphan*/ * sim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 struct vscsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vscsi_detach(device_t dev)
{
	struct vscsi_softc *sc;

	sc = device_get_softc(dev);
	if (sc == NULL)
		return (EINVAL);

	if (sc->sim != NULL) {
		mtx_lock(&sc->io_lock);
		xpt_bus_deregister(cam_sim_path(sc->sim));
		cam_sim_free(sc->sim, FALSE);
		sc->sim = NULL;
		mtx_unlock(&sc->io_lock);
	}

	if (sc->devq != NULL) {
		cam_simq_free(sc->devq);
		sc->devq = NULL;
	}
	
	mtx_destroy(&sc->io_lock);

	return (0);
}