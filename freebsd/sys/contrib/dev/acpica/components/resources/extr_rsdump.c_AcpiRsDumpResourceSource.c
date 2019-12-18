#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Index; char* StringPtr; } ;
typedef  TYPE_1__ ACPI_RESOURCE_SOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int /*<<< orphan*/  AcpiRsOutInteger8 (char*,int) ; 
 int /*<<< orphan*/  AcpiRsOutString (char*,char*) ; 

__attribute__((used)) static void
AcpiRsDumpResourceSource (
    ACPI_RESOURCE_SOURCE    *ResourceSource)
{
    ACPI_FUNCTION_ENTRY ();


    if (ResourceSource->Index == 0xFF)
    {
        return;
    }

    AcpiRsOutInteger8 ("Resource Source Index",
        ResourceSource->Index);

    AcpiRsOutString ("Resource Source",
        ResourceSource->StringPtr ?
            ResourceSource->StringPtr : "[Not Specified]");
}