#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {TYPE_2__* Object; } ;
struct TYPE_7__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_8__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDsMethodDataGetNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  AcpiUtAddReference (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DsMethodDataSetValue ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDsMethodDataSetValue (
    UINT8                   Type,
    UINT32                  Index,
    ACPI_OPERAND_OBJECT     *Object,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;


    ACPI_FUNCTION_TRACE (DsMethodDataSetValue);


    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "NewObj %p Type %2.2X, Refs=%u [%s]\n", Object,
        Type, Object->Common.ReferenceCount,
        AcpiUtGetTypeName (Object->Common.Type)));

    /* Get the namespace node for the arg/local */

    Status = AcpiDsMethodDataGetNode (Type, Index, WalkState, &Node);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * Increment ref count so object can't be deleted while installed.
     * NOTE: We do not copy the object in order to preserve the call by
     * reference semantics of ACPI Control Method invocation.
     * (See ACPI Specification 2.0C)
     */
    AcpiUtAddReference (Object);

    /* Install the object */

    Node->Object = Object;
    return_ACPI_STATUS (Status);
}