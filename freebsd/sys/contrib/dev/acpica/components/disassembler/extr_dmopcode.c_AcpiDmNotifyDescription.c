#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_11__ {int /*<<< orphan*/  Type; } ;
struct TYPE_8__ {int /*<<< orphan*/  Integer; TYPE_4__* Arg; } ;
struct TYPE_9__ {TYPE_5__* Node; TYPE_2__ Value; TYPE_4__* Next; } ;
struct TYPE_7__ {int AmlOpcode; } ;
struct TYPE_10__ {TYPE_3__ Asl; TYPE_1__ Common; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
#define  AML_BYTE_OP 130 
#define  AML_ONE_OP 129 
#define  AML_ZERO_OP 128 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetNotifyName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AcpiDmNotifyDescription (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_NAMESPACE_NODE     *Node;
    UINT8                   NotifyValue;
    UINT8                   Type = ACPI_TYPE_ANY;


    /* The notify value is the second argument */

    NextOp = Op->Asl.Value.Arg;
    NextOp = NextOp->Asl.Next;

    switch (NextOp->Common.AmlOpcode)
    {
    case AML_ZERO_OP:
    case AML_ONE_OP:

        NotifyValue = (UINT8) NextOp->Common.AmlOpcode;
        break;

    case AML_BYTE_OP:

        NotifyValue = (UINT8) NextOp->Asl.Value.Integer;
        break;

    default:
        return;
    }

    /*
     * Attempt to get the namespace node so we can determine the object type.
     * Some notify values are dependent on the object type (Device, Thermal,
     * or Processor).
     */
    Node = Op->Asl.Node;
    if (Node)
    {
        Type = Node->Type;
    }

    AcpiOsPrintf (" // %s", AcpiUtGetNotifyName (NotifyValue, Type));
}