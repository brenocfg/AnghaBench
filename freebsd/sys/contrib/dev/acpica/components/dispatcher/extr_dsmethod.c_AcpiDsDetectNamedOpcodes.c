#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Opcode; TYPE_3__* OpInfo; TYPE_2__* MethodNode; TYPE_4__* MethodDesc; } ;
struct TYPE_13__ {int InfoFlags; scalar_t__ SyncLevel; } ;
struct TYPE_12__ {TYPE_5__ Method; } ;
struct TYPE_11__ {int Flags; int /*<<< orphan*/  Name; } ;
struct TYPE_9__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_10__ {TYPE_1__ Name; } ;
typedef  TYPE_6__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/  (*) (TYPE_6__*,int /*<<< orphan*/ **)) ; 
 int ACPI_METHOD_IGNORE_SYNC_LEVEL ; 
 int ACPI_METHOD_SERIALIZED ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int AML_CREATE ; 
 int AML_FIELD ; 
 int AML_NAMED ; 

__attribute__((used)) static ACPI_STATUS
AcpiDsDetectNamedOpcodes (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       **OutOp)
{

    ACPI_FUNCTION_NAME (AcpiDsDetectNamedOpcodes);


    /* We are only interested in opcodes that create a new name */

    if (!(WalkState->OpInfo->Flags & (AML_NAMED | AML_CREATE | AML_FIELD)))
    {
        return (AE_OK);
    }

    /*
     * At this point, we know we have a Named object opcode.
     * Mark the method as serialized. Later code will create a mutex for
     * this method to enforce serialization.
     *
     * Note, ACPI_METHOD_IGNORE_SYNC_LEVEL flag means that we will ignore the
     * Sync Level mechanism for this method, even though it is now serialized.
     * Otherwise, there can be conflicts with existing ASL code that actually
     * uses sync levels.
     */
    WalkState->MethodDesc->Method.SyncLevel = 0;
    WalkState->MethodDesc->Method.InfoFlags |=
        (ACPI_METHOD_SERIALIZED | ACPI_METHOD_IGNORE_SYNC_LEVEL);

    ACPI_DEBUG_PRINT ((ACPI_DB_INFO,
        "Method serialized [%4.4s] %p - [%s] (%4.4X)\n",
        WalkState->MethodNode->Name.Ascii, WalkState->MethodNode,
        WalkState->OpInfo->Name, WalkState->Opcode));

    /* Abort the parse, no need to examine this method any further */

    return (AE_CTRL_TERMINATE);
}