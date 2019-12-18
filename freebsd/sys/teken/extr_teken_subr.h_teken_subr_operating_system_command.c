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
 int /*<<< orphan*/  TS_INSTRING ; 
 int /*<<< orphan*/  teken_printf (char*) ; 

__attribute__((used)) static void
teken_subr_operating_system_command(teken_t *t)
{

	teken_printf("Unsupported operating system command\n");
	t->t_stateflags |= TS_INSTRING;
}