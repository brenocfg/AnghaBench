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
struct vt_window {int /*<<< orphan*/  vw_kbdmode; int /*<<< orphan*/  vw_prev_kbdmode; int /*<<< orphan*/  vw_grabbed; struct vt_device* vw_device; } ;
struct vt_device {int /*<<< orphan*/  vd_keyboard; } ;
struct terminal {struct vt_window* tm_softc; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  K_XLATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/ * kbd_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbdd_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_update_kbd_mode (struct vt_window*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_window_switch (struct vt_window*) ; 

__attribute__((used)) static void
vtterm_cngrab(struct terminal *tm)
{
	struct vt_device *vd;
	struct vt_window *vw;
	keyboard_t *kbd;

	vw = tm->tm_softc;
	vd = vw->vw_device;

	if (!cold)
		vt_window_switch(vw);

	kbd = kbd_get_keyboard(vd->vd_keyboard);
	if (kbd == NULL)
		return;

	if (vw->vw_grabbed++ > 0)
		return;

	/*
	 * Make sure the keyboard is accessible even when the kbd device
	 * driver is disabled.
	 */
	kbdd_enable(kbd);

	/* We shall always use the keyboard in the XLATE mode here. */
	vw->vw_prev_kbdmode = vw->vw_kbdmode;
	vw->vw_kbdmode = K_XLATE;
	vt_update_kbd_mode(vw, kbd);

	kbdd_poll(kbd, TRUE);
}