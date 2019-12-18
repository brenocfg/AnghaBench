#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int Flags; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Node; } ;
struct TYPE_9__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_OPCODE_INFO ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int AML_CREATE ; 
 int AML_DEFER ; 
 int AML_HAS_ARGS ; 
 int AML_NAMED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * UtGetParentMethod (int /*<<< orphan*/ *) ; 
 TYPE_2__* XfGetParentMethod (TYPE_2__*) ; 

__attribute__((used)) static BOOLEAN
XfValidateCrossReference (
    ACPI_PARSE_OBJECT       *Op,
    const ACPI_OPCODE_INFO  *OpInfo,
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_PARSE_OBJECT       *ReferencingMethodOp;
    ACPI_NAMESPACE_NODE     *ReferencedMethodNode;


    /* Ignore actual named (and related) object declarations */

    if (OpInfo->Flags & (AML_NAMED | AML_CREATE | AML_DEFER | AML_HAS_ARGS))
    {
        return (TRUE);
    }

    /*
     * 1) Search upwards in parse tree for owner of the referencing object
     * 2) Search upwards in namespace to find the owner of the referenced object
     */
    ReferencingMethodOp = XfGetParentMethod (Op);
    ReferencedMethodNode = UtGetParentMethod (Node);

    if (!ReferencingMethodOp && !ReferencedMethodNode)
    {
        /*
         * 1) Case (0,0): Both Op and Node are not within methods
         * --> OK
         */
        return (TRUE);
    }

    if (!ReferencingMethodOp && ReferencedMethodNode)
    {
        /*
         * 2) Case (0,1): Op is not in a method, but Node is within a
         * method --> illegal
         */
        return (FALSE);
    }
    else if (ReferencingMethodOp && !ReferencedMethodNode)
    {
        /*
         * 3) Case (1,0): Op is within a method, but Node is not
         * --> OK
         */
        return (TRUE);
    }
    else if (ReferencingMethodOp->Asl.Node == ReferencedMethodNode)
    {
        /*
         * 4) Case (1,1): Both Op and Node are within the same method
         * --> OK
         */
        return (TRUE);
    }
    else
    {
        /*
         * 5) Case (1,1), Op and Node are in different methods
         * --> Illegal
         */
        return (FALSE);
    }
}