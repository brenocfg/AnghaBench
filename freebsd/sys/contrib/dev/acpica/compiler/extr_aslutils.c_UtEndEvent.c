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
struct TYPE_2__ {int /*<<< orphan*/  EndTime; } ;

/* Variables and functions */
 size_t ASL_NUM_EVENTS ; 
 int /*<<< orphan*/  AcpiOsGetTimer () ; 
 TYPE_1__* AslGbl_Events ; 

void
UtEndEvent (
    UINT8                   Event)
{

    if (Event >= ASL_NUM_EVENTS)
    {
        return;
    }

    /* Insert end time for event */

    AslGbl_Events[Event].EndTime = AcpiOsGetTimer ();
}