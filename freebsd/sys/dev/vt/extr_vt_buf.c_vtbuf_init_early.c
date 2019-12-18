#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  tp_row; int /*<<< orphan*/  tp_col; } ;
struct TYPE_13__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_17__ {TYPE_5__ tr_end; TYPE_3__ tr_begin; } ;
typedef  TYPE_7__ term_rect_t ;
typedef  int term_char_t ;
struct TYPE_18__ {scalar_t__ ta_bgcolor; scalar_t__ ta_fgcolor; } ;
typedef  TYPE_8__ teken_attr_t ;
struct TYPE_14__ {int /*<<< orphan*/  tp_col; } ;
struct TYPE_12__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_11__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct vt_buf {int vb_flags; int /*<<< orphan*/  vb_lock; TYPE_6__* vb_terminal; int /*<<< orphan*/  vb_history_size; TYPE_4__ vb_scr_size; TYPE_2__ vb_mark_end; TYPE_1__ vb_mark_start; scalar_t__ vb_curroffset; scalar_t__ vb_roffset; } ;
struct TYPE_16__ {int /*<<< orphan*/  tm_emulator; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int TCOLOR_BG (int) ; 
 int TCOLOR_FG (int) ; 
 int VBF_CURSOR ; 
 int VBF_MTX_INIT ; 
 int /*<<< orphan*/  VTBUF_SPACE_CHAR (int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_8__* teken_get_curattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtbuf_do_fill (struct vt_buf*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtbuf_init_rows (struct vt_buf*) ; 
 int /*<<< orphan*/  vtbuf_make_undirty (struct vt_buf*) ; 

void
vtbuf_init_early(struct vt_buf *vb)
{
	term_rect_t rect;
	const teken_attr_t *a;
	term_char_t c;

	vb->vb_flags |= VBF_CURSOR;
	vb->vb_roffset = 0;
	vb->vb_curroffset = 0;
	vb->vb_mark_start.tp_row = 0;
	vb->vb_mark_start.tp_col = 0;
	vb->vb_mark_end.tp_row = 0;
	vb->vb_mark_end.tp_col = 0;

	vtbuf_init_rows(vb);
	rect.tr_begin.tp_row = rect.tr_begin.tp_col = 0;
	rect.tr_end.tp_col = vb->vb_scr_size.tp_col;
	rect.tr_end.tp_row = vb->vb_history_size;

	a = teken_get_curattr(&vb->vb_terminal->tm_emulator);
	c = TCOLOR_FG((term_char_t)a->ta_fgcolor) | 
	    TCOLOR_BG((term_char_t)a->ta_bgcolor);
	vtbuf_do_fill(vb, &rect, VTBUF_SPACE_CHAR(c));
	vtbuf_make_undirty(vb);
	if ((vb->vb_flags & VBF_MTX_INIT) == 0) {
		mtx_init(&vb->vb_lock, "vtbuf", NULL, MTX_SPIN);
		vb->vb_flags |= VBF_MTX_INIT;
	}
}