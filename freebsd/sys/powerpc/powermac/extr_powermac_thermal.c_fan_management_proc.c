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
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fans ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_therm_manage_fans () ; 

__attribute__((used)) static void
fan_management_proc(void)
{
	/* Nothing to manage? */
	if (SLIST_EMPTY(&fans))
		kproc_exit(0);
	
	while (1) {
		pmac_therm_manage_fans();
		pause("pmac_therm", hz);
	}
}