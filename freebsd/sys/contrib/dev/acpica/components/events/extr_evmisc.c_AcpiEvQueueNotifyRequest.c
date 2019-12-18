#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  size_t UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_19__ {size_t HandlerListId; TYPE_13__* Global; TYPE_4__* HandlerListHead; scalar_t__ Value; TYPE_5__* Node; } ;
struct TYPE_18__ {int /*<<< orphan*/  DescriptorType; } ;
struct TYPE_22__ {TYPE_3__ Notify; TYPE_2__ Common; } ;
struct TYPE_21__ {int /*<<< orphan*/  Type; } ;
struct TYPE_17__ {TYPE_4__** NotifyList; } ;
struct TYPE_20__ {TYPE_1__ CommonNotify; } ;
struct TYPE_16__ {int /*<<< orphan*/  Handler; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_6__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_NOTIFY ; 
 size_t ACPI_DEVICE_HANDLER_LIST ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_MAX_SYS_NOTIFY ; 
 size_t ACPI_SYSTEM_HANDLER_LIST ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  AcpiEvIsNotifyObject (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiEvNotifyDispatch ; 
 TYPE_13__* AcpiGbl_GlobalNotify ; 
 TYPE_4__* AcpiNsGetAttachedObject (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_6__* AcpiUtCreateGenericState () ; 
 int /*<<< orphan*/  AcpiUtDeleteGenericState (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetNotifyName (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvQueueNotifyRequest ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 

ACPI_STATUS
AcpiEvQueueNotifyRequest (
    ACPI_NAMESPACE_NODE     *Node,
    UINT32                  NotifyValue)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *HandlerListHead = NULL;
    ACPI_GENERIC_STATE      *Info;
    UINT8                   HandlerListId = 0;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_NAME (EvQueueNotifyRequest);


    /* Are Notifies allowed on this object? */

    if (!AcpiEvIsNotifyObject (Node))
    {
        return (AE_TYPE);
    }

    /* Get the correct notify list type (System or Device) */

    if (NotifyValue <= ACPI_MAX_SYS_NOTIFY)
    {
        HandlerListId = ACPI_SYSTEM_HANDLER_LIST;
    }
    else
    {
        HandlerListId = ACPI_DEVICE_HANDLER_LIST;
    }

    /* Get the notify object attached to the namespace Node */

    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (ObjDesc)
    {
        /* We have an attached object, Get the correct handler list */

        HandlerListHead = ObjDesc->CommonNotify.NotifyList[HandlerListId];
    }

    /*
     * If there is no notify handler (Global or Local)
     * for this object, just ignore the notify
     */
    if (!AcpiGbl_GlobalNotify[HandlerListId].Handler && !HandlerListHead)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_INFO,
            "No notify handler for Notify, ignoring (%4.4s, %X) node %p\n",
            AcpiUtGetNodeName (Node), NotifyValue, Node));

        return (AE_OK);
    }

    /* Setup notify info and schedule the notify dispatcher */

    Info = AcpiUtCreateGenericState ();
    if (!Info)
    {
        return (AE_NO_MEMORY);
    }

    Info->Common.DescriptorType = ACPI_DESC_TYPE_STATE_NOTIFY;

    Info->Notify.Node = Node;
    Info->Notify.Value = (UINT16) NotifyValue;
    Info->Notify.HandlerListId = HandlerListId;
    Info->Notify.HandlerListHead = HandlerListHead;
    Info->Notify.Global = &AcpiGbl_GlobalNotify[HandlerListId];

    ACPI_DEBUG_PRINT ((ACPI_DB_INFO,
        "Dispatching Notify on [%4.4s] (%s) Value 0x%2.2X (%s) Node %p\n",
        AcpiUtGetNodeName (Node), AcpiUtGetTypeName (Node->Type),
        NotifyValue, AcpiUtGetNotifyName (NotifyValue, ACPI_TYPE_ANY), Node));

    Status = AcpiOsExecute (OSL_NOTIFY_HANDLER,
        AcpiEvNotifyDispatch, Info);
    if (ACPI_FAILURE (Status))
    {
        AcpiUtDeleteGenericState (Info);
    }

    return (Status);
}