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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_LINE_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_COMMAND_PROMPT ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_EXECUTE_PROMPT ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AcpiDbSetOutputDestination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_DbCommandComplete ; 
 int /*<<< orphan*/  AcpiGbl_DbCommandReady ; 
 int /*<<< orphan*/  AcpiGbl_DbLineBuf ; 
 int /*<<< orphan*/  AcpiGbl_DbTerminateLoop ; 
 int /*<<< orphan*/  AcpiGbl_MethodExecuting ; 
 int /*<<< orphan*/  AcpiOsAcquireMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsGetLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtSafeStrncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AcpiDbRunRemoteDebugger (
    char                    *BatchBuffer)
{
    ACPI_STATUS             Status;
    char                    *Ptr = BatchBuffer;
    char                    *Cmd = Ptr;


    while (!AcpiGbl_DbTerminateLoop)
    {
        if (BatchBuffer)
        {
            if (*Ptr)
            {
                while (*Ptr)
                {
                    if (*Ptr == ',')
                    {
                        /* Convert commas to spaces */
                        *Ptr = ' ';
                    }
                    else if (*Ptr == ';')
                    {
                        *Ptr = '\0';
                        continue;
                    }

                    Ptr++;
                }

                AcpiUtSafeStrncpy (AcpiGbl_DbLineBuf, Cmd, ACPI_DB_LINE_BUFFER_SIZE);
                Ptr++;
                Cmd = Ptr;
            }
            else
            {
                return;
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
            if (ACPI_FAILURE (Status))
            {
                return;
            }
        }

        /*
         * Signal the debug thread that we have a command to execute,
         * and wait for the command to complete.
         */
        AcpiOsReleaseMutex (AcpiGbl_DbCommandReady);

        Status = AcpiOsAcquireMutex (AcpiGbl_DbCommandComplete,
            ACPI_WAIT_FOREVER);
        if (ACPI_FAILURE (Status))
        {
            return;
        }
    }
}