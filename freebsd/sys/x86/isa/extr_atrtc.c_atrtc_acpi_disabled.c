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
typedef  int uint16_t ;

/* Variables and functions */
 int ACPI_FADT_NO_CMOS_RTC ; 
 int /*<<< orphan*/  acpi_get_fadt_bootflags (int*) ; 

__attribute__((used)) static bool
atrtc_acpi_disabled(void)
{
#ifdef DEV_ACPI
	uint16_t flags;

	if (!acpi_get_fadt_bootflags(&flags))
		return (false);
	return ((flags & ACPI_FADT_NO_CMOS_RTC) != 0);
#else
	return (false);
#endif
}