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
struct TYPE_4__ {void* func_code; } ;
struct ccb_setasync {struct cam_sim* callback_arg; void* callback; void* event_enable; TYPE_2__ ccb_h; } ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct cam_devq {int dummy; } ;
struct ahc_softc {int features; int flags; TYPE_1__* platform_data; int /*<<< orphan*/  dev_softc; } ;
struct TYPE_3__ {int /*<<< orphan*/  eh; struct cam_path* path_b; struct cam_sim* sim_b; struct cam_path* path; struct cam_sim* sim; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 void* AC_LOST_DEVICE ; 
 int /*<<< orphan*/  AHC_MAX_QUEUE ; 
 int AHC_PRIMARY_CHANNEL ; 
 int AHC_TWIN ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 void* XPT_SASYNC_CB ; 
 int /*<<< orphan*/  ahc_action ; 
 void* ahc_async ; 
 int /*<<< orphan*/  ahc_controller_info (struct ahc_softc*,char*) ; 
 int /*<<< orphan*/  ahc_intr_enable (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_poll ; 
 int /*<<< orphan*/  ahc_shutdown ; 
 scalar_t__ ahc_spawn_recovery_thread (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*) ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,struct cam_path*,int) ; 

int
ahc_attach(struct ahc_softc *ahc)
{
	char   ahc_info[256];
	struct ccb_setasync csa;
	struct cam_devq *devq;
	int bus_id;
	int bus_id2;
	struct cam_sim *sim;
	struct cam_sim *sim2;
	struct cam_path *path;
	struct cam_path *path2;
	int count;

	count = 0;
	sim = NULL;
	sim2 = NULL;
	path = NULL;
	path2 = NULL;


	/*
	 * Create a thread to perform all recovery.
	 */
	if (ahc_spawn_recovery_thread(ahc) != 0)
		goto fail;

	ahc_controller_info(ahc, ahc_info);
	printf("%s\n", ahc_info);
	ahc_lock(ahc);

	/*
	 * Attach secondary channel first if the user has
	 * declared it the primary channel.
	 */
	if ((ahc->features & AHC_TWIN) != 0
	 && (ahc->flags & AHC_PRIMARY_CHANNEL) != 0) {
		bus_id = 1;
		bus_id2 = 0;
	} else {
		bus_id = 0;
		bus_id2 = 1;
	}

	/*
	 * Create the device queue for our SIM(s).
	 */
	devq = cam_simq_alloc(AHC_MAX_QUEUE);
	if (devq == NULL)
		goto fail;

	/*
	 * Construct our first channel SIM entry
	 */
	sim = cam_sim_alloc(ahc_action, ahc_poll, "ahc", ahc,
			    device_get_unit(ahc->dev_softc),
			    &ahc->platform_data->mtx, 1, AHC_MAX_QUEUE, devq);
	if (sim == NULL) {
		cam_simq_free(devq);
		goto fail;
	}

	if (xpt_bus_register(sim, ahc->dev_softc, bus_id) != CAM_SUCCESS) {
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
	csa.callback = ahc_async;
	csa.callback_arg = sim;
	xpt_action((union ccb *)&csa);
	count++;

	if (ahc->features & AHC_TWIN) {
		sim2 = cam_sim_alloc(ahc_action, ahc_poll, "ahc",
				    ahc, device_get_unit(ahc->dev_softc),
				    &ahc->platform_data->mtx, 1,
				    AHC_MAX_QUEUE, devq);

		if (sim2 == NULL) {
			printf("ahc_attach: Unable to attach second "
			       "bus due to resource shortage");
			goto fail;
		}
		
		if (xpt_bus_register(sim2, ahc->dev_softc, bus_id2) !=
		    CAM_SUCCESS) {
			printf("ahc_attach: Unable to attach second "
			       "bus due to resource shortage");
			/*
			 * We do not want to destroy the device queue
			 * because the first bus is using it.
			 */
			cam_sim_free(sim2, /*free_devq*/FALSE);
			goto fail;
		}

		if (xpt_create_path(&path2, /*periph*/NULL,
				    cam_sim_path(sim2),
				    CAM_TARGET_WILDCARD,
				    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
			xpt_bus_deregister(cam_sim_path(sim2));
			cam_sim_free(sim2, /*free_devq*/FALSE);
			sim2 = NULL;
			goto fail;
		}
		xpt_setup_ccb(&csa.ccb_h, path2, /*priority*/5);
		csa.ccb_h.func_code = XPT_SASYNC_CB;
		csa.event_enable = AC_LOST_DEVICE;
		csa.callback = ahc_async;
		csa.callback_arg = sim2;
		xpt_action((union ccb *)&csa);
		count++;
	}

fail:
	if ((ahc->features & AHC_TWIN) != 0
	 && (ahc->flags & AHC_PRIMARY_CHANNEL) != 0) {
		ahc->platform_data->sim_b = sim;
		ahc->platform_data->path_b = path;
		ahc->platform_data->sim = sim2;
		ahc->platform_data->path = path2;
	} else {
		ahc->platform_data->sim = sim;
		ahc->platform_data->path = path;
		ahc->platform_data->sim_b = sim2;
		ahc->platform_data->path_b = path2;
	}
	ahc_unlock(ahc);

	if (count != 0) {
		/* We have to wait until after any system dumps... */
		ahc->platform_data->eh =
		    EVENTHANDLER_REGISTER(shutdown_final, ahc_shutdown,
					  ahc, SHUTDOWN_PRI_DEFAULT);
		ahc_intr_enable(ahc, TRUE);
	}

	return (count);
}