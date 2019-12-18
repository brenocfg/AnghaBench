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
 int /*<<< orphan*/  ACPI_DEBUG_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) ()) ; 
 int ACPI_LV_TABLES ; 
 int /*<<< orphan*/  ACPI_LV_VERBOSITY2 ; 
 int ACPI_NORMAL_DEFAULT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_ROOT_PREFIX ; 
 int /*<<< orphan*/  AcpiDbExecuteThread ; 
 int /*<<< orphan*/ * AcpiGbl_DbBuffer ; 
 int AcpiGbl_DbConsoleDebugLevel ; 
 int /*<<< orphan*/  AcpiGbl_DbDebugLevel ; 
 int /*<<< orphan*/ * AcpiGbl_DbFilename ; 
 void* AcpiGbl_DbOpt_NoIniMethods ; 
 int /*<<< orphan*/  AcpiGbl_DbOutputFlags ; 
 void* AcpiGbl_DbOutputToFile ; 
 scalar_t__* AcpiGbl_DbScopeBuf ; 
 int /*<<< orphan*/  AcpiGbl_DbScopeNode ; 
 void* AcpiGbl_DbTerminateLoop ; 
 int /*<<< orphan*/  AcpiGbl_DbThreadId ; 
 void* AcpiGbl_DbThreadsTerminated ; 
 int AcpiGbl_DebuggerConfiguration ; 
 int /*<<< orphan*/  AcpiGbl_RootNode ; 
 int /*<<< orphan*/ * AcpiOsAllocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsGetThreadId () ; 
 int /*<<< orphan*/  AcpiOsInitializeDebugger () ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 int DEBUGGER_MULTI_THREADED ; 
 void* FALSE ; 
 int /*<<< orphan*/  OSL_DEBUGGER_MAIN_THREAD ; 
 void* TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiInitializeDebugger (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (AcpiInitializeDebugger);


    /* Init globals */

    AcpiGbl_DbBuffer            = NULL;
    AcpiGbl_DbFilename          = NULL;
    AcpiGbl_DbOutputToFile      = FALSE;

    AcpiGbl_DbDebugLevel        = ACPI_LV_VERBOSITY2;
    AcpiGbl_DbConsoleDebugLevel = ACPI_NORMAL_DEFAULT | ACPI_LV_TABLES;
    AcpiGbl_DbOutputFlags       = ACPI_DB_CONSOLE_OUTPUT;

    AcpiGbl_DbOpt_NoIniMethods  = FALSE;

    AcpiGbl_DbBuffer = AcpiOsAllocate (ACPI_DEBUG_BUFFER_SIZE);
    if (!AcpiGbl_DbBuffer)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }
    memset (AcpiGbl_DbBuffer, 0, ACPI_DEBUG_BUFFER_SIZE);

    /* Initial scope is the root */

    AcpiGbl_DbScopeBuf [0] = AML_ROOT_PREFIX;
    AcpiGbl_DbScopeBuf [1] =  0;
    AcpiGbl_DbScopeNode = AcpiGbl_RootNode;

    /* Initialize user commands loop */

    AcpiGbl_DbTerminateLoop = FALSE;

    /*
     * If configured for multi-thread support, the debug executor runs in
     * a separate thread so that the front end can be in another address
     * space, environment, or even another machine.
     */
    if (AcpiGbl_DebuggerConfiguration & DEBUGGER_MULTI_THREADED)
    {
        /* These were created with one unit, grab it */

        Status = AcpiOsInitializeDebugger ();
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not get debugger mutex\n");
            return_ACPI_STATUS (Status);
        }

        /* Create the debug execution thread to execute commands */

        AcpiGbl_DbThreadsTerminated = FALSE;
        Status = AcpiOsExecute (OSL_DEBUGGER_MAIN_THREAD,
            AcpiDbExecuteThread, NULL);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "Could not start debugger thread"));
            AcpiGbl_DbThreadsTerminated = TRUE;
            return_ACPI_STATUS (Status);
        }
    }
    else
    {
        AcpiGbl_DbThreadId = AcpiOsGetThreadId ();
    }

    return_ACPI_STATUS (AE_OK);
}