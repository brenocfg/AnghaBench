#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t tp_row; size_t tp_col; } ;
typedef  TYPE_2__ term_pos_t ;
typedef  scalar_t__ term_char_t ;
struct TYPE_5__ {size_t tp_row; size_t tp_col; } ;
struct vt_buf {size_t vb_curroffset; scalar_t__** vb_rows; TYPE_1__ vb_scr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t VTBUF_MAX_HEIGHT (struct vt_buf*) ; 
 int /*<<< orphan*/  vtbuf_dirty_cell (struct vt_buf*,TYPE_2__ const*) ; 

void
vtbuf_putchar(struct vt_buf *vb, const term_pos_t *p, term_char_t c)
{
	term_char_t *row;

	KASSERT(p->tp_row < vb->vb_scr_size.tp_row,
	    ("vtbuf_putchar tp_row %d must be less than screen width %d",
		p->tp_row, vb->vb_scr_size.tp_row));
	KASSERT(p->tp_col < vb->vb_scr_size.tp_col,
	    ("vtbuf_putchar tp_col %d must be less than screen height %d",
		p->tp_col, vb->vb_scr_size.tp_col));

	row = vb->vb_rows[(vb->vb_curroffset + p->tp_row) %
	    VTBUF_MAX_HEIGHT(vb)];
	if (row[p->tp_col] != c) {
		row[p->tp_col] = c;
		vtbuf_dirty_cell(vb, p);
	}
}