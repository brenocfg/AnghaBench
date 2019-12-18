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
struct vtscsi_softc {int vtscsi_nrequests; int /*<<< orphan*/ * vtscsi_sim; int /*<<< orphan*/  vtscsi_dev; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VTSCSI_MTX (struct vtscsi_softc*) ; 
 int VTSCSI_RESERVED_REQUESTS ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vtscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct cam_devq*) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vtscsi_cam_action ; 
 int /*<<< orphan*/  vtscsi_cam_poll ; 

__attribute__((used)) static int
vtscsi_alloc_cam(struct vtscsi_softc *sc)
{
	device_t dev;
	struct cam_devq *devq;
	int openings;

	dev = sc->vtscsi_dev;
	openings = sc->vtscsi_nrequests - VTSCSI_RESERVED_REQUESTS;

	devq = cam_simq_alloc(openings);
	if (devq == NULL) {
		device_printf(dev, "cannot allocate SIM queue\n");
		return (ENOMEM);
	}

	sc->vtscsi_sim = cam_sim_alloc(vtscsi_cam_action, vtscsi_cam_poll,
	    "vtscsi", sc, device_get_unit(dev), VTSCSI_MTX(sc), 1,
	    openings, devq);
	if (sc->vtscsi_sim == NULL) {
		cam_simq_free(devq);
		device_printf(dev, "cannot allocate SIM\n");
		return (ENOMEM);
	}

	return (0);
}