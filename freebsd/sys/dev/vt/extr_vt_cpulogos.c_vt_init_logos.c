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
typedef  int /*<<< orphan*/  term_pos_t ;
struct winsize {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb_cursor; int /*<<< orphan*/  vb_history_size; } ;
struct vt_window {TYPE_1__ vw_buf; struct vt_font* vw_font; struct vt_device* vw_device; } ;
struct vt_font {int dummy; } ;
struct vt_device {int vd_flags; scalar_t__ vd_height; struct vt_window* vd_curwindow; } ;
struct terminal {struct vt_window* tm_softc; } ;

/* Variables and functions */
 int VDF_DEAD ; 
 int VDF_INITIALIZED ; 
 int VDF_INVALID ; 
 int VDF_TEXTMODE ; 
 int /*<<< orphan*/  VTY_VT ; 
 int /*<<< orphan*/  VT_LOCK (struct vt_device*) ; 
 int /*<<< orphan*/  VT_UNLOCK (struct vt_device*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  terminal_mute (struct terminal*,int) ; 
 int /*<<< orphan*/  terminal_set_cursor (struct terminal*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal_set_winsize_blank (struct terminal*,struct winsize*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_compute_drawable_area (struct vt_window*) ; 
 struct terminal vt_consterm ; 
 int vt_draw_logo_cpus ; 
 int /*<<< orphan*/  vt_fini_logos ; 
 scalar_t__ vt_logo_sprite_height ; 
 int /*<<< orphan*/  vt_resume_flush_timer (struct vt_window*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_splash_cpu ; 
 int /*<<< orphan*/  vt_splash_cpu_callout ; 
 int vt_splash_cpu_duration ; 
 int /*<<< orphan*/  vt_termsize (struct vt_device*,struct vt_font*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_winsize (struct vt_device*,struct vt_font*,struct winsize*) ; 
 int /*<<< orphan*/  vtbuf_grow (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vt_init_logos(void *dummy)
{
	struct vt_device *vd;
	struct vt_window *vw;
	struct terminal *tm;
	struct vt_font *vf;
	struct winsize wsz;
	term_pos_t size;

	if (!vty_enabled(VTY_VT))
		return;
	if (!vt_splash_cpu)
		return;

	tm = &vt_consterm;
	vw = tm->tm_softc;
	if (vw == NULL)
		return;
	vd = vw->vw_device;
	if (vd == NULL)
		return;
	vf = vw->vw_font;
	if (vf == NULL)
		return;

	VT_LOCK(vd);
	if ((vd->vd_flags & VDF_INITIALIZED) == 0)
		goto out;
	if ((vd->vd_flags & (VDF_DEAD | VDF_TEXTMODE)) != 0)
		goto out;
	if (vd->vd_height <= vt_logo_sprite_height)
		goto out;

	vt_draw_logo_cpus = 1;
	VT_UNLOCK(vd);

	vt_termsize(vd, vf, &size);
	vt_winsize(vd, vf, &wsz);

	/* Resize screen buffer and terminal. */
	terminal_mute(tm, 1);
	vtbuf_grow(&vw->vw_buf, &size, vw->vw_buf.vb_history_size);
	terminal_set_winsize_blank(tm, &wsz, 0, NULL);
	terminal_set_cursor(tm, &vw->vw_buf.vb_cursor);
	terminal_mute(tm, 0);

	VT_LOCK(vd);
	vt_compute_drawable_area(vw);

	if (vd->vd_curwindow == vw) {
		vd->vd_flags |= VDF_INVALID;
		vt_resume_flush_timer(vw, 0);
	}

	callout_init(&vt_splash_cpu_callout, 1);
	callout_reset(&vt_splash_cpu_callout, vt_splash_cpu_duration * hz,
	    vt_fini_logos, NULL);

out:
	VT_UNLOCK(vd);
}