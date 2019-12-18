#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct TYPE_5__ {int /*<<< orphan*/  cam_lock; int /*<<< orphan*/  path; struct cam_sim* sim; int /*<<< orphan*/  sim_registered; int /*<<< orphan*/ * devq; int /*<<< orphan*/  pqi_dev; } ;
struct pqisrc_softstate {int max_io_for_scsi_ml; TYPE_2__ os_specific; } ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {TYPE_3__ ccb_h; struct pqisrc_softstate* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  event_enable; } ;
struct cam_sim {int dummy; } ;
typedef  int cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  AC_FOUND_DEVICE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_INFO (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int PQI_STATUS_FAILURE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pqisrc_softstate*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 int /*<<< orphan*/ * cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smartpqi_async ; 
 int /*<<< orphan*/  smartpqi_cam_action ; 
 int /*<<< orphan*/  smartpqi_poll ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int register_sim(struct pqisrc_softstate *softs, int card_index)
{
	int error = 0;
	int max_transactions;
	union ccb   *ccb = NULL;
	cam_status status = 0;
	struct ccb_setasync csa;
	struct cam_sim *sim;

	DBG_FUNC("IN\n");

	max_transactions = softs->max_io_for_scsi_ml;
	softs->os_specific.devq = cam_simq_alloc(max_transactions);
	if (softs->os_specific.devq == NULL) {
		DBG_ERR("cam_simq_alloc failed txns = %d\n",
			max_transactions);
		return PQI_STATUS_FAILURE;
	}

	sim = cam_sim_alloc(smartpqi_cam_action, \
				smartpqi_poll, "smartpqi", softs, \
				card_index, &softs->os_specific.cam_lock, \
				1, max_transactions, softs->os_specific.devq);
	if (sim == NULL) {
		DBG_ERR("cam_sim_alloc failed txns = %d\n",
			max_transactions);
		cam_simq_free(softs->os_specific.devq);
		return PQI_STATUS_FAILURE;
	}

	softs->os_specific.sim = sim;
	mtx_lock(&softs->os_specific.cam_lock);
	status = xpt_bus_register(sim, softs->os_specific.pqi_dev, 0);
	if (status != CAM_SUCCESS) {
		DBG_ERR("xpt_bus_register failed status=%d\n", status);
		cam_sim_free(softs->os_specific.sim, FALSE);
		cam_simq_free(softs->os_specific.devq);
		mtx_unlock(&softs->os_specific.cam_lock);
		return PQI_STATUS_FAILURE;
	}

	softs->os_specific.sim_registered = TRUE;
	ccb = xpt_alloc_ccb_nowait();
	if (ccb == NULL) {
		DBG_ERR("xpt_create_path failed\n");
		return PQI_STATUS_FAILURE;
	}

	if (xpt_create_path(&ccb->ccb_h.path, NULL,
			cam_sim_path(softs->os_specific.sim),
			CAM_TARGET_WILDCARD,
			CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		DBG_ERR("xpt_create_path failed\n");
		xpt_free_ccb(ccb);
		xpt_bus_deregister(cam_sim_path(softs->os_specific.sim));
		cam_sim_free(softs->os_specific.sim, TRUE);
		mtx_unlock(&softs->os_specific.cam_lock);
		return PQI_STATUS_FAILURE;
	}
	/*
 	 * Callback to set the queue depth per target which is 
	 * derived from the FW.
 	 */
	softs->os_specific.path = ccb->ccb_h.path;
	xpt_setup_ccb(&csa.ccb_h, softs->os_specific.path, 5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = AC_FOUND_DEVICE;
	csa.callback = smartpqi_async;
	csa.callback_arg = softs;
	xpt_action((union ccb *)&csa);
	if (csa.ccb_h.status != CAM_REQ_CMP) {
		DBG_ERR("Unable to register smartpqi_aysnc handler: %d!\n", 
			csa.ccb_h.status);
	}

	mtx_unlock(&softs->os_specific.cam_lock);
	DBG_INFO("OUT\n");
	return error;
}