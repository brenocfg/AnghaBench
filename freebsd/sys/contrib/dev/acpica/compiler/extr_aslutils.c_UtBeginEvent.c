#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT8 ;
struct TYPE_2__ {char* EventName; int /*<<< orphan*/  Valid; int /*<<< orphan*/  StartTime; } ;

/* Variables and functions */
 size_t ASL_NUM_EVENTS ; 
 int /*<<< orphan*/  AcpiOsGetTimer () ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 TYPE_1__* AslGbl_Events ; 
 size_t AslGbl_NextEvent ; 
 int /*<<< orphan*/  TRUE ; 

UINT8
UtBeginEvent (
    char                    *Name)
{

    if (AslGbl_NextEvent >= ASL_NUM_EVENTS)
    {
        AcpiOsPrintf ("Ran out of compiler event structs!\n");
        return (AslGbl_NextEvent);
    }

    /* Init event with current (start) time */

    AslGbl_Events[AslGbl_NextEvent].StartTime = AcpiOsGetTimer ();
    AslGbl_Events[AslGbl_NextEvent].EventName = Name;
    AslGbl_Events[AslGbl_NextEvent].Valid = TRUE;
    return (AslGbl_NextEvent++);
}