#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_11__ {int /*<<< orphan*/  AmlStart; } ;
struct TYPE_16__ {int /*<<< orphan*/  Op; int /*<<< orphan*/  Opcode; TYPE_5__* DeferredNode; TYPE_3__* MethodNode; TYPE_1__ ParserState; int /*<<< orphan*/  Aml; } ;
struct TYPE_14__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_15__ {TYPE_4__ Name; } ;
struct TYPE_12__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_13__ {TYPE_2__ Name; } ;
typedef  TYPE_6__ ACPI_WALK_STATE ;
typedef  int ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_NAME ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_PTR_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int) ; 
 int AE_CODE_CONTROL ; 
 int /*<<< orphan*/  AcpiDbDumpMethodInfo (int,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiDsClearImplicitReturn (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiDsDumpMethodStack (int,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExEnterInterpreter () ; 
 int /*<<< orphan*/  AcpiExExitInterpreter () ; 
 int AcpiGbl_ExceptionHandler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiDsMethodError (
    ACPI_STATUS             Status,
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  AmlOffset;
    ACPI_NAME               Name = 0;


    ACPI_FUNCTION_ENTRY ();


    /* Ignore AE_OK and control exception codes */

    if (ACPI_SUCCESS (Status) ||
        (Status & AE_CODE_CONTROL))
    {
        return (Status);
    }

    /* Invoke the global exception handler */

    if (AcpiGbl_ExceptionHandler)
    {
        /* Exit the interpreter, allow handler to execute methods */

        AcpiExExitInterpreter ();

        /*
         * Handler can map the exception code to anything it wants, including
         * AE_OK, in which case the executing method will not be aborted.
         */
        AmlOffset = (UINT32) ACPI_PTR_DIFF (WalkState->Aml,
            WalkState->ParserState.AmlStart);

        if (WalkState->MethodNode)
        {
            Name = WalkState->MethodNode->Name.Integer;
        }
        else if (WalkState->DeferredNode)
        {
            Name = WalkState->DeferredNode->Name.Integer;
        }

        Status = AcpiGbl_ExceptionHandler (Status, Name,
            WalkState->Opcode, AmlOffset, NULL);
        AcpiExEnterInterpreter ();
    }

    AcpiDsClearImplicitReturn (WalkState);

    if (ACPI_FAILURE (Status))
    {
        AcpiDsDumpMethodStack (Status, WalkState, WalkState->Op);

        /* Display method locals/args if debugger is present */

#ifdef ACPI_DEBUGGER
        AcpiDbDumpMethodInfo (Status, WalkState);
#endif
    }

    return (Status);
}