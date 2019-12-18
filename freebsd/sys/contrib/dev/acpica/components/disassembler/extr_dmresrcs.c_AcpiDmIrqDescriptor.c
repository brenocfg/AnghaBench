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
typedef  int UINT32 ;
struct TYPE_4__ {int Flags; int /*<<< orphan*/  IrqMask; } ;
struct TYPE_5__ {TYPE_1__ Irq; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 size_t ACPI_EXTRACT_1BIT_FLAG (int,int) ; 
 size_t ACPI_EXTRACT_2BIT_FLAG (int,int) ; 
 size_t ACPI_GET_1BIT_FLAG (int) ; 
 int /*<<< orphan*/  AcpiDmBitList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmIndent (int) ; 
 int /*<<< orphan*/ * AcpiGbl_HeDecode ; 
 int /*<<< orphan*/ * AcpiGbl_IrqDecode ; 
 int /*<<< orphan*/ * AcpiGbl_LlDecode ; 
 int /*<<< orphan*/ * AcpiGbl_ShrDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmIrqDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("%s (",
        AcpiGbl_IrqDecode [ACPI_GET_1BIT_FLAG (Length)]);

    /* Decode flags byte if present */

    if (Length & 1)
    {
        AcpiOsPrintf ("%s, %s, %s, ",
            AcpiGbl_HeDecode [ACPI_GET_1BIT_FLAG (Resource->Irq.Flags)],
            AcpiGbl_LlDecode [ACPI_EXTRACT_1BIT_FLAG (Resource->Irq.Flags, 3)],
            AcpiGbl_ShrDecode [ACPI_EXTRACT_2BIT_FLAG (Resource->Irq.Flags, 4)]);
    }

    /* Insert a descriptor name */

    AcpiDmDescriptorName ();
    AcpiOsPrintf (")\n");

    AcpiDmIndent (Level + 1);
    AcpiDmBitList (Resource->Irq.IrqMask);
}