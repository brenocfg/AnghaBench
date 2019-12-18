#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* Next; int /*<<< orphan*/  OriginalSyncLevel; TYPE_3__* Prev; TYPE_6__* OwnerThread; } ;
struct TYPE_15__ {TYPE_5__ Mutex; } ;
struct TYPE_14__ {TYPE_4__* AcquiredMutexList; } ;
struct TYPE_9__ {TYPE_3__* Prev; } ;
struct TYPE_12__ {TYPE_1__ Mutex; } ;
struct TYPE_10__ {int /*<<< orphan*/  OriginalSyncLevel; TYPE_4__* Next; } ;
struct TYPE_11__ {TYPE_2__ Mutex; } ;
typedef  TYPE_6__ ACPI_THREAD_STATE ;
typedef  TYPE_7__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */

void
AcpiExUnlinkMutex (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_THREAD_STATE       *Thread = ObjDesc->Mutex.OwnerThread;


    if (!Thread)
    {
        return;
    }

    /* Doubly linked list */

    if (ObjDesc->Mutex.Next)
    {
        (ObjDesc->Mutex.Next)->Mutex.Prev = ObjDesc->Mutex.Prev;
    }

    if (ObjDesc->Mutex.Prev)
    {
        (ObjDesc->Mutex.Prev)->Mutex.Next = ObjDesc->Mutex.Next;

        /*
         * Migrate the previous sync level associated with this mutex to
         * the previous mutex on the list so that it may be preserved.
         * This handles the case where several mutexes have been acquired
         * at the same level, but are not released in opposite order.
         */
        (ObjDesc->Mutex.Prev)->Mutex.OriginalSyncLevel =
            ObjDesc->Mutex.OriginalSyncLevel;
    }
    else
    {
        Thread->AcquiredMutexList = ObjDesc->Mutex.Next;
    }
}