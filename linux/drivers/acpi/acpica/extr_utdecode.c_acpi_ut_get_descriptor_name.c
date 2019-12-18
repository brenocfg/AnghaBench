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
 size_t ACPI_DESC_TYPE_MAX ; 
 size_t ACPI_GET_DESCRIPTOR_TYPE (void*) ; 
 char const** acpi_gbl_desc_type_names ; 

const char *acpi_ut_get_descriptor_name(void *object)
{

	if (!object) {
		return ("NULL OBJECT");
	}

	if (ACPI_GET_DESCRIPTOR_TYPE(object) > ACPI_DESC_TYPE_MAX) {
		return ("Not a Descriptor");
	}

	return (acpi_gbl_desc_type_names[ACPI_GET_DESCRIPTOR_TYPE(object)]);
}