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
struct mmcnull_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  sim; int /*<<< orphan*/  sc_mtx; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_UNIT_ATTENTION ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 

__attribute__((used)) static void
mmcnull_intr_sdio_newintr(void *xsc) {
	struct mmcnull_softc *sc;
	struct cam_path *dpath;

	sc = (struct mmcnull_softc *) xsc;
	mtx_assert(&sc->sc_mtx, MA_OWNED);
	device_printf(sc->dev, "mmcnull_intr_sdio_newintr()\n");

	/* Our path */
	if (xpt_create_path(&dpath, NULL, cam_sim_path(sc->sim), 0, 0) != CAM_REQ_CMP) {
		device_printf(sc->dev, "mmcnull_intr_sdio_newintr(): cannot create path\n");
		return;
	}
	xpt_async(AC_UNIT_ATTENTION, dpath, NULL);
	xpt_free_path(dpath);
}