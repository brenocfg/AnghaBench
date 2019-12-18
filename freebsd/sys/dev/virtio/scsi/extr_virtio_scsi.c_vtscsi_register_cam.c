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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_sim; int /*<<< orphan*/ * vtscsi_path; int /*<<< orphan*/  vtscsi_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vtscsi_register_async (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vtscsi_register_cam(struct vtscsi_softc *sc)
{
	device_t dev;
	int registered, error;

	dev = sc->vtscsi_dev;
	registered = 0;

	VTSCSI_LOCK(sc);

	if (xpt_bus_register(sc->vtscsi_sim, dev, 0) != CAM_SUCCESS) {
		error = ENOMEM;
		device_printf(dev, "cannot register XPT bus\n");
		goto fail;
	}

	registered = 1;

	if (xpt_create_path(&sc->vtscsi_path, NULL,
	    cam_sim_path(sc->vtscsi_sim), CAM_TARGET_WILDCARD,
	    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		error = ENOMEM;
		device_printf(dev, "cannot create bus path\n");
		goto fail;
	}

	if (vtscsi_register_async(sc) != CAM_REQ_CMP) {
		error = EIO;
		device_printf(dev, "cannot register async callback\n");
		goto fail;
	}

	VTSCSI_UNLOCK(sc);

	return (0);

fail:
	if (sc->vtscsi_path != NULL) {
		xpt_free_path(sc->vtscsi_path);
		sc->vtscsi_path = NULL;
	}

	if (registered != 0)
		xpt_bus_deregister(cam_sim_path(sc->vtscsi_sim));

	VTSCSI_UNLOCK(sc);

	return (error);
}