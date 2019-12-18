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
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_CTRL_TRUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AcpiDbCommandDispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiGbl_DbLineBuf ; 
 int /*<<< orphan*/  AcpiGbl_MethodExecuting ; 
 scalar_t__ AcpiOsNotifyCommandComplete () ; 
 scalar_t__ AcpiOsWaitCommandReady () ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbStartCommand (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;


    /* TBD: [Investigate] are there namespace locking issues here? */

    /* AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE); */

    /* Go into the command loop and await next user command */


    AcpiGbl_MethodExecuting = TRUE;
    Status = AE_CTRL_TRUE;

    while (Status == AE_CTRL_TRUE)
    {
        /* Notify the completion of the command */

        Status = AcpiOsNotifyCommandComplete ();
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        /* Wait the readiness of the command */

        Status = AcpiOsWaitCommandReady ();
        if (ACPI_FAILURE (Status))
        {
            goto ErrorExit;
        }

        Status = AcpiDbCommandDispatch (AcpiGbl_DbLineBuf, WalkState, Op);
    }

    /* AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE); */

ErrorExit:
    if (ACPI_FAILURE (Status) && Status != AE_CTRL_TERMINATE)
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "While parsing/handling command line"));
    }
    return (Status);
}