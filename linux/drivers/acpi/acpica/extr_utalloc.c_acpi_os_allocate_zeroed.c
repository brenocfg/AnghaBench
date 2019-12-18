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
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 void* acpi_os_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *acpi_os_allocate_zeroed(acpi_size size)
{
	void *allocation;

	ACPI_FUNCTION_ENTRY();

	allocation = acpi_os_allocate(size);
	if (allocation) {

		/* Clear the memory block */

		memset(allocation, 0, size);
	}

	return (allocation);
}