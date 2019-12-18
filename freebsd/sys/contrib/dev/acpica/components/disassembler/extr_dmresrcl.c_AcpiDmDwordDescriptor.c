#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  Granularity; } ;
struct TYPE_8__ {TYPE_1__ Address32; } ;
typedef  int /*<<< orphan*/  AML_RESOURCE_ADDRESS32 ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RESOURCE_TYPE_ADDRESS32 ; 
 int /*<<< orphan*/  AcpiDmAddressCommon (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmAddressFields (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmAddressFlags (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmResourceSource (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 

void
AcpiDmDwordDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    /* Dump resource name and flags */

    AcpiDmAddressCommon (Resource, ACPI_RESOURCE_TYPE_ADDRESS32, Level);

    /* Dump the 5 contiguous DWORD values */

    AcpiDmAddressFields (&Resource->Address32.Granularity, 32, Level);

    /* The ResourceSource fields are optional */

    AcpiDmIndent (Level + 1);
    AcpiDmResourceSource (Resource, sizeof (AML_RESOURCE_ADDRESS32), Length);

    /* Insert a descriptor name */

    AcpiDmDescriptorName ();

    /* Type-specific flags */

    AcpiDmAddressFlags (Resource);
    AcpiOsPrintf (")\n");
}