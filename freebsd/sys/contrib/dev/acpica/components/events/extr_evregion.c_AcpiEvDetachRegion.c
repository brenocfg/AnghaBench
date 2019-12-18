#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int Flags; TYPE_4__* Next; TYPE_4__* Handler; int /*<<< orphan*/  SpaceId; } ;
struct TYPE_12__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* Setup ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ;TYPE_4__* RegionList; } ;
struct TYPE_11__ {void* RegionContext; } ;
struct TYPE_14__ {TYPE_3__ Region; TYPE_2__ AddressSpace; TYPE_1__ Extra; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  (* ACPI_ADR_SPACE_SETUP ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  ACPI_REGION_DEACTIVATE ; 
 int /*<<< orphan*/  ACPI_REG_DISCONNECT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int AOPOBJ_SETUP_COMPLETE ; 
 int /*<<< orphan*/  AcpiEvExecuteRegMethod (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* AcpiNsGetSecondaryObject (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetRegionName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_4__*) ; 
 int /*<<< orphan*/  EvDetachRegion ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiEvDetachRegion (
    ACPI_OPERAND_OBJECT     *RegionObj,
    BOOLEAN                 AcpiNsIsLocked)
{
    ACPI_OPERAND_OBJECT     *HandlerObj;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *StartDesc;
    ACPI_OPERAND_OBJECT     **LastObjPtr;
    ACPI_ADR_SPACE_SETUP    RegionSetup;
    void                    **RegionContext;
    ACPI_OPERAND_OBJECT     *RegionObj2;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvDetachRegion);


    RegionObj2 = AcpiNsGetSecondaryObject (RegionObj);
    if (!RegionObj2)
    {
        return_VOID;
    }
    RegionContext = &RegionObj2->Extra.RegionContext;

    /* Get the address handler from the region object */

    HandlerObj = RegionObj->Region.Handler;
    if (!HandlerObj)
    {
        /* This region has no handler, all done */

        return_VOID;
    }

    /* Find this region in the handler's list */

    ObjDesc = HandlerObj->AddressSpace.RegionList;
    StartDesc = ObjDesc;
    LastObjPtr = &HandlerObj->AddressSpace.RegionList;

    while (ObjDesc)
    {
        /* Is this the correct Region? */

        if (ObjDesc == RegionObj)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
                "Removing Region %p from address handler %p\n",
                RegionObj, HandlerObj));

            /* This is it, remove it from the handler's list */

            *LastObjPtr = ObjDesc->Region.Next;
            ObjDesc->Region.Next = NULL;        /* Must clear field */

            if (AcpiNsIsLocked)
            {
                Status = AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);
                if (ACPI_FAILURE (Status))
                {
                    return_VOID;
                }
            }

            /* Now stop region accesses by executing the _REG method */

            Status = AcpiEvExecuteRegMethod (RegionObj, ACPI_REG_DISCONNECT);
            if (ACPI_FAILURE (Status))
            {
                ACPI_EXCEPTION ((AE_INFO, Status, "from region _REG, [%s]",
                    AcpiUtGetRegionName (RegionObj->Region.SpaceId)));
            }

            if (AcpiNsIsLocked)
            {
                Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
                if (ACPI_FAILURE (Status))
                {
                    return_VOID;
                }
            }

            /*
             * If the region has been activated, call the setup handler with
             * the deactivate notification
             */
            if (RegionObj->Region.Flags & AOPOBJ_SETUP_COMPLETE)
            {
                RegionSetup = HandlerObj->AddressSpace.Setup;
                Status = RegionSetup (RegionObj, ACPI_REGION_DEACTIVATE,
                    HandlerObj->AddressSpace.Context, RegionContext);

                /*
                 * RegionContext should have been released by the deactivate
                 * operation. We don't need access to it anymore here.
                 */
                if (RegionContext)
                {
                    *RegionContext = NULL;
                }

                /* Init routine may fail, Just ignore errors */

                if (ACPI_FAILURE (Status))
                {
                    ACPI_EXCEPTION ((AE_INFO, Status,
                        "from region handler - deactivate, [%s]",
                        AcpiUtGetRegionName (RegionObj->Region.SpaceId)));
                }

                RegionObj->Region.Flags &= ~(AOPOBJ_SETUP_COMPLETE);
            }

            /*
             * Remove handler reference in the region
             *
             * NOTE: this doesn't mean that the region goes away, the region
             * is just inaccessible as indicated to the _REG method
             *
             * If the region is on the handler's list, this must be the
             * region's handler
             */
            RegionObj->Region.Handler = NULL;
            AcpiUtRemoveReference (HandlerObj);

            return_VOID;
        }

        /* Walk the linked list of handlers */

        LastObjPtr = &ObjDesc->Region.Next;
        ObjDesc = ObjDesc->Region.Next;

        /* Prevent infinite loop if list is corrupted */

        if (ObjDesc == StartDesc)
        {
            ACPI_ERROR ((AE_INFO,
                "Circular handler list in region object %p",
                RegionObj));
            return_VOID;
        }
    }

    /* If we get here, the region was not in the handler's region list */

    ACPI_DEBUG_PRINT ((ACPI_DB_OPREGION,
        "Cannot remove region %p from address handler %p\n",
        RegionObj, HandlerObj));

    return_VOID;
}