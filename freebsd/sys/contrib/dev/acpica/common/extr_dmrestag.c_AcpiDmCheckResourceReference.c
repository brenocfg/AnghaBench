#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_24__ {scalar_t__ Type; } ;
struct TYPE_23__ {scalar_t__ Type; scalar_t__ ObjectType; } ;
struct TYPE_19__ {int /*<<< orphan*/  String; scalar_t__ Integer; } ;
struct TYPE_20__ {scalar_t__ AmlOpcode; TYPE_1__ Value; int /*<<< orphan*/ * Node; TYPE_4__* Next; } ;
struct TYPE_22__ {TYPE_2__ Common; } ;
struct TYPE_21__ {int /*<<< orphan*/  ScopeInfo; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_OPCODE_INFO ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 scalar_t__ ACPI_MUL_8 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_NS_SEARCH_PARENT ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ AML_CREATE_BIT_FIELD_OP ; 
 scalar_t__ AML_CREATE_FIELD_OP ; 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_TYPE_CREATE_FIELD ; 
 TYPE_6__* AcpiDmGetResourceNode (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  AcpiGetTagPathname (TYPE_4__*,TYPE_6__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  AcpiNsLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_6__**) ; 
 TYPE_4__* AcpiPsGetDepthNext (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_5__* AcpiPsGetOpcodeInfo (scalar_t__) ; 

void
AcpiDmCheckResourceReference (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *BufferNameOp;
    ACPI_PARSE_OBJECT       *IndexOp;
    ACPI_NAMESPACE_NODE     *BufferNode;
    ACPI_NAMESPACE_NODE     *ResourceNode;
    const ACPI_OPCODE_INFO  *OpInfo;
    UINT32                  BitIndex;


    /* We are only interested in the CreateXxxxField opcodes */

    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
    if (OpInfo->Type != AML_TYPE_CREATE_FIELD)
    {
        return;
    }

    /* Get the buffer term operand */

    BufferNameOp = AcpiPsGetDepthNext (NULL, Op);

    /* Must be a named buffer, not an arg or local or method call */

    if (BufferNameOp->Common.AmlOpcode != AML_INT_NAMEPATH_OP)
    {
        return;
    }

    /* Get the Index term, must be an integer constant to convert */

    IndexOp = BufferNameOp->Common.Next;

    /* Major cheat: The Node field is also used for the Tag ptr. Clear it now */

    IndexOp->Common.Node = NULL;

    OpInfo = AcpiPsGetOpcodeInfo (IndexOp->Common.AmlOpcode);
    if (OpInfo->ObjectType != ACPI_TYPE_INTEGER)
    {
        return;
    }

    /* Get the bit offset of the descriptor within the buffer */

    if ((Op->Common.AmlOpcode == AML_CREATE_BIT_FIELD_OP) ||
        (Op->Common.AmlOpcode == AML_CREATE_FIELD_OP))
    {
        /* Index operand is a bit offset */

        BitIndex = (UINT32) IndexOp->Common.Value.Integer;
    }
    else
    {
        /* Index operand is a byte offset, convert to bits */

        BitIndex = (UINT32) ACPI_MUL_8 (IndexOp->Common.Value.Integer);
    }

    /* Lookup the buffer in the namespace */

    Status = AcpiNsLookup (WalkState->ScopeInfo,
        BufferNameOp->Common.Value.String, ACPI_TYPE_BUFFER,
        ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT, WalkState,
        &BufferNode);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    /* Validate object type, we must have a buffer */

    if (BufferNode->Type != ACPI_TYPE_BUFFER)
    {
        return;
    }

    /* Find the resource descriptor node corresponding to the index */

    ResourceNode = AcpiDmGetResourceNode (BufferNode, BitIndex);
    if (!ResourceNode)
    {
        return;
    }

    /* Translate the Index to a resource tag pathname */

    AcpiGetTagPathname (IndexOp, BufferNode, ResourceNode, BitIndex);
}