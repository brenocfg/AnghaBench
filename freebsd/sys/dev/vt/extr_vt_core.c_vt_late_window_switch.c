#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mode; } ;
struct vt_window {TYPE_2__ vw_smode; TYPE_1__* vw_device; int /*<<< orphan*/  vw_proc_dead_timer; } ;
struct TYPE_3__ {struct vt_window* vd_curwindow; } ;

/* Variables and functions */
 scalar_t__ VT_PROCESS ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int vt_window_postswitch (struct vt_window*) ; 
 int vt_window_switch (struct vt_window*) ; 

__attribute__((used)) static int
vt_late_window_switch(struct vt_window *vw)
{
	struct vt_window *curvw;
	int ret;

	callout_stop(&vw->vw_proc_dead_timer);

	ret = vt_window_switch(vw);
	if (ret != 0) {
		/*
		 * If the switch hasn't happened, then return the VT
		 * to the current owner, if any.
		 */
		curvw = vw->vw_device->vd_curwindow;
		if (curvw->vw_smode.mode == VT_PROCESS)
			(void)vt_window_postswitch(curvw);
		return (ret);
	}

	/* Notify owner process about terminal availability. */
	if (vw->vw_smode.mode == VT_PROCESS) {
		ret = vt_window_postswitch(vw);
	}
	return (ret);
}