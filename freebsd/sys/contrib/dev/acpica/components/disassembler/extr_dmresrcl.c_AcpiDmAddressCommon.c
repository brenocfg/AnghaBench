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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int ResourceType; int SpecificFlags; int Flags; } ;
struct TYPE_5__ {TYPE_1__ Address; } ;
typedef  TYPE_2__ AML_RESOURCE ;

/* Variables and functions */
 size_t ACPI_GET_2BIT_FLAG (int) ; 
 int ACPI_IO_RANGE ; 
 int ACPI_MEMORY_RANGE ; 
 int /*<<< orphan*/  AcpiDmAddressPrefix (int) ; 
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmIoFlags (int) ; 
 int /*<<< orphan*/  AcpiDmMemoryFlags (int,int) ; 
 int /*<<< orphan*/  AcpiDmSpaceFlags (int) ; 
 int* AcpiGbl_RngDecode ; 
 int* AcpiGbl_WordDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int) ; 

__attribute__((used)) static void
AcpiDmAddressCommon (
    AML_RESOURCE            *Resource,
    UINT8                   Type,
    UINT32                  Level)
{
    UINT8                   ResourceType;
    UINT8                   SpecificFlags;
    UINT8                   Flags;


    ResourceType = Resource->Address.ResourceType;
    SpecificFlags = Resource->Address.SpecificFlags;
    Flags = Resource->Address.Flags;

    AcpiDmIndent (Level);

    /* Validate ResourceType */

    if ((ResourceType > 2) && (ResourceType < 0xC0))
    {
        AcpiOsPrintf (
            "/**** Invalid Resource Type: 0x%X ****/", ResourceType);
        return;
    }

    /* Prefix is either Word, DWord, QWord, or Extended */

    AcpiDmAddressPrefix (Type);

    /* Resource Types above 0xC0 are vendor-defined */

    if (ResourceType > 2)
    {
        AcpiOsPrintf ("Space (0x%2.2X, ", ResourceType);
        AcpiDmSpaceFlags (Flags);
        AcpiOsPrintf (" 0x%2.2X,", SpecificFlags);
        return;
    }

    /* This is either a Memory, IO, or BusNumber descriptor (0,1,2) */

    AcpiOsPrintf ("%s (",
        AcpiGbl_WordDecode [ACPI_GET_2BIT_FLAG (ResourceType)]);

    /* Decode the general and type-specific flags */

    if (ResourceType == ACPI_MEMORY_RANGE)
    {
        AcpiDmMemoryFlags (Flags, SpecificFlags);
    }
    else /* IO range or BusNumberRange */
    {
        AcpiDmIoFlags (Flags);
        if (ResourceType == ACPI_IO_RANGE)
        {
            AcpiOsPrintf (" %s,",
                AcpiGbl_RngDecode [ACPI_GET_2BIT_FLAG (SpecificFlags)]);
        }
    }
}