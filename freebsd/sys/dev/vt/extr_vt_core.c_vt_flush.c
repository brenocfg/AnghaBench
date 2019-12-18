#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ tp_col; } ;
struct TYPE_13__ {scalar_t__ tp_col; } ;
struct TYPE_16__ {TYPE_3__ tr_end; TYPE_2__ tr_begin; } ;
typedef  TYPE_5__ term_rect_t ;
struct TYPE_17__ {int /*<<< orphan*/  ta_bgcolor; } ;
typedef  TYPE_6__ teken_attr_t ;
struct vt_window {int vw_flags; int /*<<< orphan*/  vw_buf; int /*<<< orphan*/  vw_draw_area; TYPE_1__* vw_terminal; struct vt_font* vw_font; } ;
struct vt_font {int dummy; } ;
struct vt_device {int vd_flags; int vd_mshown; scalar_t__ vd_mx; scalar_t__ vd_mx_drawn; scalar_t__ vd_my; scalar_t__ vd_my_drawn; TYPE_4__* vd_driver; struct vt_window* vd_curwindow; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* vd_bitblt_text ) (struct vt_device*,struct vt_window*,TYPE_5__*) ;int /*<<< orphan*/  (* vd_invalidate_text ) (struct vt_device*,TYPE_5__*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  tm_emulator; } ;

/* Variables and functions */
 int VDF_INVALID ; 
 int VDF_MOUSECURSOR ; 
 int VDF_SPLASH ; 
 int VDF_SUSPENDED ; 
 int VDF_TEXTMODE ; 
 int VWF_BUSY ; 
 int VWF_MOUSE_HIDE ; 
 int /*<<< orphan*/  kdb_active ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  stub1 (struct vt_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (struct vt_device*,struct vt_window*,TYPE_5__*) ; 
 TYPE_6__* teken_get_curattr (int /*<<< orphan*/ *) ; 
 scalar_t__ vt_draw_logo_cpus ; 
 int /*<<< orphan*/  vt_mark_mouse_position_as_dirty (struct vt_device*,int) ; 
 int /*<<< orphan*/  vt_set_border (struct vt_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_termrect (struct vt_device*,struct vt_font*,TYPE_5__*) ; 
 int /*<<< orphan*/  vtbuf_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtbuf_undirty (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  vtbuf_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtterm_draw_cpu_logos (struct vt_device*) ; 

__attribute__((used)) static int
vt_flush(struct vt_device *vd)
{
	struct vt_window *vw;
	struct vt_font *vf;
	term_rect_t tarea;
#ifndef SC_NO_CUTPASTE
	int cursor_was_shown, cursor_moved;
#endif

	vw = vd->vd_curwindow;
	if (vw == NULL)
		return (0);

	if (vd->vd_flags & VDF_SPLASH || vw->vw_flags & VWF_BUSY)
		return (0);

	vf = vw->vw_font;
	if (((vd->vd_flags & VDF_TEXTMODE) == 0) && (vf == NULL))
		return (0);

	vtbuf_lock(&vw->vw_buf);

#ifndef SC_NO_CUTPASTE
	cursor_was_shown = vd->vd_mshown;
	cursor_moved = (vd->vd_mx != vd->vd_mx_drawn ||
	    vd->vd_my != vd->vd_my_drawn);

	/* Check if the cursor should be displayed or not. */
	if ((vd->vd_flags & VDF_MOUSECURSOR) && /* Mouse support enabled. */
	    !(vw->vw_flags & VWF_MOUSE_HIDE) && /* Cursor displayed.      */
	    !kdb_active && panicstr == NULL) {  /* DDB inactive.          */
		vd->vd_mshown = 1;
	} else {
		vd->vd_mshown = 0;
	}

	/*
	 * If the cursor changed display state or moved, we must mark
	 * the old position as dirty, so that it's erased.
	 */
	if (cursor_was_shown != vd->vd_mshown ||
	    (vd->vd_mshown && cursor_moved))
		vt_mark_mouse_position_as_dirty(vd, true);

	/*
         * Save position of the mouse cursor. It's used by backends to
         * know where to draw the cursor and during the next refresh to
         * erase the previous position.
	 */
	vd->vd_mx_drawn = vd->vd_mx;
	vd->vd_my_drawn = vd->vd_my;

	/*
	 * If the cursor is displayed and has moved since last refresh,
	 * mark the new position as dirty.
	 */
	if (vd->vd_mshown && cursor_moved)
		vt_mark_mouse_position_as_dirty(vd, true);
#endif

	vtbuf_undirty(&vw->vw_buf, &tarea);

	/* Force a full redraw when the screen contents might be invalid. */
	if (vd->vd_flags & (VDF_INVALID | VDF_SUSPENDED)) {
		const teken_attr_t *a;

		vd->vd_flags &= ~VDF_INVALID;

		a = teken_get_curattr(&vw->vw_terminal->tm_emulator);
		vt_set_border(vd, &vw->vw_draw_area, a->ta_bgcolor);
		vt_termrect(vd, vf, &tarea);
		if (vd->vd_driver->vd_invalidate_text)
			vd->vd_driver->vd_invalidate_text(vd, &tarea);
		if (vt_draw_logo_cpus)
			vtterm_draw_cpu_logos(vd);
	}

	if (tarea.tr_begin.tp_col < tarea.tr_end.tp_col) {
		vd->vd_driver->vd_bitblt_text(vd, vw, &tarea);
		vtbuf_unlock(&vw->vw_buf);
		return (1);
	}

	vtbuf_unlock(&vw->vw_buf);
	return (0);
}