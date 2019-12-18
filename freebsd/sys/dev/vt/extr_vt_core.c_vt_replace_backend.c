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
typedef  struct vt_driver {int /*<<< orphan*/  (* vd_fini ) (struct vt_device*,void*) ;int /*<<< orphan*/  (* vd_init ) (struct vt_device*) ;} const vt_driver ;
struct vt_device {int vd_flags; TYPE_1__** vd_windows; TYPE_2__* vd_curwindow; struct vt_driver const* vd_driver; int /*<<< orphan*/ * vd_prev_softc; struct vt_driver const* vd_prev_driver; int /*<<< orphan*/ * vd_softc; } ;
struct TYPE_4__ {int /*<<< orphan*/  vw_terminal; } ;
struct TYPE_3__ {int /*<<< orphan*/  vw_terminal; } ;

/* Variables and functions */
 int VDF_ASYNC ; 
 int VDF_DOWNGRADE ; 
 int VDF_SPLASH ; 
 int VDF_TEXTMODE ; 
 size_t VT_CONSWINDOW ; 
 int /*<<< orphan*/  VT_LOCK (struct vt_device*) ; 
 int /*<<< orphan*/  VT_UNLOCK (struct vt_device*) ; 
 struct vt_device* main_vd ; 
 int /*<<< orphan*/  stub1 (struct vt_device*) ; 
 int /*<<< orphan*/  stub2 (struct vt_device*) ; 
 int /*<<< orphan*/  stub3 (struct vt_device*,void*) ; 
 int /*<<< orphan*/  termcn_cnregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminal_mute (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vt_resume_flush_timer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_suspend_flush_timer (struct vt_device*) ; 
 int /*<<< orphan*/  vt_upgrade (struct vt_device*) ; 
 int /*<<< orphan*/  vtterm_splash (struct vt_device*) ; 

__attribute__((used)) static void
vt_replace_backend(const struct vt_driver *drv, void *softc)
{
	struct vt_device *vd;

	vd = main_vd;

	if (vd->vd_flags & VDF_ASYNC) {
		/* Stop vt_flush periodic task. */
		VT_LOCK(vd);
		vt_suspend_flush_timer(vd);
		VT_UNLOCK(vd);
		/*
		 * Mute current terminal until we done. vt_change_font (called
		 * from vt_resize) will unmute it.
		 */
		terminal_mute(vd->vd_curwindow->vw_terminal, 1);
	}

	/*
	 * Reset VDF_TEXTMODE flag, driver who require that flag (vt_vga) will
	 * set it.
	 */
	VT_LOCK(vd);
	vd->vd_flags &= ~VDF_TEXTMODE;

	if (drv != NULL) {
		/*
		 * We want to upgrade from the current driver to the
		 * given driver.
		 */

		vd->vd_prev_driver = vd->vd_driver;
		vd->vd_prev_softc = vd->vd_softc;
		vd->vd_driver = drv;
		vd->vd_softc = softc;

		vd->vd_driver->vd_init(vd);
	} else if (vd->vd_prev_driver != NULL && vd->vd_prev_softc != NULL) {
		/*
		 * No driver given: we want to downgrade to the previous
		 * driver.
		 */
		const struct vt_driver *old_drv;
		void *old_softc;

		old_drv = vd->vd_driver;
		old_softc = vd->vd_softc;

		vd->vd_driver = vd->vd_prev_driver;
		vd->vd_softc = vd->vd_prev_softc;
		vd->vd_prev_driver = NULL;
		vd->vd_prev_softc = NULL;

		vd->vd_flags |= VDF_DOWNGRADE;

		vd->vd_driver->vd_init(vd);

		if (old_drv->vd_fini)
			old_drv->vd_fini(vd, old_softc);

		vd->vd_flags &= ~VDF_DOWNGRADE;
	}

	VT_UNLOCK(vd);

	/* Update windows sizes and initialize last items. */
	vt_upgrade(vd);

#ifdef DEV_SPLASH
	if (vd->vd_flags & VDF_SPLASH)
		vtterm_splash(vd);
#endif

	if (vd->vd_flags & VDF_ASYNC) {
		/* Allow to put chars now. */
		terminal_mute(vd->vd_curwindow->vw_terminal, 0);
		/* Rerun timer for screen updates. */
		vt_resume_flush_timer(vd->vd_curwindow, 0);
	}

	/*
	 * Register as console. If it already registered, cnadd() will ignore
	 * it.
	 */
	termcn_cnregister(vd->vd_windows[VT_CONSWINDOW]->vw_terminal);
}