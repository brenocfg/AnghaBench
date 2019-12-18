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
struct TYPE_2__ {int /*<<< orphan*/  (* func ) (int,char**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* commands ; 
 size_t ncmds ; 
 int /*<<< orphan*/  report_status (char*) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 

void
command_execute(char *func, int nargs, char **args)
{
	size_t i;

	i = 0;
	while (i < ncmds) {
		if (strcasecmp(func, commands[i].name) == 0) {
			/* matched function */
			commands[i].func(nargs, args);
			return;
		}
		i++;
	}

	report_status("UNKNOWN_FUNCTION");
}