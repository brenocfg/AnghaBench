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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ pmf; } ;
struct bxe_softc {int /*<<< orphan*/  sp_err_timeout_task; int /*<<< orphan*/  ifp; int /*<<< orphan*/  stats_pending; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_ERR_STATS_TO ; 
 int /*<<< orphan*/  BXE_SET_ERROR_BIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ DMAE_COMP_VAL ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ IS_PF (struct bxe_softc*) ; 
 scalar_t__ IS_VF (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_drv_stats_update (struct bxe_softc*) ; 
 scalar_t__ bxe_edebug_stats_stopped (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_hw_stats_post (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_hw_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_net_stats_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_storm_stats_post (struct bxe_softc*) ; 
 scalar_t__ bxe_storm_stats_update (struct bxe_softc*) ; 
 int hz ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 scalar_t__* stats_comp ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
bxe_stats_update(struct bxe_softc *sc)
{
    uint32_t *stats_comp = BXE_SP(sc, stats_comp);

    if (bxe_edebug_stats_stopped(sc)) {
        return;
    }

    if (IS_PF(sc)) {
        if (*stats_comp != DMAE_COMP_VAL) {
            return;
        }

        if (sc->port.pmf) {
            bxe_hw_stats_update(sc);
        }

        if (bxe_storm_stats_update(sc)) {
            if (sc->stats_pending++ == 3) {
		if (if_getdrvflags(sc->ifp) & IFF_DRV_RUNNING) {
		    BLOGE(sc, "Storm stats not updated for 3 times, resetting\n");
		    BXE_SET_ERROR_BIT(sc, BXE_ERR_STATS_TO);
		    taskqueue_enqueue_timeout(taskqueue_thread,
                            &sc->sp_err_timeout_task, hz/10);
		}
            }
            return;
        }
    } else {
        /*
         * VF doesn't collect HW statistics, and doesn't get completions,
         * performs only update.
         */
        bxe_storm_stats_update(sc);
    }

    bxe_net_stats_update(sc);
    bxe_drv_stats_update(sc);

    /* vf is done */
    if (IS_VF(sc)) {
        return;
    }

    bxe_hw_stats_post(sc);
    bxe_storm_stats_post(sc);
}