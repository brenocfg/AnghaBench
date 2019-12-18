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
 int ACPI_FADT_NO_VGA ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  acpi_get_fadt_bootflags (int*) ; 

__attribute__((used)) static bool
vga_acpi_disabled(void)
{
#if defined(__amd64__) || defined(__i386__)
	uint16_t flags;
	int ignore;

	ignore = 0;
	TUNABLE_INT_FETCH("hw.vga.acpi_ignore_no_vga", &ignore);
	if (ignore || !acpi_get_fadt_bootflags(&flags))
 		return (false);
	return ((flags & ACPI_FADT_NO_VGA) != 0);
#else
	return (false);
#endif
}