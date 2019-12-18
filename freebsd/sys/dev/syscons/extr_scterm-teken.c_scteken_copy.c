#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned int tp_col; int tp_row; } ;
struct TYPE_11__ {int tp_col; unsigned int tp_row; } ;
struct TYPE_13__ {TYPE_2__ tr_begin; TYPE_1__ tr_end; } ;
typedef  TYPE_3__ teken_rect_t ;
struct TYPE_14__ {int tp_row; int tp_col; } ;
typedef  TYPE_4__ teken_pos_t ;
struct TYPE_15__ {int xsize; int /*<<< orphan*/  vtb; int /*<<< orphan*/ * history; } ;
typedef  TYPE_5__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  mark_for_update (TYPE_5__*,int) ; 
 int /*<<< orphan*/  sc_hist_save_one_line (TYPE_5__*,int) ; 
 int /*<<< orphan*/  sc_remove_cutmarking (TYPE_5__*) ; 
 int /*<<< orphan*/  sc_vtb_move (int /*<<< orphan*/ *,int,int,unsigned int) ; 

__attribute__((used)) static void
scteken_copy(void *arg, const teken_rect_t *r, const teken_pos_t *p)
{
	scr_stat *scp = arg;
	unsigned int width;
	int src, dst, end;

#ifndef SC_NO_HISTORY
	/*
	 * We count a line of input as history if we perform a copy of
	 * one whole line upward. In other words: if a line of text gets
	 * overwritten by a rectangle that's right below it.
	 */
	if (scp->history != NULL &&
	    r->tr_begin.tp_col == 0 && r->tr_end.tp_col == scp->xsize &&
	    r->tr_begin.tp_row == p->tp_row + 1) {
		sc_hist_save_one_line(scp, p->tp_row);
	}
#endif

	if (r->tr_begin.tp_col == 0 && r->tr_end.tp_col == scp->xsize) {
		/* Single contiguous region to copy. */
		sc_vtb_move(&scp->vtb, r->tr_begin.tp_row * scp->xsize,
		    p->tp_row * scp->xsize,
		    (r->tr_end.tp_row - r->tr_begin.tp_row) * scp->xsize);
	} else {
		/* Copy line by line. */
		width = r->tr_end.tp_col - r->tr_begin.tp_col;

		if (p->tp_row < r->tr_begin.tp_row) {
			/* Copy from top to bottom. */
			src = r->tr_begin.tp_row * scp->xsize +
			    r->tr_begin.tp_col;
			end = r->tr_end.tp_row * scp->xsize +
			    r->tr_end.tp_col;
			dst = p->tp_row * scp->xsize + p->tp_col;

			while (src < end) {
				sc_vtb_move(&scp->vtb, src, dst, width);

				src += scp->xsize;
				dst += scp->xsize;
			}
		} else {
			/* Copy from bottom to top. */
			src = (r->tr_end.tp_row - 1) * scp->xsize +
			    r->tr_begin.tp_col;
			end = r->tr_begin.tp_row * scp->xsize +
			    r->tr_begin.tp_col;
			dst = (p->tp_row + r->tr_end.tp_row -
			    r->tr_begin.tp_row - 1) * scp->xsize + p->tp_col;

			while (src >= end) {
				sc_vtb_move(&scp->vtb, src, dst, width);

				src -= scp->xsize;
				dst -= scp->xsize;
			}
		}
	}

	/* Mark begin and end positions to be refreshed. */
	mark_for_update(scp,
	    p->tp_row * scp->xsize + p->tp_col);
	mark_for_update(scp,
	    (p->tp_row + r->tr_end.tp_row - r->tr_begin.tp_row - 1) *
	    scp->xsize +
	    (p->tp_col + r->tr_end.tp_col - r->tr_begin.tp_col - 1));
	sc_remove_cutmarking(scp);
}