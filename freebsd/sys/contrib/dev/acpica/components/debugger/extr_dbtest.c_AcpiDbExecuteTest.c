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
typedef  int UINT32 ;

/* Variables and functions */
 int ACPI_TYPE_NOT_FOUND ; 
 int /*<<< orphan*/  AcpiDbEvaluateAllPredefinedNames (int /*<<< orphan*/ *) ; 
 int AcpiDbMatchArgument (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDbTestAllObjects () ; 
 int /*<<< orphan*/  AcpiDbTestTypes ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
#define  CMD_TEST_OBJECTS 129 
#define  CMD_TEST_PREDEFINED 128 

void
AcpiDbExecuteTest (
    char                    *TypeArg)
{
    UINT32                  Temp;


    AcpiUtStrupr (TypeArg);
    Temp = AcpiDbMatchArgument (TypeArg, AcpiDbTestTypes);
    if (Temp == ACPI_TYPE_NOT_FOUND)
    {
        AcpiOsPrintf ("Invalid or unsupported argument\n");
        return;
    }

    switch (Temp)
    {
    case CMD_TEST_OBJECTS:

        AcpiDbTestAllObjects ();
        break;

    case CMD_TEST_PREDEFINED:

        AcpiDbEvaluateAllPredefinedNames (NULL);
        break;

    default:
        break;
    }
}