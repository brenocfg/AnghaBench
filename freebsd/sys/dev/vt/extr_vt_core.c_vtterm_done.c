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
struct vt_window {struct vt_device* vw_device; } ;
struct vt_device {int vd_flags; TYPE_1__* vd_driver; struct vt_window* vd_curwindow; } ;
struct terminal {struct vt_window* tm_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* vd_postswitch ) (struct vt_device*) ;} ;

/* Variables and functions */
 int VDF_ASYNC ; 
 int VDF_INVALID ; 
 int VDF_SPLASH ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  stub1 (struct vt_device*) ; 
 int /*<<< orphan*/  vt_flush (struct vt_device*) ; 

__attribute__((used)) static void
vtterm_done(struct terminal *tm)
{
	struct vt_window *vw = tm->tm_softc;
	struct vt_device *vd = vw->vw_device;

	if (kdb_active || panicstr != NULL) {
		/* Switch to the debugger. */
		if (vd->vd_curwindow != vw) {
			vd->vd_curwindow = vw;
			vd->vd_flags |= VDF_INVALID;
			if (vd->vd_driver->vd_postswitch)
				vd->vd_driver->vd_postswitch(vd);
		}
		vd->vd_flags &= ~VDF_SPLASH;
		vt_flush(vd);
	} else if (!(vd->vd_flags & VDF_ASYNC)) {
		vt_flush(vd);
	}
}