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
 int /*<<< orphan*/  TS_INSERT ; 
 int /*<<< orphan*/  teken_printf (char*,unsigned int) ; 

__attribute__((used)) static void
teken_subr_reset_mode(teken_t *t, unsigned int cmd)
{

	switch (cmd) {
	case 4:
		t->t_stateflags &= ~TS_INSERT;
		break;
	default:
		teken_printf("Unknown reset mode: %u\n", cmd);
	}
}