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
 int /*<<< orphan*/ * cpus_load_timer ; 
 int /*<<< orphan*/  free_proc_table () ; 
 int /*<<< orphan*/  timer_stop (int /*<<< orphan*/ *) ; 

void
fini_processor_tbl(void)
{

	if (cpus_load_timer != NULL) {
		timer_stop(cpus_load_timer);
		cpus_load_timer = NULL;
	}

	free_proc_table();
}