#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_5__ {scalar_t__ Object; } ;
struct TYPE_4__ {TYPE_2__* Arguments; TYPE_2__* LocalVariables; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 size_t ACPI_METHOD_NUM_ARGS ; 
 size_t ACPI_METHOD_NUM_LOCALS ; 
 int /*<<< orphan*/  AcpiNsDetachObject (TYPE_2__*) ; 
 int /*<<< orphan*/  DsMethodDataDeleteAll ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDsMethodDataDeleteAll (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  Index;


    ACPI_FUNCTION_TRACE (DsMethodDataDeleteAll);


    /* Detach the locals */

    for (Index = 0; Index < ACPI_METHOD_NUM_LOCALS; Index++)
    {
        if (WalkState->LocalVariables[Index].Object)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Deleting Local%u=%p\n",
                Index, WalkState->LocalVariables[Index].Object));

            /* Detach object (if present) and remove a reference */

            AcpiNsDetachObject (&WalkState->LocalVariables[Index]);
        }
    }

    /* Detach the arguments */

    for (Index = 0; Index < ACPI_METHOD_NUM_ARGS; Index++)
    {
        if (WalkState->Arguments[Index].Object)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Deleting Arg%u=%p\n",
                Index, WalkState->Arguments[Index].Object));

            /* Detach object (if present) and remove a reference */

            AcpiNsDetachObject (&WalkState->Arguments[Index]);
        }
    }

    return_VOID;
}