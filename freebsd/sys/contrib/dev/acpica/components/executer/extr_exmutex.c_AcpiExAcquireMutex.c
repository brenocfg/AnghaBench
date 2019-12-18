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
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_16__ {scalar_t__ CurrentSyncLevel; int /*<<< orphan*/  ThreadId; } ;
struct TYPE_13__ {scalar_t__ SyncLevel; int AcquisitionDepth; scalar_t__ OriginalSyncLevel; TYPE_6__* OwnerThread; int /*<<< orphan*/  Node; } ;
struct TYPE_12__ {scalar_t__ Value; } ;
struct TYPE_15__ {TYPE_2__ Mutex; TYPE_1__ Integer; } ;
struct TYPE_14__ {TYPE_6__* Thread; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_MUTEX_ORDER ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiExAcquireMutexObject (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExLinkMutex (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireMutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExAcquireMutex (
    ACPI_OPERAND_OBJECT     *TimeDesc,
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (ExAcquireMutex, ObjDesc);


    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Must have a valid thread state struct */

    if (!WalkState->Thread)
    {
        ACPI_ERROR ((AE_INFO,
            "Cannot acquire Mutex [%4.4s], null thread info",
            AcpiUtGetNodeName (ObjDesc->Mutex.Node)));
        return_ACPI_STATUS (AE_AML_INTERNAL);
    }

    /*
     * Current sync level must be less than or equal to the sync level
     * of the mutex. This mechanism provides some deadlock prevention.
     */
    if (WalkState->Thread->CurrentSyncLevel > ObjDesc->Mutex.SyncLevel)
    {
        ACPI_ERROR ((AE_INFO,
            "Cannot acquire Mutex [%4.4s], "
            "current SyncLevel is too large (%u)",
            AcpiUtGetNodeName (ObjDesc->Mutex.Node),
            WalkState->Thread->CurrentSyncLevel));
        return_ACPI_STATUS (AE_AML_MUTEX_ORDER);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Acquiring: Mutex SyncLevel %u, Thread SyncLevel %u, "
        "Depth %u TID %p\n",
        ObjDesc->Mutex.SyncLevel, WalkState->Thread->CurrentSyncLevel,
        ObjDesc->Mutex.AcquisitionDepth, WalkState->Thread));

    Status = AcpiExAcquireMutexObject ((UINT16) TimeDesc->Integer.Value,
        ObjDesc, WalkState->Thread->ThreadId);

    if (ACPI_SUCCESS (Status) && ObjDesc->Mutex.AcquisitionDepth == 1)
    {
        /* Save Thread object, original/current sync levels */

        ObjDesc->Mutex.OwnerThread = WalkState->Thread;
        ObjDesc->Mutex.OriginalSyncLevel =
            WalkState->Thread->CurrentSyncLevel;
        WalkState->Thread->CurrentSyncLevel =
            ObjDesc->Mutex.SyncLevel;

        /* Link the mutex to the current thread for force-unlock at method exit */

        AcpiExLinkMutex (ObjDesc, WalkState->Thread);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "Acquired: Mutex SyncLevel %u, Thread SyncLevel %u, Depth %u\n",
        ObjDesc->Mutex.SyncLevel, WalkState->Thread->CurrentSyncLevel,
        ObjDesc->Mutex.AcquisitionDepth));

    return_ACPI_STATUS (Status);
}