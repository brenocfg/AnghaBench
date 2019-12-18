#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ts_end; scalar_t__ ts_begin; } ;
struct TYPE_9__ {int /*<<< orphan*/  tp_row; } ;
struct TYPE_8__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_11__ {int t_stateflags; scalar_t__ t_curscs; void** t_scs; TYPE_3__ t_scrollreg; TYPE_3__ t_originreg; TYPE_2__ t_winsize; TYPE_1__ t_cursor; int /*<<< orphan*/  t_defattr; int /*<<< orphan*/  t_curattr; } ;
typedef  TYPE_4__ teken_t ;

/* Variables and functions */
 int TS_8BIT ; 
 int TS_AUTOWRAP ; 
 int TS_CONS25 ; 
 int TS_CONS25KEYS ; 
 void* teken_scs_us_ascii ; 
 int /*<<< orphan*/  teken_subr_save_cursor (TYPE_4__*) ; 
 int /*<<< orphan*/  teken_tab_default (TYPE_4__*) ; 

__attribute__((used)) static void
teken_subr_do_reset(teken_t *t)
{

	t->t_curattr = t->t_defattr;
	t->t_cursor.tp_row = t->t_cursor.tp_col = 0;
	t->t_scrollreg.ts_begin = 0;
	t->t_scrollreg.ts_end = t->t_winsize.tp_row;
	t->t_originreg = t->t_scrollreg;
	t->t_stateflags &= TS_8BIT | TS_CONS25 | TS_CONS25KEYS;
	t->t_stateflags |= TS_AUTOWRAP;

	t->t_scs[0] = teken_scs_us_ascii;
	t->t_scs[1] = teken_scs_us_ascii;
	t->t_curscs = 0;

	teken_subr_save_cursor(t);
	teken_tab_default(t);
}