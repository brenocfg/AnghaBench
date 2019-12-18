#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xferlist; } ;
struct TYPE_3__ {int /*<<< orphan*/  fc; int /*<<< orphan*/ * post_busreset; } ;
struct sbp_targ_softc {int /*<<< orphan*/  mtx; TYPE_2__ fwb; TYPE_1__ fd; struct sbp_targ_lstate* black_hole; struct sbp_targ_lstate** lstate; int /*<<< orphan*/  sim; int /*<<< orphan*/  path; } ;
struct sbp_targ_lstate {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MAX_LUN ; 
 int /*<<< orphan*/  M_SBP_TARG ; 
 int /*<<< orphan*/  SBP_LOCK (struct sbp_targ_softc*) ; 
 int /*<<< orphan*/  SBP_UNLOCK (struct sbp_targ_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sbp_targ_lstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_bindremove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fw_xferlist_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbp_targ_detach(device_t dev)
{
	struct sbp_targ_softc *sc;
	struct sbp_targ_lstate *lstate;
	int i;

	sc = (struct sbp_targ_softc *)device_get_softc(dev);
	sc->fd.post_busreset = NULL;

	SBP_LOCK(sc);
	xpt_free_path(sc->path);
	xpt_bus_deregister(cam_sim_path(sc->sim));
	cam_sim_free(sc->sim, /*free_devq*/TRUE);
	SBP_UNLOCK(sc);

	for (i = 0; i < MAX_LUN; i++) {
		lstate = sc->lstate[i];
		if (lstate != NULL) {
			xpt_free_path(lstate->path);
			free(lstate, M_SBP_TARG);
		}
	}
	if (sc->black_hole != NULL) {
		xpt_free_path(sc->black_hole->path);
		free(sc->black_hole, M_SBP_TARG);
	}

	fw_bindremove(sc->fd.fc, &sc->fwb);
	fw_xferlist_remove(&sc->fwb.xferlist);

	mtx_destroy(&sc->mtx);

	return 0;
}