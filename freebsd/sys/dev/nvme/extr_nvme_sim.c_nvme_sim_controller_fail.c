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
struct nvme_sim_softc {int /*<<< orphan*/  s_sim; int /*<<< orphan*/  s_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  M_NVME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nvme_sim_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_sim_controller_fail(void *ctrlr_arg)
{
	struct nvme_sim_softc *sc = ctrlr_arg;

	xpt_async(AC_LOST_DEVICE, sc->s_path, NULL);
	xpt_free_path(sc->s_path);
	xpt_bus_deregister(cam_sim_path(sc->s_sim));
	cam_sim_free(sc->s_sim, /*free_devq*/TRUE);
	free(sc, M_NVME);
}