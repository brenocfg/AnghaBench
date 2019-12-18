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
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 int acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t acpi_object_path(acpi_handle handle, char *buf)
{
	struct acpi_buffer path = {ACPI_ALLOCATE_BUFFER, NULL};
	int result;

	result = acpi_get_name(handle, ACPI_FULL_PATHNAME, &path);
	if (result)
		return result;

	result = sprintf(buf, "%s\n", (char *)path.pointer);
	kfree(path.pointer);
	return result;
}