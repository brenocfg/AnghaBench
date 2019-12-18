#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* GpeBlockListHead; } ;
struct TYPE_11__ {struct TYPE_11__* EventInfo; struct TYPE_11__* RegisterInfo; scalar_t__ GpeCount; TYPE_2__* Previous; TYPE_1__* Next; TYPE_4__* XruptBlock; } ;
struct TYPE_10__ {TYPE_1__* Next; } ;
struct TYPE_9__ {TYPE_2__* Previous; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_GPE_BLOCK_INFO ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_3__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_EVENTS ; 
 int /*<<< orphan*/  AcpiCurrentGpeCount ; 
 int /*<<< orphan*/  AcpiEvDeleteGpeXrupt (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiGbl_GpeLock ; 
 int /*<<< orphan*/  AcpiHwDisableGpeBlock (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvInstallGpeBlock ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvDeleteGpeBlock (
    ACPI_GPE_BLOCK_INFO     *GpeBlock)
{
    ACPI_STATUS             Status;
    ACPI_CPU_FLAGS          Flags;


    ACPI_FUNCTION_TRACE (EvInstallGpeBlock);


    Status = AcpiUtAcquireMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Disable all GPEs in this block */

    Status = AcpiHwDisableGpeBlock (GpeBlock->XruptBlock, GpeBlock, NULL);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (!GpeBlock->Previous && !GpeBlock->Next)
    {
        /* This is the last GpeBlock on this interrupt */

        Status = AcpiEvDeleteGpeXrupt (GpeBlock->XruptBlock);
        if (ACPI_FAILURE (Status))
        {
            goto UnlockAndExit;
        }
    }
    else
    {
        /* Remove the block on this interrupt with lock */

        Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);
        if (GpeBlock->Previous)
        {
            GpeBlock->Previous->Next = GpeBlock->Next;
        }
        else
        {
            GpeBlock->XruptBlock->GpeBlockListHead = GpeBlock->Next;
        }

        if (GpeBlock->Next)
        {
            GpeBlock->Next->Previous = GpeBlock->Previous;
        }

        AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);
    }

    AcpiCurrentGpeCount -= GpeBlock->GpeCount;

    /* Free the GpeBlock */

    ACPI_FREE (GpeBlock->RegisterInfo);
    ACPI_FREE (GpeBlock->EventInfo);
    ACPI_FREE (GpeBlock);

UnlockAndExit:
    Status = AcpiUtReleaseMutex (ACPI_MTX_EVENTS);
    return_ACPI_STATUS (Status);
}