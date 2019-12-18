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
typedef  scalar_t__ UINT32 ;
struct TYPE_3__ {scalar_t__ BlockBaseNumber; scalar_t__ GpeCount; int /*<<< orphan*/ * EventInfo; } ;
typedef  int /*<<< orphan*/  ACPI_GPE_EVENT_INFO ;
typedef  TYPE_1__ ACPI_GPE_BLOCK_INFO ;

/* Variables and functions */

ACPI_GPE_EVENT_INFO *
AcpiEvLowGetGpeInfo (
    UINT32                  GpeNumber,
    ACPI_GPE_BLOCK_INFO     *GpeBlock)
{
    UINT32                  GpeIndex;


    /*
     * Validate that the GpeNumber is within the specified GpeBlock.
     * (Two steps)
     */
    if (!GpeBlock ||
        (GpeNumber < GpeBlock->BlockBaseNumber))
    {
        return (NULL);
    }

    GpeIndex = GpeNumber - GpeBlock->BlockBaseNumber;
    if (GpeIndex >= GpeBlock->GpeCount)
    {
        return (NULL);
    }

    return (&GpeBlock->EventInfo[GpeIndex]);
}