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
struct gdt_softc {int sc_bus_cnt; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/ * sims; int /*<<< orphan*/ * paths; int /*<<< orphan*/  sc_devnode; } ;
struct cam_devq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gdt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_INIT ; 
 int /*<<< orphan*/  GDT_MAXCMDS ; 
 int /*<<< orphan*/  GDT_NORMAL ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gdt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iir_action ; 
 int /*<<< orphan*/  iir_poll ; 
 int /*<<< orphan*/  iir_shutdown ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iir_attach(struct gdt_softc *gdt)
{
    struct cam_devq *devq;
    int i;

    GDT_DPRINTF(GDT_D_INIT, ("iir_attach()\n"));

    /*
     * Create the device queue for our SIM.
     * XXX Throttle this down since the card has problems under load.
     */
    devq = cam_simq_alloc(32);
    if (devq == NULL)
        return;

    for (i = 0; i < gdt->sc_bus_cnt; i++) {
        /*
         * Construct our SIM entry
         */
        gdt->sims[i] = cam_sim_alloc(iir_action, iir_poll, "iir",
	    gdt, device_get_unit(gdt->sc_devnode), &gdt->sc_lock,
	    /*untagged*/1, /*tagged*/GDT_MAXCMDS, devq);
	mtx_lock(&gdt->sc_lock);
        if (xpt_bus_register(gdt->sims[i], gdt->sc_devnode, i) != CAM_SUCCESS) {
            cam_sim_free(gdt->sims[i], /*free_devq*/i == 0);
	    mtx_unlock(&gdt->sc_lock);
            break;
        }

        if (xpt_create_path(&gdt->paths[i], /*periph*/NULL,
                            cam_sim_path(gdt->sims[i]),
                            CAM_TARGET_WILDCARD,
                            CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
            xpt_bus_deregister(cam_sim_path(gdt->sims[i]));
            cam_sim_free(gdt->sims[i], /*free_devq*/i == 0);
	    mtx_unlock(&gdt->sc_lock);
            break;
        }
	mtx_unlock(&gdt->sc_lock);
    }
    if (i > 0)
        EVENTHANDLER_REGISTER(shutdown_final, iir_shutdown,
                              gdt, SHUTDOWN_PRI_DEFAULT);
    /* iir_watchdog(gdt); */
    gdt->sc_state = GDT_NORMAL;
}