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
struct TYPE_14__ {int /*<<< orphan*/  tp_row; } ;
struct TYPE_12__ {int /*<<< orphan*/  ts_end; scalar_t__ ts_begin; } ;
struct TYPE_11__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_15__ {int t_stateflags; int /*<<< orphan*/  t_defattr; TYPE_4__ t_winsize; TYPE_2__ t_scrollreg; TYPE_2__ t_originreg; TYPE_1__ t_cursor; } ;
typedef  TYPE_5__ teken_t ;
struct TYPE_13__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_16__ {TYPE_4__ tr_end; TYPE_3__ tr_begin; } ;
typedef  TYPE_6__ teken_rect_t ;

/* Variables and functions */
 int TS_ORIGIN ; 
 int TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_5__*) ; 
 int /*<<< orphan*/  teken_funcs_fill (TYPE_5__*,TYPE_6__*,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
teken_subr_alignment_test(teken_t *t)
{
	teken_rect_t tr;

	t->t_cursor.tp_row = t->t_cursor.tp_col = 0;
	t->t_scrollreg.ts_begin = 0;
	t->t_scrollreg.ts_end = t->t_winsize.tp_row;
	t->t_originreg = t->t_scrollreg;
	t->t_stateflags &= ~(TS_WRAPPED|TS_ORIGIN);
	teken_funcs_cursor(t);

	tr.tr_begin.tp_row = 0;
	tr.tr_begin.tp_col = 0;
	tr.tr_end = t->t_winsize;
	teken_funcs_fill(t, &tr, 'E', &t->t_defattr);
}