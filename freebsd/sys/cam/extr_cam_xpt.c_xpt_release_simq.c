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
struct cam_sim {int flags; struct cam_devq* devq; int /*<<< orphan*/  callout; } ;
struct TYPE_2__ {scalar_t__ qfrozen_cnt; } ;
struct cam_devq {int /*<<< orphan*/  send_mtx; TYPE_1__ send_queue; } ;

/* Variables and functions */
 int CAM_SIM_REL_TIMEOUT_PENDING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  xpt_run_devq (struct cam_devq*) ; 

void
xpt_release_simq(struct cam_sim *sim, int run_queue)
{
	struct cam_devq	*devq;

	devq = sim->devq;
	mtx_lock(&devq->send_mtx);
	if (devq->send_queue.qfrozen_cnt <= 0) {
#ifdef INVARIANTS
		printf("xpt_release_simq: requested 1 > present %u\n",
		    devq->send_queue.qfrozen_cnt);
#endif
	} else
		devq->send_queue.qfrozen_cnt--;
	if (devq->send_queue.qfrozen_cnt == 0) {
		/*
		 * If there is a timeout scheduled to release this
		 * sim queue, remove it.  The queue frozen count is
		 * already at 0.
		 */
		if ((sim->flags & CAM_SIM_REL_TIMEOUT_PENDING) != 0){
			callout_stop(&sim->callout);
			sim->flags &= ~CAM_SIM_REL_TIMEOUT_PENDING;
		}
		if (run_queue) {
			/*
			 * Now that we are unfrozen run the send queue.
			 */
			xpt_run_devq(sim->devq);
		}
	}
	mtx_unlock(&devq->send_mtx);
}