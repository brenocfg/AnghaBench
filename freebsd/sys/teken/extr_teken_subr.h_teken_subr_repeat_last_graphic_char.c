#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int tp_row; unsigned int tp_col; } ;
struct TYPE_6__ {scalar_t__ t_last; TYPE_1__ t_winsize; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_subr_regular_character (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
teken_subr_repeat_last_graphic_char(teken_t *t, unsigned int rpts)
{
	unsigned int max_repetitions;

	max_repetitions = t->t_winsize.tp_row * t->t_winsize.tp_col;
	if (rpts > max_repetitions)
		rpts = max_repetitions;
	for (; t->t_last != 0 && rpts > 0; rpts--)
		teken_subr_regular_character(t, t->t_last);
}