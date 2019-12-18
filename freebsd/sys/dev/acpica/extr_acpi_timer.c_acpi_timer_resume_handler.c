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
struct timecounter {int /*<<< orphan*/  (* tc_get_timecount ) (struct timecounter*) ;int /*<<< orphan*/  tc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_timer_dev ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct timecounter*) ; 
 int /*<<< orphan*/  stub2 (struct timecounter*) ; 
 struct timecounter* timecounter ; 

__attribute__((used)) static void
acpi_timer_resume_handler(struct timecounter *newtc)
{
	struct timecounter *tc;

	tc = timecounter;
	if (tc != newtc) {
		if (bootverbose)
			device_printf(acpi_timer_dev,
			    "restoring timecounter, %s -> %s\n",
			    tc->tc_name, newtc->tc_name);
		(void)newtc->tc_get_timecount(newtc);
		(void)newtc->tc_get_timecount(newtc);
		timecounter = newtc;
	}
}