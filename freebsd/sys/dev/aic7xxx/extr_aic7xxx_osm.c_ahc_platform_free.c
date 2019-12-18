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
struct ahc_softc {struct ahc_platform_data* platform_data; int /*<<< orphan*/  dev_softc; } ;
struct ahc_platform_data {int /*<<< orphan*/ * eh; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/ * sim_b; int /*<<< orphan*/  path_b; int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_res_type; int /*<<< orphan*/ * regs; int /*<<< orphan*/  regs_res_id; int /*<<< orphan*/  regs_res_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ahc_platform_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

void
ahc_platform_free(struct ahc_softc *ahc)
{
	struct ahc_platform_data *pdata;

	pdata = ahc->platform_data;
	if (pdata != NULL) {
		if (pdata->regs != NULL)
			bus_release_resource(ahc->dev_softc,
					     pdata->regs_res_type,
					     pdata->regs_res_id,
					     pdata->regs);

		if (pdata->irq != NULL)
			bus_release_resource(ahc->dev_softc,
					     pdata->irq_res_type,
					     0, pdata->irq);

		if (pdata->sim_b != NULL) {
			xpt_async(AC_LOST_DEVICE, pdata->path_b, NULL);
			xpt_free_path(pdata->path_b);
			xpt_bus_deregister(cam_sim_path(pdata->sim_b));
			cam_sim_free(pdata->sim_b, /*free_devq*/TRUE);
		}
		if (pdata->sim != NULL) {
			xpt_async(AC_LOST_DEVICE, pdata->path, NULL);
			xpt_free_path(pdata->path);
			xpt_bus_deregister(cam_sim_path(pdata->sim));
			cam_sim_free(pdata->sim, /*free_devq*/TRUE);
		}
		if (pdata->eh != NULL)
			EVENTHANDLER_DEREGISTER(shutdown_final, pdata->eh);
		free(ahc->platform_data, M_DEVBUF);
	}
}