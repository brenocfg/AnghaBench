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
struct mmcnull_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  tick; int /*<<< orphan*/ * devq; int /*<<< orphan*/ * sim; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  sim_action_func ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mmcnull_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (int /*<<< orphan*/ *) ; 
 struct mmcnull_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_sdio_mode ; 
 int /*<<< orphan*/  mmcnull_action_sd ; 
 int /*<<< orphan*/  mmcnull_action_sdio ; 
 int /*<<< orphan*/  mmcnull_poll ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmcnull_attach(device_t dev)
{
	struct mmcnull_softc *sc;
	sim_action_func action_func;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->sc_mtx, "mmcnullmtx", NULL, MTX_DEF);

	if ((sc->devq = cam_simq_alloc(1)) == NULL)
		return (ENOMEM);

	if (is_sdio_mode)
		action_func = mmcnull_action_sdio;
	else
		action_func = mmcnull_action_sd;
	sc->sim = cam_sim_alloc(action_func, mmcnull_poll, "mmcnull", sc,
				device_get_unit(dev), &sc->sc_mtx, 1, 1,
				sc->devq);

	if (sc->sim == NULL) {
		cam_simq_free(sc->devq);
		device_printf(dev, "cannot allocate CAM SIM\n");
		return (EINVAL);
	}

	mtx_lock(&sc->sc_mtx);
	if (xpt_bus_register(sc->sim, dev, 0) != 0) {
		device_printf(dev,
			      "cannot register SCSI pass-through bus\n");
		cam_sim_free(sc->sim, FALSE);
		cam_simq_free(sc->devq);
		mtx_unlock(&sc->sc_mtx);
		return (EINVAL);
	}
	mtx_unlock(&sc->sc_mtx);

	callout_init_mtx(&sc->tick, &sc->sc_mtx, 0);	/* Callout to emulate interrupts */

	device_printf(dev, "attached OK\n");

	return (0);
}