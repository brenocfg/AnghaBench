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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct ccb_mmcio {int dummy; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_mmcio mmcio; } ;
struct mmcnull_softc {int /*<<< orphan*/  tick; union ccb* cur_ccb; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_INPROG ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct mmcnull_softc*) ; 
 struct mmcnull_softc* cam_sim_softc (struct cam_sim*) ; 
 int hz ; 
 scalar_t__ is_sdio_mode ; 
 int /*<<< orphan*/  mmcnull_intr_sd ; 
 int /*<<< orphan*/  mmcnull_intr_sdio ; 

__attribute__((used)) static void
mmcnull_handle_mmcio(struct cam_sim *sim, union ccb *ccb)
{
	struct mmcnull_softc *sc;
	struct ccb_mmcio *mmcio;

	sc = cam_sim_softc(sim);
	mmcio = &ccb->mmcio;
	ccb->ccb_h.status = CAM_REQ_INPROG;
	sc->cur_ccb = ccb;

	/* Real h/w will wait for the interrupt */
	if (is_sdio_mode)
		callout_reset(&sc->tick, hz / 10, mmcnull_intr_sdio, sc);
	else
		callout_reset(&sc->tick, hz / 10, mmcnull_intr_sd, sc);
}