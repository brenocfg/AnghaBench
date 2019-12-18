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
struct acpi_resource_source {int index; char* string_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  acpi_rs_out_integer8 (char*,int) ; 
 int /*<<< orphan*/  acpi_rs_out_string (char*,char*) ; 

__attribute__((used)) static void
acpi_rs_dump_resource_source(struct acpi_resource_source *resource_source)
{
	ACPI_FUNCTION_ENTRY();

	if (resource_source->index == 0xFF) {
		return;
	}

	acpi_rs_out_integer8("Resource Source Index", resource_source->index);

	acpi_rs_out_string("Resource Source",
			   resource_source->string_ptr ?
			   resource_source->string_ptr : "[Not Specified]");
}