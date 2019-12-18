#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int tp_row; unsigned int tp_col; } ;
struct TYPE_5__ {unsigned int tp_row; unsigned int tp_col; } ;
struct TYPE_7__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_3__ term_rect_t ;
typedef  int /*<<< orphan*/  term_char_t ;
struct vt_buf {unsigned int vb_curroffset; int /*<<< orphan*/ ** vb_rows; } ;

/* Variables and functions */
 unsigned int VTBUF_MAX_HEIGHT (struct vt_buf*) ; 

__attribute__((used)) static void
vtbuf_do_fill(struct vt_buf *vb, const term_rect_t *r, term_char_t c)
{
	unsigned int pr, pc;
	term_char_t *row;

	for (pr = r->tr_begin.tp_row; pr < r->tr_end.tp_row; pr++) {
		row = vb->vb_rows[(vb->vb_curroffset + pr) %
		    VTBUF_MAX_HEIGHT(vb)];
		for (pc = r->tr_begin.tp_col; pc < r->tr_end.tp_col; pc++) {
			row[pc] = c;
		}
	}
}