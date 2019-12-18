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
struct acpi_resource_source {scalar_t__ string_length; scalar_t__ string_ptr; } ;
typedef  int /*<<< orphan*/  acpi_rs_length ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 

__attribute__((used)) static acpi_rs_length
acpi_rs_struct_option_length(struct acpi_resource_source *resource_source)
{
	ACPI_FUNCTION_ENTRY();

	/*
	 * If the resource_source string is valid, return the size of the string
	 * (string_length includes the NULL terminator) plus the size of the
	 * resource_source_index (1).
	 */
	if (resource_source->string_ptr) {
		return ((acpi_rs_length)(resource_source->string_length + 1));
	}

	return (0);
}