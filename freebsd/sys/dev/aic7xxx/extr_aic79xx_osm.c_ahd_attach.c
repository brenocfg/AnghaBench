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
struct TYPE_4__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {struct cam_sim* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  event_enable; TYPE_2__ ccb_h; } ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct cam_devq {int dummy; } ;
struct ahd_softc {TYPE_1__* platform_data; int /*<<< orphan*/  dev_softc; } ;
struct TYPE_3__ {int /*<<< orphan*/  eh; struct cam_path* path; struct cam_sim* sim; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  AHD_MAX_QUEUE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  ahd_action ; 
 int /*<<< orphan*/  ahd_async ; 
 int /*<<< orphan*/  ahd_controller_info (struct ahd_softc*,char*) ; 
 int /*<<< orphan*/  ahd_intr_enable (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_poll ; 
 int /*<<< orphan*/  ahd_shutdown ; 
 scalar_t__ ahd_spawn_recovery_thread (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*) ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,struct cam_path*,int) ; 

int
ahd_attach(struct ahd_softc *ahd)
{
	char   ahd_info[256];
	struct ccb_setasync csa;
	struct cam_devq *devq;
	struct cam_sim *sim;
	struct cam_path *path;
	int count;

	count = 0;
	devq = NULL;
	sim = NULL;
	path = NULL;

	/*
	 * Create a thread to perform all recovery.
	 */
	if (ahd_spawn_recovery_thread(ahd) != 0)
		goto fail;

	ahd_controller_info(ahd, ahd_info);
	printf("%s\n", ahd_info);
	ahd_lock(ahd);

	/*
	 * Create the device queue for our SIM(s).
	 */
	devq = cam_simq_alloc(AHD_MAX_QUEUE);
	if (devq == NULL)
		goto fail;

	/*
	 * Construct our SIM entry
	 */
	sim = cam_sim_alloc(ahd_action, ahd_poll, "ahd", ahd,
			    device_get_unit(ahd->dev_softc),
			    &ahd->platform_data->mtx, 1, /*XXX*/256, devq);
	if (sim == NULL) {
		cam_simq_free(devq);
		goto fail;
	}

	if (xpt_bus_register(sim, ahd->dev_softc, /*bus_id*/0) != CAM_SUCCESS) {
		cam_sim_free(sim, /*free_devq*/TRUE);
		sim = NULL;
		goto fail;
	}
	
	if (xpt_create_path(&path, /*periph*/NULL,
			    cam_sim_path(sim), CAM_TARGET_WILDCARD,
			    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_bus_deregister(cam_sim_path(sim));
		cam_sim_free(sim, /*free_devq*/TRUE);
		sim = NULL;
		goto fail;
	}
		
	xpt_setup_ccb(&csa.ccb_h, path, /*priority*/5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = AC_LOST_DEVICE;
	csa.callback = ahd_async;
	csa.callback_arg = sim;
	xpt_action((union ccb *)&csa);
	count++;

fail:
	ahd->platform_data->sim = sim;
	ahd->platform_data->path = path;
	ahd_unlock(ahd);
	if (count != 0) {
		/* We have to wait until after any system dumps... */
		ahd->platform_data->eh =
		    EVENTHANDLER_REGISTER(shutdown_final, ahd_shutdown,
					  ahd, SHUTDOWN_PRI_DEFAULT);
		ahd_intr_enable(ahd, TRUE);
	}


	return (count);
}