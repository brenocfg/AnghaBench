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
typedef  union ccb {int dummy; } ccb ;
struct TYPE_3__ {int /*<<< orphan*/  map_lock; void* mtx_init; int /*<<< orphan*/  cam_lock; int /*<<< orphan*/ * devq; int /*<<< orphan*/ * sim; void* sim_registered; int /*<<< orphan*/  path; } ;
struct pqisrc_softstate {TYPE_1__ os_specific; } ;
struct TYPE_4__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {struct pqisrc_softstate* callback_arg; int /*<<< orphan*/  callback; scalar_t__ event_enable; TYPE_2__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smartpqi_async ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void deregister_sim(struct pqisrc_softstate *softs)
{
	struct ccb_setasync csa;
	
	DBG_FUNC("IN\n");

	if (softs->os_specific.mtx_init) {
		mtx_lock(&softs->os_specific.cam_lock);
	}


	xpt_setup_ccb(&csa.ccb_h, softs->os_specific.path, 5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = 0;
	csa.callback = smartpqi_async;
	csa.callback_arg = softs;
	xpt_action((union ccb *)&csa);
	xpt_free_path(softs->os_specific.path);

	xpt_release_simq(softs->os_specific.sim, 0);

	xpt_bus_deregister(cam_sim_path(softs->os_specific.sim));
	softs->os_specific.sim_registered = FALSE;

	if (softs->os_specific.sim) {
		cam_sim_free(softs->os_specific.sim, FALSE);
		softs->os_specific.sim = NULL;
	}
	if (softs->os_specific.mtx_init) {
		mtx_unlock(&softs->os_specific.cam_lock);
	}
	if (softs->os_specific.devq != NULL) {
		cam_simq_free(softs->os_specific.devq);
	}
	if (softs->os_specific.mtx_init) {
		mtx_destroy(&softs->os_specific.cam_lock);
		softs->os_specific.mtx_init = FALSE;
	}

	mtx_destroy(&softs->os_specific.map_lock);

	DBG_FUNC("OUT\n");
}