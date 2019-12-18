#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_8__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_11__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_4__ term_rect_t ;
typedef  int /*<<< orphan*/  term_char_t ;
struct TYPE_10__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct vt_buf {TYPE_3__ vb_scr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  vtbuf_dirty (struct vt_buf*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  vtbuf_do_fill (struct vt_buf*,TYPE_4__ const*,int /*<<< orphan*/ ) ; 

void
vtbuf_fill(struct vt_buf *vb, const term_rect_t *r, term_char_t c)
{

	KASSERT(r->tr_begin.tp_row < vb->vb_scr_size.tp_row,
	    ("vtbuf_fill begin.tp_row %d must be < screen height %d",
		r->tr_begin.tp_row, vb->vb_scr_size.tp_row));
	KASSERT(r->tr_begin.tp_col < vb->vb_scr_size.tp_col,
	    ("vtbuf_fill begin.tp_col %d must be < screen width %d",
		r->tr_begin.tp_col, vb->vb_scr_size.tp_col));

	KASSERT(r->tr_end.tp_row <= vb->vb_scr_size.tp_row,
	    ("vtbuf_fill end.tp_row %d must be <= screen height %d",
		r->tr_end.tp_row, vb->vb_scr_size.tp_row));
	KASSERT(r->tr_end.tp_col <= vb->vb_scr_size.tp_col,
	    ("vtbuf_fill end.tp_col %d must be <= screen width %d",
		r->tr_end.tp_col, vb->vb_scr_size.tp_col));

	vtbuf_do_fill(vb, r, c);
	vtbuf_dirty(vb, r);
}