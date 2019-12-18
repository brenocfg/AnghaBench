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
struct TYPE_8__ {int /*<<< orphan*/  ta_bgcolor; int /*<<< orphan*/  ta_fgcolor; scalar_t__ ta_format; } ;
struct TYPE_9__ {TYPE_1__ t_defattr; scalar_t__ t_utf8_left; scalar_t__ t_stateflags; int /*<<< orphan*/  t_nextstate; void* t_softc; int /*<<< orphan*/  const* t_funcs; } ;
typedef  TYPE_2__ teken_t ;
struct TYPE_10__ {int tp_row; int tp_col; } ;
typedef  TYPE_3__ teken_pos_t ;
typedef  int /*<<< orphan*/  teken_funcs_t ;

/* Variables and functions */
 int /*<<< orphan*/  TC_BLACK ; 
 int /*<<< orphan*/  TC_WHITE ; 
 int /*<<< orphan*/  teken_set_winsize (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  teken_state_init ; 
 int /*<<< orphan*/  teken_subr_do_reset (TYPE_2__*) ; 

void
teken_init(teken_t *t, const teken_funcs_t *tf, void *softc)
{
	teken_pos_t tp = { .tp_row = 24, .tp_col = 80 };

	t->t_funcs = tf;
	t->t_softc = softc;

	t->t_nextstate = teken_state_init;
	t->t_stateflags = 0;
	t->t_utf8_left = 0;

	t->t_defattr.ta_format = 0;
	t->t_defattr.ta_fgcolor = TC_WHITE;
	t->t_defattr.ta_bgcolor = TC_BLACK;
	teken_subr_do_reset(t);

	teken_set_winsize(t, &tp);
}