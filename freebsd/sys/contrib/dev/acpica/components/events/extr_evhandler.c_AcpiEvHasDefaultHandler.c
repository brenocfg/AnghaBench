#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ SpaceId; int HandlerFlags; TYPE_3__* Next; } ;
struct TYPE_5__ {TYPE_3__* Handler; } ;
struct TYPE_7__ {TYPE_2__ AddressSpace; TYPE_1__ CommonNotify; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_ADR_SPACE_TYPE ;

/* Variables and functions */
 int ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
 TYPE_3__* AcpiNsGetAttachedObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AcpiEvHasDefaultHandler (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_ADR_SPACE_TYPE     SpaceId)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *HandlerObj;


    /* Must have an existing internal object */

    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (ObjDesc)
    {
        HandlerObj = ObjDesc->CommonNotify.Handler;

        /* Walk the linked list of handlers for this object */

        while (HandlerObj)
        {
            if (HandlerObj->AddressSpace.SpaceId == SpaceId)
            {
                if (HandlerObj->AddressSpace.HandlerFlags &
                    ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)
                {
                    return (TRUE);
                }
            }

            HandlerObj = HandlerObj->AddressSpace.Next;
        }
    }

    return (FALSE);
}