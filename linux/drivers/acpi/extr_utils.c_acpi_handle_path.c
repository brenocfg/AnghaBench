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
struct acpi_buffer {char* pointer; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 scalar_t__ AE_OK ; 
 scalar_t__ acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 scalar_t__ in_interrupt () ; 

__attribute__((used)) static char *acpi_handle_path(acpi_handle handle)
{
	struct acpi_buffer buffer = {
		.length = ACPI_ALLOCATE_BUFFER,
		.pointer = NULL
	};

	if (in_interrupt() ||
	    acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer) != AE_OK)
		return NULL;
	return buffer.pointer;
}