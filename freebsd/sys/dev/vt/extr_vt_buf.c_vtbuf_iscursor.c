#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tp_col; int tp_row; } ;
struct TYPE_5__ {int tp_col; int tp_row; } ;
struct TYPE_4__ {int tp_row; int tp_col; } ;
struct vt_buf {int vb_flags; int vb_history_size; TYPE_3__ vb_mark_end; TYPE_2__ vb_mark_start; TYPE_1__ vb_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  POS_INDEX (int,int) ; 
 int VBF_CURSOR ; 
 int VBF_SCROLL ; 
 scalar_t__ vtbuf_in_this_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtbuf_wth (struct vt_buf const*,int) ; 

int
vtbuf_iscursor(const struct vt_buf *vb, int row, int col)
{
#ifndef SC_NO_CUTPASTE
	int sc, sr, sz, ec, er, tmp;
#endif

	if ((vb->vb_flags & (VBF_CURSOR|VBF_SCROLL)) == VBF_CURSOR &&
	    (vb->vb_cursor.tp_row == row) && (vb->vb_cursor.tp_col == col))
		return (1);

#ifndef SC_NO_CUTPASTE
	/* Mark cut/paste region. */
	if (vb->vb_mark_start.tp_col == vb->vb_mark_end.tp_col &&
	    vb->vb_mark_start.tp_row == vb->vb_mark_end.tp_row)
		return (0);

	sc = vb->vb_mark_start.tp_col;
	sr = vb->vb_mark_start.tp_row;
	ec = vb->vb_mark_end.tp_col;
	er = vb->vb_mark_end.tp_row;

	/*
	 * Information about if the selection was made bottom-top or
	 * top-bottom is lost due to modulo arithmetics and needs to
	 * be recovered:
	 */
	sz = vb->vb_history_size;
	tmp = (sz + er - sr) % sz;
	row = vtbuf_wth(vb, row);

	/* Swap start and end if start > end */
	if ((2 * tmp) > sz || (tmp == 0 && sc > ec)) {
		tmp = sc; sc = ec; ec = tmp;
		tmp = sr; sr = er; er = tmp;
	}

	if (vtbuf_in_this_range(POS_INDEX(sc, sr), POS_INDEX(col, row),
	    POS_INDEX(ec, er), POS_INDEX(0, sz)))
		return (1);
#endif

	return (0);
}