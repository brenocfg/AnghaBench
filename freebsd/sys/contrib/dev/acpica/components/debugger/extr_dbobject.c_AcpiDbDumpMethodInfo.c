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
struct TYPE_5__ {int /*<<< orphan*/ * Thread; scalar_t__ DeferredNode; int /*<<< orphan*/ * MethodNode; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_THREAD_STATE ;
typedef  int ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int AE_CODE_CONTROL ; 
 int AE_CODE_MASK ; 
 int /*<<< orphan*/  AcpiDbDecodeArguments (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiDbDecodeLocals (TYPE_1__*) ; 
 int /*<<< orphan*/ * AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 

void
AcpiDbDumpMethodInfo (
    ACPI_STATUS             Status,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_THREAD_STATE       *Thread;
    ACPI_NAMESPACE_NODE     *Node;


    Node = WalkState->MethodNode;

    /* There are no locals or arguments for the module-level code case */

    if (Node == AcpiGbl_RootNode)
    {
        return;
    }

    /* Ignore control codes, they are not errors */

    if ((Status & AE_CODE_MASK) == AE_CODE_CONTROL)
    {
        return;
    }

    /* We may be executing a deferred opcode */

    if (WalkState->DeferredNode)
    {
        AcpiOsPrintf ("Executing subtree for Buffer/Package/Region\n");
        return;
    }

    /*
     * If there is no Thread, we are not actually executing a method.
     * This can happen when the iASL compiler calls the interpreter
     * to perform constant folding.
     */
    Thread = WalkState->Thread;
    if (!Thread)
    {
        return;
    }

    /* Display the method locals and arguments */

    AcpiOsPrintf ("\n");
    AcpiDbDecodeLocals (WalkState);
    AcpiOsPrintf ("\n");
    AcpiDbDecodeArguments (WalkState);
    AcpiOsPrintf ("\n");
}