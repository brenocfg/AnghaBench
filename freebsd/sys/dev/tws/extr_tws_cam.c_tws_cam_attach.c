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
struct tws_softc {int /*<<< orphan*/  sim_lock; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/  tws_dev; } ;
struct cam_devq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_SIMQ_ALLOC ; 
 int /*<<< orphan*/  CAM_SIM_ALLOC ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  TRUE ; 
 int TWS_RESERVED_REQS ; 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int,...) ; 
 int /*<<< orphan*/  TWS_XPT_BUS_REGISTER ; 
 int /*<<< orphan*/  TWS_XPT_CREATE_PATH ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tws_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tws_action ; 
 int tws_cam_depth ; 
 int /*<<< orphan*/  tws_log (struct tws_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_poll ; 
 int tws_queue_depth ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
tws_cam_attach(struct tws_softc *sc)
{
    struct cam_devq *devq;

    TWS_TRACE_DEBUG(sc, "entry", 0, sc);
    /* Create a device queue for sim */

    /* 
     * if the user sets cam depth to less than 1 
     * cam may get confused 
     */
    if ( tws_cam_depth < 1 )
        tws_cam_depth = 1;
    if ( tws_cam_depth > (tws_queue_depth - TWS_RESERVED_REQS)  )
        tws_cam_depth = tws_queue_depth - TWS_RESERVED_REQS;

    TWS_TRACE_DEBUG(sc, "depths,ctlr,cam", tws_queue_depth, tws_cam_depth);

    if ((devq = cam_simq_alloc(tws_cam_depth)) == NULL) {
        tws_log(sc, CAM_SIMQ_ALLOC);
        return(ENOMEM);
    }

   /*
    * Create a SIM entry.  Though we can support tws_cam_depth
    * simultaneous requests, we claim to be able to handle only
    * (tws_cam_depth), so that we always have reserved  requests
    * packet available to service ioctls and internal commands.
    */
    sc->sim = cam_sim_alloc(tws_action, tws_poll, "tws", sc,
                      device_get_unit(sc->tws_dev), 
                      &sc->sim_lock,
                      tws_cam_depth, 1, devq);
                      /* 1, 1, devq); */
    if (sc->sim == NULL) {
        cam_simq_free(devq);
        tws_log(sc, CAM_SIM_ALLOC);
    }
    /* Register the bus. */
    mtx_lock(&sc->sim_lock);
    if (xpt_bus_register(sc->sim, 
                         sc->tws_dev, 
                         0) != CAM_SUCCESS) {
        cam_sim_free(sc->sim, TRUE); /* passing true will free the devq */
        sc->sim = NULL; /* so cam_detach will not try to free it */
        mtx_unlock(&sc->sim_lock);
        tws_log(sc, TWS_XPT_BUS_REGISTER);
        return(ENXIO);
    }
    if (xpt_create_path(&sc->path, NULL, cam_sim_path(sc->sim),
                         CAM_TARGET_WILDCARD,
                         CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
        xpt_bus_deregister(cam_sim_path(sc->sim));
        /* Passing TRUE to cam_sim_free will free the devq as well. */
        cam_sim_free(sc->sim, TRUE);
        tws_log(sc, TWS_XPT_CREATE_PATH);
        mtx_unlock(&sc->sim_lock);
        return(ENXIO);
    }
    mtx_unlock(&sc->sim_lock);

    return(0);
}