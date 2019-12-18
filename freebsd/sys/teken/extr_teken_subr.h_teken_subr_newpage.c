#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_16__ {int /*<<< orphan*/  ts_begin; int /*<<< orphan*/  ts_end; } ;
struct TYPE_15__ {int /*<<< orphan*/  tp_col; } ;
struct TYPE_18__ {int t_stateflags; TYPE_5__ t_cursor; TYPE_4__ t_originreg; int /*<<< orphan*/  t_curattr; TYPE_3__ t_winsize; } ;
typedef  TYPE_6__ teken_t ;
struct TYPE_14__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_13__ {scalar_t__ tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_19__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_7__ teken_rect_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK ; 
 int TS_CONS25 ; 
 int TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_6__*) ; 
 int /*<<< orphan*/  teken_funcs_fill (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_subr_newline (TYPE_6__*) ; 

__attribute__((used)) static void
teken_subr_newpage(teken_t *t)
{

	if (t->t_stateflags & TS_CONS25) {
		teken_rect_t tr;

		/* Clear screen. */
		tr.tr_begin.tp_row = t->t_originreg.ts_begin;
		tr.tr_begin.tp_col = 0;
		tr.tr_end.tp_row = t->t_originreg.ts_end;
		tr.tr_end.tp_col = t->t_winsize.tp_col;
		teken_funcs_fill(t, &tr, BLANK, &t->t_curattr);

		/* Cursor at top left. */
		t->t_cursor.tp_row = t->t_originreg.ts_begin;
		t->t_cursor.tp_col = 0;
		t->t_stateflags &= ~TS_WRAPPED;
		teken_funcs_cursor(t);
	} else {
		teken_subr_newline(t);
	}
}