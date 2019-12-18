#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  void ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * AcpiNsGetAttachedObject (void*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,void*,...) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (void*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbWalkForReferences (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OPERAND_OBJECT     *ObjDesc = (ACPI_OPERAND_OBJECT  *) Context;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;


    /* Check for match against the namespace node itself */

    if (Node == (void *) ObjDesc)
    {
        AcpiOsPrintf ("Object is a Node [%4.4s]\n",
            AcpiUtGetNodeName (Node));
    }

    /* Check for match against the object attached to the node */

    if (AcpiNsGetAttachedObject (Node) == ObjDesc)
    {
        AcpiOsPrintf ("Reference at Node->Object %p [%4.4s]\n",
            Node, AcpiUtGetNodeName (Node));
    }

    return (AE_OK);
}