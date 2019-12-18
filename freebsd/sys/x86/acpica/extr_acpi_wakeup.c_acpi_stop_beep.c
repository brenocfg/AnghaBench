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
 scalar_t__ acpi_resume_beep ; 
 int /*<<< orphan*/  timer_spkr_release () ; 

__attribute__((used)) static void
acpi_stop_beep(void *arg)
{

	if (acpi_resume_beep != 0)
		timer_spkr_release();
}