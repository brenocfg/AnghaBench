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
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ALLOCATE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_EXECUTER ; 
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_LV_TRACE_POINT ; 
 int /*<<< orphan*/  ACPI_TRACE_ENABLED ; 
 int /*<<< orphan*/  ACPI_TRACE_ONESHOT ; 
 int /*<<< orphan*/  ACPI_TRACE_OPCODE ; 
 int /*<<< orphan*/ * AcpiDbTraceMethodName ; 
 int /*<<< orphan*/  AcpiDbgLayer ; 
 int /*<<< orphan*/  AcpiDebugTrace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_DbConsoleDebugLevel ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (char*) ; 

void
AcpiDbTrace (
    char                    *EnableArg,
    char                    *MethodArg,
    char                    *OnceArg)
{
    UINT32                  DebugLevel = 0;
    UINT32                  DebugLayer = 0;
    UINT32                  Flags = 0;


    AcpiUtStrupr (EnableArg);
    AcpiUtStrupr (OnceArg);

    if (MethodArg)
    {
        if (AcpiDbTraceMethodName)
        {
            ACPI_FREE (AcpiDbTraceMethodName);
            AcpiDbTraceMethodName = NULL;
        }

        AcpiDbTraceMethodName = ACPI_ALLOCATE (strlen (MethodArg) + 1);
        if (!AcpiDbTraceMethodName)
        {
            AcpiOsPrintf ("Failed to allocate method name (%s)\n",
                MethodArg);
            return;
        }

        strcpy (AcpiDbTraceMethodName, MethodArg);
    }

    if (!strcmp (EnableArg, "ENABLE") ||
        !strcmp (EnableArg, "METHOD") ||
        !strcmp (EnableArg, "OPCODE"))
    {
        if (!strcmp (EnableArg, "ENABLE"))
        {
            /* Inherit current console settings */

            DebugLevel = AcpiGbl_DbConsoleDebugLevel;
            DebugLayer = AcpiDbgLayer;
        }
        else
        {
            /* Restrict console output to trace points only */

            DebugLevel = ACPI_LV_TRACE_POINT;
            DebugLayer = ACPI_EXECUTER;
        }

        Flags = ACPI_TRACE_ENABLED;

        if (!strcmp (EnableArg, "OPCODE"))
        {
            Flags |= ACPI_TRACE_OPCODE;
        }

        if (OnceArg && !strcmp (OnceArg, "ONCE"))
        {
            Flags |= ACPI_TRACE_ONESHOT;
        }
    }

    (void) AcpiDebugTrace (AcpiDbTraceMethodName,
        DebugLevel, DebugLayer, Flags);
}