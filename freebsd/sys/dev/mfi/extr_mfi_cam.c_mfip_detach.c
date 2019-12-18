#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mfip_softc {scalar_t__ state; int /*<<< orphan*/ * devq; TYPE_1__* mfi_sc; int /*<<< orphan*/ * sim; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/ * mfi_cam_rescan_cb; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MFIP_STATE_DETACH ; 
 scalar_t__ MFIP_STATE_RESCAN ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 struct mfip_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mfip_detach(device_t dev)
{
	struct mfip_softc *sc;

	sc = device_get_softc(dev);
	if (sc == NULL)
		return (EINVAL);

	mtx_lock(&sc->mfi_sc->mfi_io_lock);
	if (sc->state == MFIP_STATE_RESCAN) {
		mtx_unlock(&sc->mfi_sc->mfi_io_lock);
		return (EBUSY);
	}
	sc->state = MFIP_STATE_DETACH;
	mtx_unlock(&sc->mfi_sc->mfi_io_lock);

	sc->mfi_sc->mfi_cam_rescan_cb = NULL;

	if (sc->sim != NULL) {
		mtx_lock(&sc->mfi_sc->mfi_io_lock);
		xpt_bus_deregister(cam_sim_path(sc->sim));
		cam_sim_free(sc->sim, FALSE);
		sc->sim = NULL;
		mtx_unlock(&sc->mfi_sc->mfi_io_lock);
	}

	if (sc->devq != NULL) {
		cam_simq_free(sc->devq);
		sc->devq = NULL;
	}

	return (0);
}