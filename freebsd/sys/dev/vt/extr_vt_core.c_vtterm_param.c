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
struct vt_window {unsigned int vw_mouse_level; int /*<<< orphan*/  vw_buf; } ;
struct terminal {struct vt_window* tm_softc; } ;

/* Variables and functions */
#define  TP_MOUSE 130 
#define  TP_SETLOCALCURSOR 129 
#define  TP_SHOWCURSOR 128 
 int /*<<< orphan*/  vt_resume_flush_timer (struct vt_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtbuf_cursor_visibility (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
vtterm_param(struct terminal *tm, int cmd, unsigned int arg)
{
	struct vt_window *vw = tm->tm_softc;

	switch (cmd) {
	case TP_SETLOCALCURSOR:
		/*
		 * 0 means normal (usually block), 1 means hidden, and
		 * 2 means blinking (always block) for compatibility with
		 * syscons.  We don't support any changes except hiding,
		 * so must map 2 to 0.
		 */
		arg = (arg == 1) ? 0 : 1;
		/* FALLTHROUGH */
	case TP_SHOWCURSOR:
		vtbuf_cursor_visibility(&vw->vw_buf, arg);
		vt_resume_flush_timer(vw, 0);
		break;
	case TP_MOUSE:
		vw->vw_mouse_level = arg;
		break;
	}
}