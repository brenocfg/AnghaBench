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
struct mrsas_softc {int max_scsi_cmds; int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  sim_lock; int /*<<< orphan*/ * sim_1; int /*<<< orphan*/  path_1; int /*<<< orphan*/ * sim_0; int /*<<< orphan*/  path_0; int /*<<< orphan*/  ev_tq; int /*<<< orphan*/  ev_task; } ;
struct cam_devq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int ENOMEM ; 
 int ENXIO ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,struct mrsas_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mrsas_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrsas_action ; 
 scalar_t__ mrsas_aen_handler ; 
 scalar_t__ mrsas_bus_scan (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_cam_poll ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mrsas_cam_attach(struct mrsas_softc *sc)
{
	struct cam_devq *devq;
	int mrsas_cam_depth;

	mrsas_cam_depth = sc->max_scsi_cmds;

	if ((devq = cam_simq_alloc(mrsas_cam_depth)) == NULL) {
		device_printf(sc->mrsas_dev, "Cannot allocate SIM queue\n");
		return (ENOMEM);
	}
	/*
	 * Create SIM for bus 0 and register, also create path
	 */
	sc->sim_0 = cam_sim_alloc(mrsas_action, mrsas_cam_poll, "mrsas", sc,
	    device_get_unit(sc->mrsas_dev), &sc->sim_lock, mrsas_cam_depth,
	    mrsas_cam_depth, devq);
	if (sc->sim_0 == NULL) {
		cam_simq_free(devq);
		device_printf(sc->mrsas_dev, "Cannot register SIM\n");
		return (ENXIO);
	}
	/* Initialize taskqueue for Event Handling */
	TASK_INIT(&sc->ev_task, 0, (void *)mrsas_aen_handler, sc);
	sc->ev_tq = taskqueue_create("mrsas_taskq", M_NOWAIT | M_ZERO,
	    taskqueue_thread_enqueue, &sc->ev_tq);

	/* Run the task queue with lowest priority */
	taskqueue_start_threads(&sc->ev_tq, 1, 255, "%s taskq",
	    device_get_nameunit(sc->mrsas_dev));
	mtx_lock(&sc->sim_lock);
	if (xpt_bus_register(sc->sim_0, sc->mrsas_dev, 0) != CAM_SUCCESS) {
		cam_sim_free(sc->sim_0, TRUE);	/* passing true frees the devq */
		mtx_unlock(&sc->sim_lock);
		return (ENXIO);
	}
	if (xpt_create_path(&sc->path_0, NULL, cam_sim_path(sc->sim_0),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_bus_deregister(cam_sim_path(sc->sim_0));
		cam_sim_free(sc->sim_0, TRUE);	/* passing true will free the
						 * devq */
		mtx_unlock(&sc->sim_lock);
		return (ENXIO);
	}
	mtx_unlock(&sc->sim_lock);

	/*
	 * Create SIM for bus 1 and register, also create path
	 */
	sc->sim_1 = cam_sim_alloc(mrsas_action, mrsas_cam_poll, "mrsas", sc,
	    device_get_unit(sc->mrsas_dev), &sc->sim_lock, mrsas_cam_depth,
	    mrsas_cam_depth, devq);
	if (sc->sim_1 == NULL) {
		cam_simq_free(devq);
		device_printf(sc->mrsas_dev, "Cannot register SIM\n");
		return (ENXIO);
	}
	mtx_lock(&sc->sim_lock);
	if (xpt_bus_register(sc->sim_1, sc->mrsas_dev, 1) != CAM_SUCCESS) {
		cam_sim_free(sc->sim_1, TRUE);	/* passing true frees the devq */
		mtx_unlock(&sc->sim_lock);
		return (ENXIO);
	}
	if (xpt_create_path(&sc->path_1, NULL, cam_sim_path(sc->sim_1),
	    CAM_TARGET_WILDCARD,
	    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_bus_deregister(cam_sim_path(sc->sim_1));
		cam_sim_free(sc->sim_1, TRUE);
		mtx_unlock(&sc->sim_lock);
		return (ENXIO);
	}
	mtx_unlock(&sc->sim_lock);

#if (__FreeBSD_version <= 704000)
	if (mrsas_bus_scan(sc)) {
		device_printf(sc->mrsas_dev, "Error in bus scan.\n");
		return (1);
	}
#endif
	return (0);
}