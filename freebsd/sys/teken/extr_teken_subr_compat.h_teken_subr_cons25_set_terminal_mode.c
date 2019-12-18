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
struct TYPE_3__ {int /*<<< orphan*/  t_stateflags; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_CONS25 ; 

__attribute__((used)) static void
teken_subr_cons25_set_terminal_mode(teken_t *t, unsigned int mode)
{

	switch (mode) {
	case 0:	/* Switch terminal to xterm. */
		t->t_stateflags &= ~TS_CONS25;
		break;
	case 1: /* Switch terminal to cons25. */
		t->t_stateflags |= TS_CONS25;
		break;
	default:
		break;
	}
}