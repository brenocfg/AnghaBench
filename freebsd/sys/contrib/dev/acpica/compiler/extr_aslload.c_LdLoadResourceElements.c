#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_22__ {TYPE_5__* Op; int /*<<< orphan*/  Length; scalar_t__ Value; } ;
struct TYPE_17__ {int /*<<< orphan*/  BitLength; scalar_t__ BitOffset; } ;
struct TYPE_18__ {TYPE_1__ Tag; scalar_t__ Integer; } ;
struct TYPE_19__ {TYPE_6__* Node; TYPE_2__ Value; scalar_t__ ExternalName; scalar_t__ Namepath; scalar_t__ ParentMethod; } ;
struct TYPE_21__ {TYPE_3__ Asl; } ;
struct TYPE_20__ {int /*<<< orphan*/  ScopeInfo; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_RESOURCE ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_RESOURCE_FIELD ; 
 scalar_t__ AE_ALREADY_EXISTS ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 TYPE_5__* ASL_GET_CHILD_NODE (TYPE_5__*) ; 
 TYPE_5__* ASL_GET_PEER_NODE (TYPE_5__*) ; 
 int /*<<< orphan*/  ASL_MSG_FOUND_HERE ; 
 int /*<<< orphan*/  ASL_MSG_NAME_EXISTS ; 
 scalar_t__ AcpiNsLookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*,TYPE_6__**) ; 
 int /*<<< orphan*/  AslDualParseOpError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static ACPI_STATUS
LdLoadResourceElements (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_PARSE_OBJECT       *InitializerOp = NULL;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;


    /*
     * Enter the resource name into the namespace. Name must not already exist.
     * This opens a scope, so later field names are guaranteed to be new/unique.
     */
    Status = AcpiNsLookup (WalkState->ScopeInfo, Op->Asl.Namepath,
        ACPI_TYPE_LOCAL_RESOURCE, ACPI_IMODE_LOAD_PASS1,
        ACPI_NS_NO_UPSEARCH | ACPI_NS_ERROR_IF_FOUND,
        WalkState, &Node);
    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_ALREADY_EXISTS)
        {
            /* Actual node causing the error was saved in ParentMethod */

            AslDualParseOpError (ASL_ERROR, ASL_MSG_NAME_EXISTS,
                (ACPI_PARSE_OBJECT *) Op->Asl.ParentMethod,
                Op->Asl.Namepath, ASL_MSG_FOUND_HERE, Node->Op,
                Node->Op->Asl.ExternalName);
            return (AE_OK);
        }
        return (Status);
    }

    Node->Value = (UINT32) Op->Asl.Value.Integer;
    Node->Op = Op;
    Op->Asl.Node = Node;

    /*
     * Now enter the predefined fields, for easy lookup when referenced
     * by the source ASL
     */
    InitializerOp = ASL_GET_CHILD_NODE (Op);
    while (InitializerOp)
    {
        if (InitializerOp->Asl.ExternalName)
        {
            Status = AcpiNsLookup (WalkState->ScopeInfo,
                InitializerOp->Asl.ExternalName,
                ACPI_TYPE_LOCAL_RESOURCE_FIELD, ACPI_IMODE_LOAD_PASS1,
                ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE, NULL, &Node);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            /*
             * Store the field offset and length in the namespace node
             * so it can be used when the field is referenced
             */
            Node->Value = InitializerOp->Asl.Value.Tag.BitOffset;
            Node->Length = InitializerOp->Asl.Value.Tag.BitLength;
            InitializerOp->Asl.Node = Node;
            Node->Op = InitializerOp;
        }

        InitializerOp = ASL_GET_PEER_NODE (InitializerOp);
    }

    return (AE_OK);
}