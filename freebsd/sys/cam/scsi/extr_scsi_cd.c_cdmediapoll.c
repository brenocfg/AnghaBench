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
struct cd_softc {scalar_t__ state; int tur; scalar_t__ outstanding_cmds; int /*<<< orphan*/  mediapoll_c; } ;
struct cam_periph {struct cd_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 scalar_t__ CD_STATE_NORMAL ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cam_periph_acquire (struct cam_periph*) ; 
 int cd_poll_period ; 
 int hz ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cdmediapoll(void *arg)
{
	struct cam_periph *periph = arg;
	struct cd_softc *softc = periph->softc;

	if (softc->state == CD_STATE_NORMAL && !softc->tur &&
	    softc->outstanding_cmds == 0) {
		if (cam_periph_acquire(periph) == 0) {
			softc->tur = 1;
			xpt_schedule(periph, CAM_PRIORITY_NORMAL);
		}
	}
	/* Queue us up again */
	if (cd_poll_period != 0)
		callout_schedule(&softc->mediapoll_c, cd_poll_period * hz);
}