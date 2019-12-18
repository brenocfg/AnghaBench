#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_5__ {size_t NumOperands; int /*<<< orphan*/ * Operands; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiExResolveToValue (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  DsResolveOperands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsResolveOperands (
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE_PTR (DsResolveOperands, WalkState);


    /*
     * Attempt to resolve each of the valid operands
     * Method arguments are passed by reference, not by value. This means
     * that the actual objects are passed, not copies of the objects.
     */
    for (i = 0; i < WalkState->NumOperands; i++)
    {
        Status = AcpiExResolveToValue (&WalkState->Operands[i], WalkState);
        if (ACPI_FAILURE (Status))
        {
            break;
        }
    }

    return_ACPI_STATUS (Status);
}