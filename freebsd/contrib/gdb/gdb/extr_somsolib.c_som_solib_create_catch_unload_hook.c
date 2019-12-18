#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  create_solib_unload_event_breakpoint (char*,int,char*,char*) ; 

void
som_solib_create_catch_unload_hook (int pid, int tempflag, char *filename,
				    char *cond_string)
{
  create_solib_unload_event_breakpoint ("__d_trap", tempflag, filename, cond_string);
}