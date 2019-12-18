#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_20__ {scalar_t__ Type; } ;
struct TYPE_18__ {scalar_t__ SpaceId; } ;
struct TYPE_17__ {scalar_t__ SpaceId; } ;
struct TYPE_16__ {int /*<<< orphan*/  Handler; } ;
struct TYPE_15__ {scalar_t__ Type; } ;
struct TYPE_19__ {TYPE_4__ AddressSpace; TYPE_3__ Region; TYPE_2__ CommonNotify; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 scalar_t__ ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_CTRL_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvAttachRegion (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvDetachRegion (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* AcpiEvFindRegionHandler (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_6__* AcpiGbl_RootNode ; 
 TYPE_5__* AcpiNsGetAttachedObject (TYPE_6__*) ; 
 TYPE_6__* AcpiNsValidateHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetRegionName (scalar_t__) ; 
 int /*<<< orphan*/  EvInstallHandler ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static ACPI_STATUS
AcpiEvInstallHandler (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OPERAND_OBJECT     *HandlerObj;
    ACPI_OPERAND_OBJECT     *NextHandlerObj;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_NAME (EvInstallHandler);


    HandlerObj = (ACPI_OPERAND_OBJECT  *) Context;

    /* Parameter validation */

    if (!HandlerObj)
    {
        return (AE_OK);
    }

    /* Convert and validate the device handle */

    Node = AcpiNsValidateHandle (ObjHandle);
    if (!Node)
    {
        return (AE_BAD_PARAMETER);
    }

    /*
     * We only care about regions and objects that are allowed to have
     * address space handlers
     */
    if ((Node->Type != ACPI_TYPE_DEVICE) &&
        (Node->Type != ACPI_TYPE_REGION) &&
        (Node != AcpiGbl_RootNode))
    {
        return (AE_OK);
    }

    /* Check for an existing internal object */

    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (!ObjDesc)
    {
        /* No object, just exit */

        return (AE_OK);
    }

    /* Devices are handled different than regions */

    if (ObjDesc->Common.Type == ACPI_TYPE_DEVICE)
    {
        /* Check if this Device already has a handler for this address space */

        NextHandlerObj = AcpiEvFindRegionHandler (
            HandlerObj->AddressSpace.SpaceId, ObjDesc->CommonNotify.Handler);
        if (NextHandlerObj)
        {
            /* Found a handler, is it for the same address space? */

            ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
                "Found handler for region [%s] in device %p(%p) handler %p\n",
                AcpiUtGetRegionName (HandlerObj->AddressSpace.SpaceId),
                ObjDesc, NextHandlerObj, HandlerObj));

            /*
             * Since the object we found it on was a device, then it means
             * that someone has already installed a handler for the branch
             * of the namespace from this device on. Just bail out telling
             * the walk routine to not traverse this branch. This preserves
             * the scoping rule for handlers.
             */
            return (AE_CTRL_DEPTH);
        }

        /*
         * As long as the device didn't have a handler for this space we
         * don't care about it. We just ignore it and proceed.
         */
        return (AE_OK);
    }

    /* Object is a Region */

    if (ObjDesc->Region.SpaceId != HandlerObj->AddressSpace.SpaceId)
    {
        /* This region is for a different address space, just ignore it */

        return (AE_OK);
    }

    /*
     * Now we have a region and it is for the handler's address space type.
     *
     * First disconnect region for any previous handler (if any)
     */
    AcpiEvDetachRegion (ObjDesc, FALSE);

    /* Connect the region to the new handler */

    Status = AcpiEvAttachRegion (HandlerObj, ObjDesc, FALSE);
    return (Status);
}