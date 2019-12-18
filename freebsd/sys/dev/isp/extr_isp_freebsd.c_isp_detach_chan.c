#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct TYPE_12__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {struct cam_sim* callback_arg; int /*<<< orphan*/  callback; scalar_t__ event_enable; TYPE_4__ ccb_h; } ;
struct cam_sim {int dummy; } ;
typedef  struct cam_sim cam_path ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_10__ {TYPE_1__ pc; } ;
struct TYPE_11__ {int /*<<< orphan*/  isp_lock; TYPE_2__ isp_osinfo; } ;
typedef  TYPE_3__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISP_GET_PC (TYPE_3__*,int,struct cam_sim*,struct cam_sim*) ; 
 int /*<<< orphan*/  ISP_GET_PC_ADDR (TYPE_3__*,int,int*,int*) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 int /*<<< orphan*/  isp_cam_async ; 
 int /*<<< orphan*/  mtx_sleep (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_sim*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_4__*,struct cam_sim*,int) ; 

__attribute__((used)) static void
isp_detach_chan(ispsoftc_t *isp, int chan)
{
	struct cam_sim *sim;
	struct cam_path *path;
	struct ccb_setasync csa;
	int *num_threads;

	ISP_GET_PC(isp, chan, sim, sim);
	ISP_GET_PC(isp, chan, path, path);
	ISP_GET_PC_ADDR(isp, chan, num_threads, num_threads);

	xpt_setup_ccb(&csa.ccb_h, path, 5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = 0;
	csa.callback = isp_cam_async;
	csa.callback_arg = sim;
	xpt_action((union ccb *)&csa);
	xpt_free_path(path);
	xpt_bus_deregister(cam_sim_path(sim));
	cam_sim_free(sim, FALSE);

	/* Wait for the channel's spawned threads to exit. */
	wakeup(isp->isp_osinfo.pc.ptr);
	while (*num_threads != 0)
		mtx_sleep(isp, &isp->isp_lock, PRIBIO, "isp_reap", 100);
}