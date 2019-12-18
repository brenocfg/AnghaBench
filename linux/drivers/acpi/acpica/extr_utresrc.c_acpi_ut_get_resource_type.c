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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_GET8 (void*) ; 
 int ACPI_RESOURCE_NAME_LARGE ; 
 int ACPI_RESOURCE_NAME_SMALL_MASK ; 

u8 acpi_ut_get_resource_type(void *aml)
{
	ACPI_FUNCTION_ENTRY();

	/*
	 * Byte 0 contains the descriptor name (Resource Type)
	 * Examine the large/small bit in the resource header
	 */
	if (ACPI_GET8(aml) & ACPI_RESOURCE_NAME_LARGE) {

		/* Large Resource Type -- bits 6:0 contain the name */

		return (ACPI_GET8(aml));
	} else {
		/* Small Resource Type -- bits 6:3 contain the name */

		return ((u8) (ACPI_GET8(aml) & ACPI_RESOURCE_NAME_SMALL_MASK));
	}
}