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
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {scalar_t__ AccessSize; int /*<<< orphan*/  Address; int /*<<< orphan*/  BitOffset; int /*<<< orphan*/  BitWidth; int /*<<< orphan*/  AddressSpaceId; } ;
struct TYPE_5__ {TYPE_1__ GenericReg; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmAddressSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmDumpInteger64 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AcpiDmDumpInteger8 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AcpiDmIndent (scalar_t__) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmGenericRegisterDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Register (");
    AcpiDmAddressSpace (Resource->GenericReg.AddressSpaceId);
    AcpiOsPrintf ("\n");

    AcpiDmIndent (Level + 1);
    AcpiDmDumpInteger8 (Resource->GenericReg.BitWidth, "Bit Width");

    AcpiDmIndent (Level + 1);
    AcpiDmDumpInteger8 (Resource->GenericReg.BitOffset, "Bit Offset");

    AcpiDmIndent (Level + 1);
    AcpiDmDumpInteger64 (Resource->GenericReg.Address, "Address");

    /* Optional field for ACPI 3.0 */

    AcpiDmIndent (Level + 1);
    if (Resource->GenericReg.AccessSize)
    {
        AcpiOsPrintf ("0x%2.2X,               // %s\n",
            Resource->GenericReg.AccessSize, "Access Size");
        AcpiDmIndent (Level + 1);
    }
    else
    {
        AcpiOsPrintf (",");
    }

    /* DescriptorName was added for ACPI 3.0+ */

    AcpiDmDescriptorName ();
    AcpiOsPrintf (")\n");
}