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
struct TYPE_6__ {int /*<<< orphan*/  ts_end; scalar_t__ ts_begin; } ;
struct TYPE_5__ {int /*<<< orphan*/  tp_row; } ;
struct TYPE_7__ {TYPE_2__ t_scrollreg; TYPE_2__ t_originreg; TYPE_1__ t_winsize; } ;
typedef  TYPE_3__ teken_t ;

/* Variables and functions */

__attribute__((used)) static void
teken_subr_do_resize(teken_t *t)
{

	t->t_scrollreg.ts_begin = 0;
	t->t_scrollreg.ts_end = t->t_winsize.tp_row;
	t->t_originreg = t->t_scrollreg;
}