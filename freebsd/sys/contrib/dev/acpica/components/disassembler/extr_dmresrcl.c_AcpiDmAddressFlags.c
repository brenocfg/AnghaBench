#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ResourceType; int /*<<< orphan*/  SpecificFlags; } ;
struct TYPE_5__ {TYPE_1__ Address; } ;
typedef  TYPE_2__ AML_RESOURCE ;

/* Variables and functions */
 scalar_t__ ACPI_IO_RANGE ; 
 scalar_t__ ACPI_MEMORY_RANGE ; 
 int /*<<< orphan*/  AcpiDmIoFlags2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmMemoryFlags2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AcpiDmAddressFlags (
    AML_RESOURCE            *Resource)
{

    if (Resource->Address.ResourceType == ACPI_IO_RANGE)
    {
        AcpiDmIoFlags2 (Resource->Address.SpecificFlags);
    }
    else if (Resource->Address.ResourceType == ACPI_MEMORY_RANGE)
    {
        AcpiDmMemoryFlags2 (Resource->Address.SpecificFlags);
    }
}