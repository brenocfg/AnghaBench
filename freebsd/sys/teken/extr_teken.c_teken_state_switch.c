#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  t_stateflags; scalar_t__ t_curnum; int /*<<< orphan*/ * t_nextstate; } ;
typedef  TYPE_1__ teken_t ;
typedef  int /*<<< orphan*/  teken_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_FIRSTDIGIT ; 

__attribute__((used)) static void
teken_state_switch(teken_t *t, teken_state_t *s)
{

	t->t_nextstate = s;
	t->t_curnum = 0;
	t->t_stateflags |= TS_FIRSTDIGIT;
}