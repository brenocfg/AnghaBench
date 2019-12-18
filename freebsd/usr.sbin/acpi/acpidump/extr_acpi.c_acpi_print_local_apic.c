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
typedef  int uint32_t ;

/* Variables and functions */
 int ACPI_MADT_ENABLED ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_print_local_apic(uint32_t apic_id, uint32_t flags)
{

	printf("\tFlags={");
	if (flags & ACPI_MADT_ENABLED)
		printf("ENABLED");
	else
		printf("DISABLED");
	printf("}\n");
	printf("\tAPIC ID=%d\n", apic_id);
}