#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_8__ {int /*<<< orphan*/  ts_begin; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_stateflags; TYPE_2__ t_cursor; TYPE_1__ t_scrollreg; TYPE_1__ t_originreg; } ;
typedef  TYPE_3__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TP_132COLS ; 
 int /*<<< orphan*/  TP_AUTOREPEAT ; 
 int /*<<< orphan*/  TP_MOUSE ; 
 int /*<<< orphan*/  TP_SHOWCURSOR ; 
 int /*<<< orphan*/  TS_AUTOWRAP ; 
 int /*<<< orphan*/  TS_CURSORKEYS ; 
 int /*<<< orphan*/  TS_ORIGIN ; 
 int /*<<< orphan*/  TS_WRAPPED ; 
 int /*<<< orphan*/  teken_funcs_cursor (TYPE_3__*) ; 
 int /*<<< orphan*/  teken_funcs_param (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  teken_printf (char*,...) ; 
 int /*<<< orphan*/  teken_subr_reset_to_initial_state (TYPE_3__*) ; 

__attribute__((used)) static void
teken_subr_set_dec_mode(teken_t *t, unsigned int cmd)
{

	switch (cmd) {
	case 1: /* Cursor keys mode. */
		t->t_stateflags |= TS_CURSORKEYS;
		break;
	case 2: /* DECANM: ANSI/VT52 mode. */
		teken_printf("DECSET VT52\n");
		break;
	case 3: /* 132 column mode. */
		teken_funcs_param(t, TP_132COLS, 1);
		teken_subr_reset_to_initial_state(t);
		break;
	case 5: /* Inverse video. */
		teken_printf("DECSET inverse video\n");
		break;
	case 6: /* Origin mode. */
		t->t_stateflags |= TS_ORIGIN;
		t->t_originreg = t->t_scrollreg;
		t->t_cursor.tp_row = t->t_scrollreg.ts_begin;
		t->t_cursor.tp_col = 0;
		t->t_stateflags &= ~TS_WRAPPED;
		teken_funcs_cursor(t);
		break;
	case 7: /* Autowrap mode. */
		t->t_stateflags |= TS_AUTOWRAP;
		break;
	case 8: /* Autorepeat mode. */
		teken_funcs_param(t, TP_AUTOREPEAT, 1);
		break;
	case 25: /* Display cursor. */
		teken_funcs_param(t, TP_SHOWCURSOR, 1);
		break;
	case 40: /* Allow 132 columns. */
		teken_printf("DECSET allow 132\n");
		break;
	case 45: /* Enable reverse wraparound. */
		teken_printf("DECSET reverse wraparound\n");
		break;
	case 47: /* Switch to alternate buffer. */
		teken_printf("Switch away from alternate buffer\n");
		break;
	case 1000: /* Mouse input. */
		teken_funcs_param(t, TP_MOUSE, 1);
		break;
	default:
		teken_printf("Unknown DECSET: %u\n", cmd);
	}
}