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
typedef  size_t UINT32 ;
struct TYPE_3__ {size_t RegisterCount; int /*<<< orphan*/ * RegisterInfo; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_GPE_XRUPT_INFO ;
typedef  TYPE_1__ ACPI_GPE_BLOCK_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiHwGpeEnableWrite (int,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiHwDisableGpeBlock (
    ACPI_GPE_XRUPT_INFO     *GpeXruptInfo,
    ACPI_GPE_BLOCK_INFO     *GpeBlock,
    void                    *Context)
{
    UINT32                  i;
    ACPI_STATUS             Status;


    /* Examine each GPE Register within the block */

    for (i = 0; i < GpeBlock->RegisterCount; i++)
    {
        /* Disable all GPEs in this register */

        Status = AcpiHwGpeEnableWrite (0x00, &GpeBlock->RegisterInfo[i]);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }

    return (AE_OK);
}