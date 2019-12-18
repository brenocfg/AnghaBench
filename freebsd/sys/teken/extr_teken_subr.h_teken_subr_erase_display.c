#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  tp_row; int /*<<< orphan*/  tp_col; } ;
struct TYPE_12__ {int /*<<< orphan*/  tp_row; } ;
struct TYPE_15__ {int /*<<< orphan*/  t_curattr; TYPE_4__ t_winsize; TYPE_2__ t_cursor; } ;
typedef  TYPE_5__ teken_t ;
struct TYPE_13__ {int /*<<< orphan*/  tp_row; int /*<<< orphan*/  tp_col; } ;
struct TYPE_11__ {int /*<<< orphan*/  tp_row; scalar_t__ tp_col; } ;
struct TYPE_16__ {TYPE_3__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_6__ teken_rect_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK ; 
 int /*<<< orphan*/  teken_funcs_fill (TYPE_5__ const*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_subr_erase_line (TYPE_5__ const*,int) ; 

__attribute__((used)) static void
teken_subr_erase_display(const teken_t *t, unsigned int mode)
{
	teken_rect_t r;

	r.tr_begin.tp_col = 0;
	r.tr_end.tp_col = t->t_winsize.tp_col;

	switch (mode) {
	case 1: /* Erase from the top to the cursor. */
		teken_subr_erase_line(t, 1);

		/* Erase lines above. */
		if (t->t_cursor.tp_row == 0)
			return;
		r.tr_begin.tp_row = 0;
		r.tr_end.tp_row = t->t_cursor.tp_row;
		break;
	case 2: /* Erase entire display. */
		r.tr_begin.tp_row = 0;
		r.tr_end.tp_row = t->t_winsize.tp_row;
		break;
	default: /* Erase from cursor to the bottom. */
		teken_subr_erase_line(t, 0);

		/* Erase lines below. */
		if (t->t_cursor.tp_row == t->t_winsize.tp_row - 1)
			return;
		r.tr_begin.tp_row = t->t_cursor.tp_row + 1;
		r.tr_end.tp_row = t->t_winsize.tp_row;
		break;
	}

	teken_funcs_fill(t, &r, BLANK, &t->t_curattr);
}