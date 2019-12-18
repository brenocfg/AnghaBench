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
struct TYPE_2__ {int Length; int Type; } ;
typedef  TYPE_1__ ACPI_DMAR_HEADER ;

/* Variables and functions */
#define  ACPI_DMAR_TYPE_HARDWARE_UNIT 128 
 int /*<<< orphan*/  acpi_handle_dmar_drhd (void*) ; 

__attribute__((used)) static int
acpi_handle_dmar_remapping_structure(void *addr, int remaining)
{
	ACPI_DMAR_HEADER *hdr = addr;

	if (remaining < (int)sizeof(ACPI_DMAR_HEADER))
		return (-1);

	if (remaining < hdr->Length)
		return (-1);

	switch (hdr->Type) {
	case ACPI_DMAR_TYPE_HARDWARE_UNIT:
		acpi_handle_dmar_drhd(addr);
		break;
	}
	return (hdr->Length);
}