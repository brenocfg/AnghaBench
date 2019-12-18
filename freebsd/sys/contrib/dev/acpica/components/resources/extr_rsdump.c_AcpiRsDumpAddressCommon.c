#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_5__ {int ResourceType; } ;
struct TYPE_6__ {TYPE_1__ Address; } ;
typedef  TYPE_2__ ACPI_RESOURCE_DATA ;

/* Variables and functions */
#define  ACPI_BUS_NUMBER_RANGE 130 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
#define  ACPI_IO_RANGE 129 
#define  ACPI_MEMORY_RANGE 128 
 int /*<<< orphan*/  AcpiRsDumpDescriptor (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRsDumpGeneralFlags ; 
 int /*<<< orphan*/  AcpiRsDumpIoFlags ; 
 int /*<<< orphan*/  AcpiRsDumpMemoryFlags ; 
 int /*<<< orphan*/  AcpiRsOutInteger8 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRsOutString (char*,char*) ; 

__attribute__((used)) static void
AcpiRsDumpAddressCommon (
    ACPI_RESOURCE_DATA      *Resource)
{
    ACPI_FUNCTION_ENTRY ();


   /* Decode the type-specific flags */

    switch (Resource->Address.ResourceType)
    {
    case ACPI_MEMORY_RANGE:

        AcpiRsDumpDescriptor (Resource, AcpiRsDumpMemoryFlags);
        break;

    case ACPI_IO_RANGE:

        AcpiRsDumpDescriptor (Resource, AcpiRsDumpIoFlags);
        break;

    case ACPI_BUS_NUMBER_RANGE:

        AcpiRsOutString ("Resource Type", "Bus Number Range");
        break;

    default:

        AcpiRsOutInteger8 ("Resource Type",
            (UINT8) Resource->Address.ResourceType);
        break;
    }

    /* Decode the general flags */

    AcpiRsDumpDescriptor (Resource, AcpiRsDumpGeneralFlags);
}