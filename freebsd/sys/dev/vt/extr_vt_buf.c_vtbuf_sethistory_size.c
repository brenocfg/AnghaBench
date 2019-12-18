#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
typedef  TYPE_2__ term_pos_t ;
struct TYPE_4__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct vt_buf {TYPE_1__ vb_scr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtbuf_grow (struct vt_buf*,TYPE_2__*,unsigned int) ; 

void
vtbuf_sethistory_size(struct vt_buf *vb, unsigned int size)
{
	term_pos_t p;

	/* With same size */
	p.tp_row = vb->vb_scr_size.tp_row;
	p.tp_col = vb->vb_scr_size.tp_col;
	vtbuf_grow(vb, &p, size);
}