#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDbDecodeArguments (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * AcpiDsGetCurrentWalkState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_CurrentWalkList ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 

void
AcpiDbDisplayArguments (
    void)
{
    ACPI_WALK_STATE         *WalkState;


    WalkState = AcpiDsGetCurrentWalkState (AcpiGbl_CurrentWalkList);
    if (!WalkState)
    {
        AcpiOsPrintf ("There is no method currently executing\n");
        return;
    }

    AcpiDbDecodeArguments (WalkState);
}