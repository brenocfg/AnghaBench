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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */

__attribute__((used)) static acpi_size
acpi_ut_bound_string_length(const char *string, acpi_size count)
{
	u32 length = 0;

	while (*string && count) {
		length++;
		string++;
		count--;
	}

	return (length);
}