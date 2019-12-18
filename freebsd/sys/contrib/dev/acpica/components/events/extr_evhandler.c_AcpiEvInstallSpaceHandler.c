#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT8 ;
struct TYPE_23__ {scalar_t__ Type; } ;
struct TYPE_21__ {TYPE_4__* Handler; } ;
struct TYPE_20__ {scalar_t__ Handler; TYPE_4__* Next; int /*<<< orphan*/ * Setup; void* Context; TYPE_5__* Node; int /*<<< orphan*/ * RegionList; void* HandlerFlags; void* SpaceId; } ;
struct TYPE_19__ {void* Type; } ;
struct TYPE_22__ {TYPE_3__ CommonNotify; TYPE_2__ AddressSpace; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;
typedef  int ACPI_ADR_SPACE_TYPE ;
typedef  int /*<<< orphan*/ * ACPI_ADR_SPACE_SETUP ;
typedef  scalar_t__ ACPI_ADR_SPACE_HANDLER ;

/* Variables and functions */
 void* ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
#define  ACPI_ADR_SPACE_CMOS 133 
#define  ACPI_ADR_SPACE_DATA_TABLE 132 
#define  ACPI_ADR_SPACE_PCI_BAR_TARGET 131 
#define  ACPI_ADR_SPACE_PCI_CONFIG 130 
#define  ACPI_ADR_SPACE_SYSTEM_IO 129 
#define  ACPI_ADR_SPACE_SYSTEM_MEMORY 128 
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DEFAULT_HANDLER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_WALK_UNLOCK ; 
 scalar_t__ ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 scalar_t__ ACPI_TYPE_LOCAL_ADDRESS_HANDLER ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 scalar_t__ ACPI_TYPE_THERMAL ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SAME_HANDLER ; 
 int /*<<< orphan*/ * AcpiEvCmosRegionSetup ; 
 int /*<<< orphan*/ * AcpiEvDefaultRegionSetup ; 
 TYPE_4__* AcpiEvFindRegionHandler (int,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiEvInstallHandler ; 
 int /*<<< orphan*/ * AcpiEvIoSpaceRegionSetup ; 
 int /*<<< orphan*/ * AcpiEvPciBarRegionSetup ; 
 int /*<<< orphan*/ * AcpiEvPciConfigRegionSetup ; 
 int /*<<< orphan*/ * AcpiEvSystemMemoryRegionSetup ; 
 scalar_t__ AcpiExCmosSpaceHandler ; 
 scalar_t__ AcpiExDataTableSpaceHandler ; 
 scalar_t__ AcpiExPciBarSpaceHandler ; 
 scalar_t__ AcpiExPciConfigSpaceHandler ; 
 scalar_t__ AcpiExSystemIoSpaceHandler ; 
 scalar_t__ AcpiExSystemMemorySpaceHandler ; 
 TYPE_5__* AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiNsAttachObject (TYPE_5__*,TYPE_4__*,scalar_t__) ; 
 TYPE_4__* AcpiNsGetAttachedObject (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiNsWalkNamespace (scalar_t__,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* AcpiUtCreateInternalObject (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtGetRegionName (int) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_4__*) ; 
 int /*<<< orphan*/  EvInstallSpaceHandler ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvInstallSpaceHandler (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_ADR_SPACE_TYPE     SpaceId,
    ACPI_ADR_SPACE_HANDLER  Handler,
    ACPI_ADR_SPACE_SETUP    Setup,
    void                    *Context)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *HandlerObj;
    ACPI_STATUS             Status = AE_OK;
    ACPI_OBJECT_TYPE        Type;
    UINT8                   Flags = 0;


    ACPI_FUNCTION_TRACE (EvInstallSpaceHandler);


    /*
     * This registration is valid for only the types below and the root.
     * The root node is where the default handlers get installed.
     */
    if ((Node->Type != ACPI_TYPE_DEVICE)     &&
        (Node->Type != ACPI_TYPE_PROCESSOR)  &&
        (Node->Type != ACPI_TYPE_THERMAL)    &&
        (Node != AcpiGbl_RootNode))
    {
        Status = AE_BAD_PARAMETER;
        goto UnlockAndExit;
    }

    if (Handler == ACPI_DEFAULT_HANDLER)
    {
        Flags = ACPI_ADDR_HANDLER_DEFAULT_INSTALLED;

        switch (SpaceId)
        {
        case ACPI_ADR_SPACE_SYSTEM_MEMORY:

            Handler = AcpiExSystemMemorySpaceHandler;
            Setup   = AcpiEvSystemMemoryRegionSetup;
            break;

        case ACPI_ADR_SPACE_SYSTEM_IO:

            Handler = AcpiExSystemIoSpaceHandler;
            Setup   = AcpiEvIoSpaceRegionSetup;
            break;

        case ACPI_ADR_SPACE_PCI_CONFIG:

            Handler = AcpiExPciConfigSpaceHandler;
            Setup   = AcpiEvPciConfigRegionSetup;
            break;

        case ACPI_ADR_SPACE_CMOS:

            Handler = AcpiExCmosSpaceHandler;
            Setup   = AcpiEvCmosRegionSetup;
            break;

        case ACPI_ADR_SPACE_PCI_BAR_TARGET:

            Handler = AcpiExPciBarSpaceHandler;
            Setup   = AcpiEvPciBarRegionSetup;
            break;

        case ACPI_ADR_SPACE_DATA_TABLE:

            Handler = AcpiExDataTableSpaceHandler;
            Setup   = NULL;
            break;

        default:

            Status = AE_BAD_PARAMETER;
            goto UnlockAndExit;
        }
    }

    /* If the caller hasn't specified a setup routine, use the default */

    if (!Setup)
    {
        Setup = AcpiEvDefaultRegionSetup;
    }

    /* Check for an existing internal object */

    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (ObjDesc)
    {
        /*
         * The attached device object already exists. Now make sure
         * the handler is not already installed.
         */
        HandlerObj = AcpiEvFindRegionHandler (SpaceId,
            ObjDesc->CommonNotify.Handler);

        if (HandlerObj)
        {
            if (HandlerObj->AddressSpace.Handler == Handler)
            {
                /*
                 * It is (relatively) OK to attempt to install the SAME
                 * handler twice. This can easily happen with the
                 * PCI_Config space.
                 */
                Status = AE_SAME_HANDLER;
                goto UnlockAndExit;
            }
            else
            {
                /* A handler is already installed */

                Status = AE_ALREADY_EXISTS;
            }

            goto UnlockAndExit;
        }
    }
    else
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
            "Creating object on Device %p while installing handler\n",
            Node));

        /* ObjDesc does not exist, create one */

        if (Node->Type == ACPI_TYPE_ANY)
        {
            Type = ACPI_TYPE_DEVICE;
        }
        else
        {
            Type = Node->Type;
        }

        ObjDesc = AcpiUtCreateInternalObject (Type);
        if (!ObjDesc)
        {
            Status = AE_NO_MEMORY;
            goto UnlockAndExit;
        }

        /* Init new descriptor */

        ObjDesc->Common.Type = (UINT8) Type;

        /* Attach the new object to the Node */

        Status = AcpiNsAttachObject (Node, ObjDesc, Type);

        /* Remove local reference to the object */

        AcpiUtRemoveReference (ObjDesc);

        if (ACPI_FAILURE (Status))
        {
            goto UnlockAndExit;
        }
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
        "Installing address handler for region %s(%X) "
        "on Device %4.4s %p(%p)\n",
        AcpiUtGetRegionName (SpaceId), SpaceId,
        AcpiUtGetNodeName (Node), Node, ObjDesc));

    /*
     * Install the handler
     *
     * At this point there is no existing handler. Just allocate the object
     * for the handler and link it into the list.
     */
    HandlerObj = AcpiUtCreateInternalObject (ACPI_TYPE_LOCAL_ADDRESS_HANDLER);
    if (!HandlerObj)
    {
        Status = AE_NO_MEMORY;
        goto UnlockAndExit;
    }

    /* Init handler obj */

    HandlerObj->AddressSpace.SpaceId = (UINT8) SpaceId;
    HandlerObj->AddressSpace.HandlerFlags = Flags;
    HandlerObj->AddressSpace.RegionList = NULL;
    HandlerObj->AddressSpace.Node = Node;
    HandlerObj->AddressSpace.Handler = Handler;
    HandlerObj->AddressSpace.Context = Context;
    HandlerObj->AddressSpace.Setup = Setup;

    /* Install at head of Device.AddressSpace list */

    HandlerObj->AddressSpace.Next = ObjDesc->CommonNotify.Handler;

    /*
     * The Device object is the first reference on the HandlerObj.
     * Each region that uses the handler adds a reference.
     */
    ObjDesc->CommonNotify.Handler = HandlerObj;

    /*
     * Walk the namespace finding all of the regions this handler will
     * manage.
     *
     * Start at the device and search the branch toward the leaf nodes
     * until either the leaf is encountered or a device is detected that
     * has an address handler of the same type.
     *
     * In either case, back up and search down the remainder of the branch
     */
    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, Node,
        ACPI_UINT32_MAX, ACPI_NS_WALK_UNLOCK,
        AcpiEvInstallHandler, NULL, HandlerObj, NULL);

UnlockAndExit:
    return_ACPI_STATUS (Status);
}