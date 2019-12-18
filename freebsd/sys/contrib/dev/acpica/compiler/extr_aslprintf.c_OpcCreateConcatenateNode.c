#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int AcpiBtype; TYPE_2__* Parent; TYPE_2__* Child; TYPE_2__* Next; int /*<<< orphan*/  LogicalLineNumber; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_CONCATENATE_OP ; 
 int /*<<< orphan*/  PARSEOP_CONCATENATE ; 
 int /*<<< orphan*/  PARSEOP_ZERO ; 
 void* TrAllocateOp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
OpcCreateConcatenateNode (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_PARSE_OBJECT       *Node)
{
    ACPI_PARSE_OBJECT       *NewConcatOp;


    if (!Op->Asl.Child)
    {
        Op->Asl.Child = Node;
        Node->Asl.Parent = Op;
        return;
    }

    NewConcatOp = TrAllocateOp (PARSEOP_CONCATENATE);
    NewConcatOp->Asl.AmlOpcode = AML_CONCATENATE_OP;
    NewConcatOp->Asl.AcpiBtype = 0x7;
    NewConcatOp->Asl.LogicalLineNumber = Op->Asl.LogicalLineNumber;

    /* First arg is child of Op*/

    NewConcatOp->Asl.Child = Op->Asl.Child;
    Op->Asl.Child->Asl.Parent = NewConcatOp;

    /* Second arg is Node */

    NewConcatOp->Asl.Child->Asl.Next = Node;
    Node->Asl.Parent = NewConcatOp;

    /* Third arg is Zero (not used) */

    NewConcatOp->Asl.Child->Asl.Next->Asl.Next =
        TrAllocateOp (PARSEOP_ZERO);
    NewConcatOp->Asl.Child->Asl.Next->Asl.Next->Asl.Parent =
        NewConcatOp;

    Op->Asl.Child = NewConcatOp;
    NewConcatOp->Asl.Parent = Op;
}