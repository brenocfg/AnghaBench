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
struct TYPE_6__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_5__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_4__ {int tp_row; } ;
struct vt_buf {int vb_curroffset; int vb_history_size; int vb_flags; int vb_roffset; TYPE_3__ vb_mark_end; TYPE_2__ vb_mark_start; TYPE_1__ vb_scr_size; } ;

/* Variables and functions */
 int VBF_HISTORY_FULL ; 
 int VBF_SCROLL ; 
 scalar_t__ vtbuf_in_this_range (int,int /*<<< orphan*/ ,int,int) ; 

void
vthistory_addlines(struct vt_buf *vb, int offset)
{
#ifndef SC_NO_CUTPASTE
	int cur, sz;
#endif

	vb->vb_curroffset += offset;
	if (vb->vb_curroffset + vb->vb_scr_size.tp_row >= vb->vb_history_size) {
		vb->vb_flags |= VBF_HISTORY_FULL;
		vb->vb_curroffset %= vb->vb_history_size;
	}
	if ((vb->vb_flags & VBF_SCROLL) == 0) {
		vb->vb_roffset = vb->vb_curroffset;
	}

#ifndef SC_NO_CUTPASTE
	sz = vb->vb_history_size;
	cur = vb->vb_roffset + vb->vb_scr_size.tp_row + sz - 1;
	if (vtbuf_in_this_range(cur, vb->vb_mark_start.tp_row, cur + offset, sz) ||
	    vtbuf_in_this_range(cur, vb->vb_mark_end.tp_row, cur + offset, sz)) {
		/* clear screen selection */
		vb->vb_mark_start.tp_row = vb->vb_mark_end.tp_row;
		vb->vb_mark_start.tp_col = vb->vb_mark_end.tp_col;
	}
#endif
}