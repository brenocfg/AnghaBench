#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tp_row; int tp_col; } ;
typedef  TYPE_2__ term_pos_t ;
typedef  int /*<<< orphan*/  term_char_t ;
struct TYPE_5__ {int tp_col; } ;
struct TYPE_7__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct vt_buf {TYPE_1__ vb_scr_size; TYPE_4__ vb_mark_end; TYPE_4__ vb_mark_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  POS_COPY (TYPE_2__,TYPE_4__) ; 
 scalar_t__ POS_INDEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtbuf_htw (struct vt_buf*,int /*<<< orphan*/ ) ; 

int
vtbuf_get_marked_len(struct vt_buf *vb)
{
	int ei, si, sz;
	term_pos_t s, e;

	/* Swap according to window coordinates. */
	if (POS_INDEX(vtbuf_htw(vb, vb->vb_mark_start.tp_row),
	    vb->vb_mark_start.tp_col) >
	    POS_INDEX(vtbuf_htw(vb, vb->vb_mark_end.tp_row),
	    vb->vb_mark_end.tp_col)) {
		POS_COPY(e, vb->vb_mark_start);
		POS_COPY(s, vb->vb_mark_end);
	} else {
		POS_COPY(s, vb->vb_mark_start);
		POS_COPY(e, vb->vb_mark_end);
	}

	si = s.tp_row * vb->vb_scr_size.tp_col + s.tp_col;
	ei = e.tp_row * vb->vb_scr_size.tp_col + e.tp_col;

	/* Number symbols and number of rows to inject \n */
	sz = ei - si + ((e.tp_row - s.tp_row) * 2);

	return (sz * sizeof(term_char_t));
}