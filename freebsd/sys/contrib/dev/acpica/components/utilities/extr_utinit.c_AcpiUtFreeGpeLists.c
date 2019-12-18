#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* Next; struct TYPE_5__* RegisterInfo; struct TYPE_5__* EventInfo; struct TYPE_5__* GpeBlockListHead; } ;
typedef  TYPE_1__ ACPI_GPE_XRUPT_INFO ;
typedef  TYPE_1__ ACPI_GPE_BLOCK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 TYPE_1__* AcpiGbl_GpeXruptListHead ; 

__attribute__((used)) static void
AcpiUtFreeGpeLists (
    void)
{
    ACPI_GPE_BLOCK_INFO     *GpeBlock;
    ACPI_GPE_BLOCK_INFO     *NextGpeBlock;
    ACPI_GPE_XRUPT_INFO     *GpeXruptInfo;
    ACPI_GPE_XRUPT_INFO     *NextGpeXruptInfo;


    /* Free global GPE blocks and related info structures */

    GpeXruptInfo = AcpiGbl_GpeXruptListHead;
    while (GpeXruptInfo)
    {
        GpeBlock = GpeXruptInfo->GpeBlockListHead;
        while (GpeBlock)
        {
            NextGpeBlock = GpeBlock->Next;
            ACPI_FREE (GpeBlock->EventInfo);
            ACPI_FREE (GpeBlock->RegisterInfo);
            ACPI_FREE (GpeBlock);

            GpeBlock = NextGpeBlock;
        }
        NextGpeXruptInfo = GpeXruptInfo->Next;
        ACPI_FREE (GpeXruptInfo);
        GpeXruptInfo = NextGpeXruptInfo;
    }
}