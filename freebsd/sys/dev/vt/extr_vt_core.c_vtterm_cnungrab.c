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
struct vt_window {scalar_t__ vw_grabbed; int /*<<< orphan*/  vw_prev_kbdmode; int /*<<< orphan*/  vw_kbdmode; struct vt_device* vw_device; } ;
struct vt_device {int /*<<< orphan*/  vd_keyboard; } ;
struct terminal {struct vt_window* tm_softc; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * kbd_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbdd_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_update_kbd_mode (struct vt_window*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtterm_cnungrab(struct terminal *tm)
{
	struct vt_device *vd;
	struct vt_window *vw;
	keyboard_t *kbd;

	vw = tm->tm_softc;
	vd = vw->vw_device;

	kbd = kbd_get_keyboard(vd->vd_keyboard);
	if (kbd == NULL)
		return;

	if (--vw->vw_grabbed > 0)
		return;

	kbdd_poll(kbd, FALSE);

	vw->vw_kbdmode = vw->vw_prev_kbdmode;
	vt_update_kbd_mode(vw, kbd);
	kbdd_disable(kbd);
}