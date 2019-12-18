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
struct TYPE_4__ {int /*<<< orphan*/  Minimum; int /*<<< orphan*/  Flags; } ;
struct TYPE_5__ {TYPE_1__ Memory24; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 size_t ACPI_GET_1BIT_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmIndent (scalar_t__) ; 
 int /*<<< orphan*/  AcpiDmMemoryFields (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/ * AcpiGbl_RwDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmMemory24Descriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    /* Dump name and read/write flag */

    AcpiDmIndent (Level);
    AcpiOsPrintf ("Memory24 (%s,\n",
        AcpiGbl_RwDecode [ACPI_GET_1BIT_FLAG (Resource->Memory24.Flags)]);

    /* Dump the 4 contiguous WORD values */

    AcpiDmMemoryFields (&Resource->Memory24.Minimum, 16, Level);

    /* Insert a descriptor name */

    AcpiDmIndent (Level + 1);
    AcpiDmDescriptorName ();
    AcpiOsPrintf (")\n");
}