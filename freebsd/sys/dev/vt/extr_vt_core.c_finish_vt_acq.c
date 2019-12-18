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
struct vt_window {int vw_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int VWF_SWWAIT_ACQ ; 

__attribute__((used)) static int
finish_vt_acq(struct vt_window *vw)
{

	if (vw->vw_flags & VWF_SWWAIT_ACQ) {
		vw->vw_flags &= ~VWF_SWWAIT_ACQ;
		return (0);
	}
	return (EINVAL);
}