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
struct TYPE_4__ {int /*<<< orphan*/  DmaChannelMask; int /*<<< orphan*/  Flags; } ;
struct TYPE_5__ {TYPE_1__ Dma; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 size_t ACPI_EXTRACT_1BIT_FLAG (int /*<<< orphan*/ ,int) ; 
 size_t ACPI_EXTRACT_2BIT_FLAG (int /*<<< orphan*/ ,int) ; 
 size_t ACPI_GET_2BIT_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmBitList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmIndent (scalar_t__) ; 
 int /*<<< orphan*/ * AcpiGbl_BmDecode ; 
 int /*<<< orphan*/ * AcpiGbl_SizDecode ; 
 int /*<<< orphan*/ * AcpiGbl_TypDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmDmaDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("DMA (%s, %s, %s, ",
        AcpiGbl_TypDecode [ACPI_EXTRACT_2BIT_FLAG (Resource->Dma.Flags, 5)],
        AcpiGbl_BmDecode  [ACPI_EXTRACT_1BIT_FLAG (Resource->Dma.Flags, 2)],
        AcpiGbl_SizDecode [ACPI_GET_2BIT_FLAG (Resource->Dma.Flags)]);

    /* Insert a descriptor name */

    AcpiDmDescriptorName ();
    AcpiOsPrintf (")\n");

    AcpiDmIndent (Level + 1);
    AcpiDmBitList (Resource->Dma.DmaChannelMask);
}