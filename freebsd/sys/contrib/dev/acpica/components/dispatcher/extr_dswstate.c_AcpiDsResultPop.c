#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_6__ {int /*<<< orphan*/ ** ObjDesc; } ;
struct TYPE_8__ {TYPE_1__ Results; } ;
struct TYPE_7__ {scalar_t__ ResultCount; TYPE_3__* Results; } ;
typedef  TYPE_2__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 size_t ACPI_RESULTS_FRAME_OBJ_NUM ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_NO_RETURN_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDsResultStackPop (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsResultPop ; 

ACPI_STATUS
AcpiDsResultPop (
    ACPI_OPERAND_OBJECT     **Object,
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  Index;
    ACPI_GENERIC_STATE      *State;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_NAME (DsResultPop);


    State = WalkState->Results;

    /* Incorrect state of result stack */

    if (State && !WalkState->ResultCount)
    {
        ACPI_ERROR ((AE_INFO, "No results on result stack"));
        return (AE_AML_INTERNAL);
    }

    if (!State && WalkState->ResultCount)
    {
        ACPI_ERROR ((AE_INFO, "No result state for result stack"));
        return (AE_AML_INTERNAL);
    }

    /* Empty result stack */

    if (!State)
    {
        ACPI_ERROR ((AE_INFO, "Result stack is empty! State=%p", WalkState));
        return (AE_AML_NO_RETURN_VALUE);
    }

    /* Return object of the top element and clean that top element result stack */

    WalkState->ResultCount--;
    Index = (UINT32) WalkState->ResultCount % ACPI_RESULTS_FRAME_OBJ_NUM;

    *Object = State->Results.ObjDesc [Index];
    if (!*Object)
    {
        ACPI_ERROR ((AE_INFO, "No result objects on result stack, State=%p",
            WalkState));
        return (AE_AML_NO_RETURN_VALUE);
    }

    State->Results.ObjDesc [Index] = NULL;
    if (Index == 0)
    {
        Status = AcpiDsResultStackPop (WalkState);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Obj=%p [%s] Index=%X State=%p Num=%X\n", *Object,
        AcpiUtGetObjectTypeName (*Object),
        Index, WalkState, WalkState->ResultCount));

    return (AE_OK);
}