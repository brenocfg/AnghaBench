#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  BootFlags; } ;
typedef  TYPE_1__ ACPI_TABLE_FADT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_FADT ; 
 scalar_t__ acpi_find_table (int /*<<< orphan*/ ) ; 
 TYPE_1__* acpi_map_table (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_1__*) ; 

bool
acpi_get_fadt_bootflags(uint16_t *flagsp)
{
#ifdef DEV_ACPI
	ACPI_TABLE_FADT *fadt;
	vm_paddr_t physaddr;

	physaddr = acpi_find_table(ACPI_SIG_FADT);
	if (physaddr == 0)
		return (false);
	fadt = acpi_map_table(physaddr, ACPI_SIG_FADT);
	if (fadt == NULL)
		return (false);
	*flagsp = fadt->BootFlags;
	acpi_unmap_table(fadt);
	return (true);
#else
	return (false);
#endif
}