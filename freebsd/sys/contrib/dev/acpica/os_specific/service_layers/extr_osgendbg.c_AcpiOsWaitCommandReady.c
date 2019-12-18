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
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_LINE_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_COMMAND_PROMPT ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_EXECUTE_PROMPT ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AE_TIME ; 
 int /*<<< orphan*/  AcpiDbSetOutputDestination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_DbCommandReady ; 
 int /*<<< orphan*/  AcpiGbl_DbLineBuf ; 
 scalar_t__ AcpiGbl_DbTerminateLoop ; 
 scalar_t__ AcpiGbl_DebuggerConfiguration ; 
 int /*<<< orphan*/  AcpiGbl_MethodExecuting ; 
 scalar_t__ AcpiOsAcquireMutex (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AcpiOsGetLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEBUGGER_MULTI_THREADED ; 

ACPI_STATUS
AcpiOsWaitCommandReady (
    void)
{
    ACPI_STATUS             Status = AE_OK;


    if (AcpiGbl_DebuggerConfiguration == DEBUGGER_MULTI_THREADED)
    {
        Status = AE_TIME;

        while (Status == AE_TIME)
        {
            if (AcpiGbl_DbTerminateLoop)
            {
                Status = AE_CTRL_TERMINATE;
            }
            else
            {
                Status = AcpiOsAcquireMutex (AcpiGbl_DbCommandReady, 1000);
            }
        }
    }
    else
    {
        /* Force output to console until a command is entered */

        AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);

        /* Different prompt if method is executing */

        if (!AcpiGbl_MethodExecuting)
        {
            AcpiOsPrintf ("%1c ", ACPI_DEBUGGER_COMMAND_PROMPT);
        }
        else
        {
            AcpiOsPrintf ("%1c ", ACPI_DEBUGGER_EXECUTE_PROMPT);
        }

        /* Get the user input line */

        Status = AcpiOsGetLine (AcpiGbl_DbLineBuf,
            ACPI_DB_LINE_BUFFER_SIZE, NULL);
    }

    if (ACPI_FAILURE (Status) && Status != AE_CTRL_TERMINATE)
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "While parsing/handling command line"));
    }
    return (Status);
}