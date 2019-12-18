#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int tp_col; int tp_row; } ;
struct TYPE_9__ {int tp_col; int tp_row; } ;
struct TYPE_12__ {TYPE_3__ tr_end; TYPE_2__ tr_begin; } ;
typedef  TYPE_5__ term_rect_t ;
struct vt_window {int /*<<< orphan*/  vw_buf; struct vt_font* vw_font; } ;
struct vt_font {int vf_width; int vf_height; } ;
struct vt_device {int vd_mx_drawn; int vd_my_drawn; TYPE_4__* vd_driver; TYPE_1__* vd_mcursor; struct vt_window* vd_curwindow; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* vd_invalidate_text ) (struct vt_device*,TYPE_5__*) ;} ;
struct TYPE_8__ {int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vt_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  vtbuf_dirty (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  vtbuf_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtbuf_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vt_mark_mouse_position_as_dirty(struct vt_device *vd, int locked)
{
	term_rect_t area;
	struct vt_window *vw;
	struct vt_font *vf;
	int x, y;

	vw = vd->vd_curwindow;
	vf = vw->vw_font;

	x = vd->vd_mx_drawn;
	y = vd->vd_my_drawn;

	if (vf != NULL) {
		area.tr_begin.tp_col = x / vf->vf_width;
		area.tr_begin.tp_row = y / vf->vf_height;
		area.tr_end.tp_col =
		    ((x + vd->vd_mcursor->width) / vf->vf_width) + 1;
		area.tr_end.tp_row =
		    ((y + vd->vd_mcursor->height) / vf->vf_height) + 1;
	} else {
		/*
		 * No font loaded (ie. vt_vga operating in textmode).
		 *
		 * FIXME: This fake area needs to be revisited once the
		 * mouse cursor is supported in vt_vga's textmode.
		 */
		area.tr_begin.tp_col = x;
		area.tr_begin.tp_row = y;
		area.tr_end.tp_col = x + 2;
		area.tr_end.tp_row = y + 2;
	}

	if (!locked)
		vtbuf_lock(&vw->vw_buf);
	if (vd->vd_driver->vd_invalidate_text)
		vd->vd_driver->vd_invalidate_text(vd, &area);
	vtbuf_dirty(&vw->vw_buf, &area);
	if (!locked)
		vtbuf_unlock(&vw->vw_buf);
}