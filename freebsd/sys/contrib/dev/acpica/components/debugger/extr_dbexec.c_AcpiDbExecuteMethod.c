#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_10__ {scalar_t__ Length; int /*<<< orphan*/  Pointer; } ;
struct TYPE_9__ {int /*<<< orphan*/  Pathname; scalar_t__** Args; int /*<<< orphan*/ * Types; } ;
struct TYPE_8__ {size_t Count; int /*<<< orphan*/ * Pointer; } ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_1__ ACPI_OBJECT_LIST ;
typedef  int /*<<< orphan*/  ACPI_OBJECT ;
typedef  TYPE_2__ ACPI_DB_METHOD_INFO ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEBUGGER_MAX_ARGS ; 
 scalar_t__ ACPI_DEBUG_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ AE_ABORT_METHOD ; 
 scalar_t__ AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiDbConvertToObject (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDbDeleteObjects (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDbgLevel ; 
 scalar_t__ AcpiEvaluateObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*) ; 
 void* AcpiGbl_AbortMethod ; 
 void* AcpiGbl_CmSingleStep ; 
 int /*<<< orphan*/  AcpiGbl_DbBuffer ; 
 scalar_t__ AcpiGbl_DbOutputToFile ; 
 void* AcpiGbl_MethodExecuting ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 int /*<<< orphan*/  DbExecuteMethod ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbExecuteMethod (
    ACPI_DB_METHOD_INFO     *Info,
    ACPI_BUFFER             *ReturnObj)
{
    ACPI_STATUS             Status;
    ACPI_OBJECT_LIST        ParamObjects;
    ACPI_OBJECT             Params[ACPI_DEBUGGER_MAX_ARGS + 1];
    UINT32                  i;


    ACPI_FUNCTION_TRACE (DbExecuteMethod);


    if (AcpiGbl_DbOutputToFile && !AcpiDbgLevel)
    {
        AcpiOsPrintf ("Warning: debug output is not enabled!\n");
    }

    ParamObjects.Count = 0;
    ParamObjects.Pointer = NULL;

    /* Pass through any command-line arguments */

    if (Info->Args && Info->Args[0])
    {
        /* Get arguments passed on the command line */

        for (i = 0; (Info->Args[i] && *(Info->Args[i])); i++)
        {
            /* Convert input string (token) to an actual ACPI_OBJECT */

            Status = AcpiDbConvertToObject (Info->Types[i],
                Info->Args[i], &Params[i]);
            if (ACPI_FAILURE (Status))
            {
                ACPI_EXCEPTION ((AE_INFO, Status,
                    "While parsing method arguments"));
                goto Cleanup;
            }
        }

        ParamObjects.Count = i;
        ParamObjects.Pointer = Params;
    }

    /* Prepare for a return object of arbitrary size */

    ReturnObj->Pointer = AcpiGbl_DbBuffer;
    ReturnObj->Length  = ACPI_DEBUG_BUFFER_SIZE;

    /* Do the actual method execution */

    AcpiGbl_MethodExecuting = TRUE;
    Status = AcpiEvaluateObject (NULL, Info->Pathname,
        &ParamObjects, ReturnObj);

    AcpiGbl_CmSingleStep = FALSE;
    AcpiGbl_MethodExecuting = FALSE;

    if (ACPI_FAILURE (Status))
    {
        if ((Status == AE_ABORT_METHOD) || AcpiGbl_AbortMethod)
        {
            /* Clear the abort and fall back to the debugger prompt */

            ACPI_EXCEPTION ((AE_INFO, Status,
                "Aborting top-level method"));

            AcpiGbl_AbortMethod = FALSE;
            Status = AE_OK;
            goto Cleanup;
        }

        ACPI_EXCEPTION ((AE_INFO, Status,
            "while executing %s from AML Debugger", Info->Pathname));

        if (Status == AE_BUFFER_OVERFLOW)
        {
            ACPI_ERROR ((AE_INFO,
                "Possible buffer overflow within AML Debugger "
                "buffer (size 0x%X needed 0x%X)",
                ACPI_DEBUG_BUFFER_SIZE, (UINT32) ReturnObj->Length));
        }
    }

Cleanup:
    AcpiDbDeleteObjects (ParamObjects.Count, Params);
    return_ACPI_STATUS (Status);
}