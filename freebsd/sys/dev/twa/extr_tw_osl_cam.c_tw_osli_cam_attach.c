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
struct twa_softc {int /*<<< orphan*/  sim_lock; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/  bus_dev; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  TW_OSLI_MAX_NUM_IOS ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct twa_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twa_action ; 
 int /*<<< orphan*/  twa_poll ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TW_INT32
tw_osli_cam_attach(struct twa_softc *sc)
{
	struct cam_devq		*devq;

	tw_osli_dbg_dprintf(3, sc, "entered");

	/*
	 * Create the device queue for our SIM.
	 */
	if ((devq = cam_simq_alloc(TW_OSLI_MAX_NUM_IOS)) == NULL) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2100,
			"Failed to create SIM device queue",
			ENOMEM);
		return(ENOMEM);
	}

	/*
	 * Create a SIM entry.  Though we can support TW_OSLI_MAX_NUM_REQUESTS
	 * simultaneous requests, we claim to be able to handle only
	 * TW_OSLI_MAX_NUM_IOS (two less), so that we always have a request
	 * packet available to service ioctls and AENs.
	 */
	tw_osli_dbg_dprintf(3, sc, "Calling cam_sim_alloc");
	sc->sim = cam_sim_alloc(twa_action, twa_poll, "twa", sc,
			device_get_unit(sc->bus_dev), sc->sim_lock,
			TW_OSLI_MAX_NUM_IOS, 1, devq);
	if (sc->sim == NULL) {
		cam_simq_free(devq);
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2101,
			"Failed to create a SIM entry",
			ENOMEM);
		return(ENOMEM);
	}

	/*
	 * Register the bus.
	 */
	tw_osli_dbg_dprintf(3, sc, "Calling xpt_bus_register");
	mtx_lock(sc->sim_lock);
	if (xpt_bus_register(sc->sim, sc->bus_dev, 0) != CAM_SUCCESS) {
		cam_sim_free(sc->sim, TRUE);
		sc->sim = NULL; /* so cam_detach will not try to free it */
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2102,
			"Failed to register the bus",
			ENXIO);
		mtx_unlock(sc->sim_lock);
		return(ENXIO);
	}

	tw_osli_dbg_dprintf(3, sc, "Calling xpt_create_path");
	if (xpt_create_path(&sc->path, NULL,
				cam_sim_path(sc->sim),
				CAM_TARGET_WILDCARD,
				CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_bus_deregister(cam_sim_path (sc->sim));
		/* Passing TRUE to cam_sim_free will free the devq as well. */
		cam_sim_free(sc->sim, TRUE);
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2103,
			"Failed to create path",
			ENXIO);
		mtx_unlock(sc->sim_lock);
		return(ENXIO);
	}
	mtx_unlock(sc->sim_lock);

	tw_osli_dbg_dprintf(3, sc, "exiting");
	return(0);
}