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
struct acpi_buffer {scalar_t__ length; int /*<<< orphan*/  pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_ALLOCATE_LOCAL_BUFFER ; 
 scalar_t__ ACPI_NO_BUFFER ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 

acpi_status acpi_ut_validate_buffer(struct acpi_buffer *buffer)
{

	/* Obviously, the structure pointer must be valid */

	if (!buffer) {
		return (AE_BAD_PARAMETER);
	}

	/* Special semantics for the length */

	if ((buffer->length == ACPI_NO_BUFFER) ||
	    (buffer->length == ACPI_ALLOCATE_BUFFER) ||
	    (buffer->length == ACPI_ALLOCATE_LOCAL_BUFFER)) {
		return (AE_OK);
	}

	/* Length is valid, the buffer pointer must be also */

	if (!buffer->pointer) {
		return (AE_BAD_PARAMETER);
	}

	return (AE_OK);
}