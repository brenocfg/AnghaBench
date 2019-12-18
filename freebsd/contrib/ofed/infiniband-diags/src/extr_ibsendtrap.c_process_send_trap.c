#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  build_func; scalar_t__ trap_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 int send_trap (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 TYPE_1__* traps ; 

int process_send_trap(char *trap_name)
{
	int i;

	for (i = 0; traps[i].trap_name; i++)
		if (strcmp(traps[i].trap_name, trap_name) == 0)
			return send_trap(traps[i].build_func);
	ibdiag_show_usage();
	return 1;
}