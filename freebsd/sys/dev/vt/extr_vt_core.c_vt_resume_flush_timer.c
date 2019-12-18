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
struct vt_window {struct vt_device* vw_device; } ;
struct vt_device {int vd_flags; int /*<<< orphan*/  vd_timer_armed; struct vt_window* vd_curwindow; } ;

/* Variables and functions */
 int VDF_ASYNC ; 
 int /*<<< orphan*/  atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vt_schedule_flush (struct vt_device*,int) ; 

void
vt_resume_flush_timer(struct vt_window *vw, int ms)
{
	struct vt_device *vd = vw->vw_device;

	if (vd->vd_curwindow != vw)
		return;

	if (!(vd->vd_flags & VDF_ASYNC) ||
	    !atomic_cmpset_int(&vd->vd_timer_armed, 0, 1))
		return;

	vt_schedule_flush(vd, ms);
}