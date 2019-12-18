#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* pointer; } ;
union acpi_object {TYPE_1__ string; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

acpi_status
acpi_bus_get_ejd(acpi_handle handle, acpi_handle *ejd)
{
	acpi_status status;
	acpi_handle tmp;
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
	union acpi_object *obj;

	status = acpi_get_handle(handle, "_EJD", &tmp);
	if (ACPI_FAILURE(status))
		return status;

	status = acpi_evaluate_object(handle, "_EJD", NULL, &buffer);
	if (ACPI_SUCCESS(status)) {
		obj = buffer.pointer;
		status = acpi_get_handle(ACPI_ROOT_OBJECT, obj->string.pointer,
					 ejd);
		kfree(buffer.pointer);
	}
	return status;
}