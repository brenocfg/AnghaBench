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
struct vt_window {int vw_flags; int /*<<< orphan*/  vw_switch_to; int /*<<< orphan*/  vw_proc_dead_timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int VWF_SWWAIT_REL ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_late_window_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
finish_vt_rel(struct vt_window *vw, int release, int *s)
{

	if (vw->vw_flags & VWF_SWWAIT_REL) {
		vw->vw_flags &= ~VWF_SWWAIT_REL;
		if (release) {
			callout_drain(&vw->vw_proc_dead_timer);
			(void)vt_late_window_switch(vw->vw_switch_to);
		}
		return (0);
	}
	return (EINVAL);
}