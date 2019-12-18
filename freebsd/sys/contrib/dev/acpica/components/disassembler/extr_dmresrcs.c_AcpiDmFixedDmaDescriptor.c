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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int Width; int /*<<< orphan*/  Channels; int /*<<< orphan*/  RequestLines; } ;
struct TYPE_5__ {TYPE_1__ FixedDma; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmDescriptorName () ; 
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AcpiGbl_DtsDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmFixedDmaDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    AcpiDmIndent (Level);
    AcpiOsPrintf ("FixedDMA (0x%4.4X, 0x%4.4X, ",
        Resource->FixedDma.RequestLines,
        Resource->FixedDma.Channels);

    if (Resource->FixedDma.Width <= 5)
    {
        AcpiOsPrintf ("%s, ",
            AcpiGbl_DtsDecode [Resource->FixedDma.Width]);
    }
    else
    {
        AcpiOsPrintf ("%X /* INVALID DMA WIDTH */, ",
            Resource->FixedDma.Width);
    }

    /* Insert a descriptor name */

    AcpiDmDescriptorName ();
    AcpiOsPrintf (")\n");
}