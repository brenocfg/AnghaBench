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
struct timecounter {int tc_flags; int /*<<< orphan*/  tc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_LAST ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timecounter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int TC_FLAGS_SUSPEND_SAFE ; 
 int /*<<< orphan*/  acpi_timer_dev ; 
 int /*<<< orphan*/ * acpi_timer_eh ; 
 int /*<<< orphan*/  acpi_timer_read () ; 
 int /*<<< orphan*/  acpi_timer_resume_handler ; 
 struct timecounter acpi_timer_timecounter ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_resume ; 
 struct timecounter* timecounter ; 

__attribute__((used)) static void
acpi_timer_suspend_handler(struct timecounter *newtc)
{
	struct timecounter *tc;

	/* Deregister existing resume event handler. */
	if (acpi_timer_eh != NULL) {
		EVENTHANDLER_DEREGISTER(power_resume, acpi_timer_eh);
		acpi_timer_eh = NULL;
	}

	if ((timecounter->tc_flags & TC_FLAGS_SUSPEND_SAFE) != 0) {
		/*
		 * If we are using a suspend safe timecounter, don't
		 * save/restore it across suspend/resume.
		 */
		return;
	}

	KASSERT(newtc == &acpi_timer_timecounter,
	    ("acpi_timer_suspend_handler: wrong timecounter"));

	tc = timecounter;
	if (tc != newtc) {
		if (bootverbose)
			device_printf(acpi_timer_dev,
			    "switching timecounter, %s -> %s\n",
			    tc->tc_name, newtc->tc_name);
		(void)acpi_timer_read();
		(void)acpi_timer_read();
		timecounter = newtc;
		acpi_timer_eh = EVENTHANDLER_REGISTER(power_resume,
		    acpi_timer_resume_handler, tc, EVENTHANDLER_PRI_LAST);
	}
}