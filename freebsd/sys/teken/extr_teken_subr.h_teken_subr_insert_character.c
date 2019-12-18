#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_13__ {scalar_t__ tp_col; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_curattr; TYPE_3__ t_cursor; TYPE_1__ t_winsize; } ;
typedef  TYPE_4__ teken_t ;
struct TYPE_14__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_17__ {TYPE_2__ tr_end; TYPE_3__ tr_begin; } ;
typedef  TYPE_5__ teken_rect_t ;
struct TYPE_18__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
typedef  TYPE_6__ teken_pos_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK ; 
 int /*<<< orphan*/  teken_funcs_copy (TYPE_4__ const*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  teken_funcs_fill (TYPE_4__ const*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
teken_subr_insert_character(const teken_t *t, unsigned int ncols)
{
	teken_rect_t tr;

	tr.tr_begin = t->t_cursor;
	tr.tr_end.tp_row = t->t_cursor.tp_row + 1;

	if (t->t_cursor.tp_col + ncols >= t->t_winsize.tp_col) {
		tr.tr_end.tp_col = t->t_winsize.tp_col;
	} else {
		teken_pos_t tp;

		/* Copy characters to the right. */
		tr.tr_end.tp_col = t->t_winsize.tp_col - ncols;
		tp.tp_row = t->t_cursor.tp_row;
		tp.tp_col = t->t_cursor.tp_col + ncols;
		teken_funcs_copy(t, &tr, &tp);

		tr.tr_end.tp_col = t->t_cursor.tp_col + ncols;
	}

	/* Blank current location. */
	teken_funcs_fill(t, &tr, BLANK, &t->t_curattr);
}