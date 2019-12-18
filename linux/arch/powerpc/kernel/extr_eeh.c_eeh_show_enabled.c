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
 int /*<<< orphan*/  EEH_ENABLED ; 
 int /*<<< orphan*/  EEH_FORCE_DISABLED ; 
 scalar_t__ eeh_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void eeh_show_enabled(void)
{
	if (eeh_has_flag(EEH_FORCE_DISABLED))
		pr_info("EEH: Recovery disabled by kernel parameter.\n");
	else if (eeh_has_flag(EEH_ENABLED))
		pr_info("EEH: Capable adapter found: recovery enabled.\n");
	else
		pr_info("EEH: No capable adapters found: recovery disabled.\n");
}