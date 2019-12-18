#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aac_softc {int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/ * cam_rescan_cb; } ;
struct aac_cam {int /*<<< orphan*/  sim; int /*<<< orphan*/  path; TYPE_1__* inf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * aac_cam; struct aac_softc* aac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aac_cam_detach(device_t dev)
{
	struct aac_softc *sc;
	struct aac_cam *camsc;
	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	camsc = (struct aac_cam *)device_get_softc(dev);
	sc = camsc->inf->aac_sc;
	camsc->inf->aac_cam = NULL;

	mtx_lock(&sc->aac_io_lock);

	xpt_async(AC_LOST_DEVICE, camsc->path, NULL);
	xpt_free_path(camsc->path);
	xpt_bus_deregister(cam_sim_path(camsc->sim));
	cam_sim_free(camsc->sim, /*free_devq*/TRUE);

	sc->cam_rescan_cb = NULL;

	mtx_unlock(&sc->aac_io_lock);

	return (0);
}