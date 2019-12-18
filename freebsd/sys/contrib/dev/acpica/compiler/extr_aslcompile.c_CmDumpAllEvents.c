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
struct TYPE_3__ {char* EventName; scalar_t__ StartTime; scalar_t__ EndTime; scalar_t__ Valid; } ;
typedef  TYPE_1__ ASL_EVENT_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_100NSEC_PER_MSEC ; 
 scalar_t__ ACPI_100NSEC_PER_USEC ; 
 scalar_t__ ACPI_USEC_PER_MSEC ; 
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 scalar_t__ AslGbl_CompileTimesFlag ; 
 TYPE_1__* AslGbl_Events ; 
 scalar_t__ AslGbl_NextEvent ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
CmDumpAllEvents (
    void)
{
    ASL_EVENT_INFO          *Event;
    UINT32                  Delta;
    UINT32                  MicroSeconds;
    UINT32                  MilliSeconds;
    UINT32                  i;


    Event = AslGbl_Events;

    DbgPrint (ASL_DEBUG_OUTPUT, "\n\nElapsed time for major events\n\n");
    if (AslGbl_CompileTimesFlag)
    {
        printf ("\nElapsed time for major events\n\n");
    }

    for (i = 0; i < AslGbl_NextEvent; i++)
    {
        if (Event->Valid)
        {
            /* Delta will be in 100-nanosecond units */

            Delta = (UINT32) (Event->EndTime - Event->StartTime);

            MicroSeconds = Delta / ACPI_100NSEC_PER_USEC;
            MilliSeconds = Delta / ACPI_100NSEC_PER_MSEC;

            /* Round milliseconds up */

            if ((MicroSeconds - (MilliSeconds * ACPI_USEC_PER_MSEC)) >= 500)
            {
                MilliSeconds++;
            }

            DbgPrint (ASL_DEBUG_OUTPUT, "%8u usec %8u msec - %s\n",
                MicroSeconds, MilliSeconds, Event->EventName);

            if (AslGbl_CompileTimesFlag)
            {
                printf ("%8u usec %8u msec - %s\n",
                    MicroSeconds, MilliSeconds, Event->EventName);
            }
        }

        Event++;
    }
}