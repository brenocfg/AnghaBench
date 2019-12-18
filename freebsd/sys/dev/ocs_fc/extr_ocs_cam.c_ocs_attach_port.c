#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  sim_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  devq; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_10__ {int /*<<< orphan*/  ltask; int /*<<< orphan*/  ldt; struct cam_path* path; struct cam_sim* sim; TYPE_1__* ocs; } ;
typedef  TYPE_2__ ocs_fcport ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* FCPORT (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OCS_SCSI_MAX_IOS ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_action ; 
 int /*<<< orphan*/  ocs_ldt_task ; 
 int /*<<< orphan*/  ocs_poll ; 
 int /*<<< orphan*/  ocs_scsi_get_property (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_attach_port(ocs_t *ocs, int chan)
{

	struct cam_sim	*sim = NULL;
	struct cam_path	*path = NULL;
	uint32_t	max_io = ocs_scsi_get_property(ocs, OCS_SCSI_MAX_IOS);
	ocs_fcport *fcp = FCPORT(ocs, chan);

	if (NULL == (sim = cam_sim_alloc(ocs_action, ocs_poll, 
				device_get_name(ocs->dev), ocs, 
				device_get_unit(ocs->dev), &ocs->sim_lock,
				max_io, max_io, ocs->devq))) {
		device_printf(ocs->dev, "Can't allocate SIM\n");
		return 1;
	}

	mtx_lock(&ocs->sim_lock);
	if (CAM_SUCCESS != xpt_bus_register(sim, ocs->dev, chan)) {
		device_printf(ocs->dev, "Can't register bus %d\n", 0);
		mtx_unlock(&ocs->sim_lock);
		cam_sim_free(sim, FALSE);
		return 1;
	}
	mtx_unlock(&ocs->sim_lock);

	if (CAM_REQ_CMP != xpt_create_path(&path, NULL, cam_sim_path(sim),
				CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD)) {
		device_printf(ocs->dev, "Can't create path\n");
		xpt_bus_deregister(cam_sim_path(sim));
		mtx_unlock(&ocs->sim_lock);
		cam_sim_free(sim, FALSE);
		return 1;
	}
	
	fcp->ocs = ocs;
	fcp->sim  = sim;
	fcp->path = path;

	callout_init_mtx(&fcp->ldt, &ocs->sim_lock, 0);
	TASK_INIT(&fcp->ltask, 1, ocs_ldt_task, fcp);

	return 0;
}