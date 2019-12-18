#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_18__ {int Flags; TYPE_4__* Op; int /*<<< orphan*/  Type; } ;
struct TYPE_14__ {int /*<<< orphan*/  String; } ;
struct TYPE_15__ {int AmlOpcode; TYPE_4__* Next; TYPE_5__* Node; int /*<<< orphan*/  ExternalName; TYPE_1__ Value; int /*<<< orphan*/  CompileFlags; } ;
struct TYPE_17__ {TYPE_2__ Asl; } ;
struct TYPE_16__ {int /*<<< orphan*/  ScopeInfo; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REGION_FIELD ; 
 scalar_t__ AE_ALREADY_EXISTS ; 
 scalar_t__ AE_BAD_PARAMETER ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
#define  AML_BANK_FIELD_OP 133 
#define  AML_FIELD_OP 132 
#define  AML_INDEX_FIELD_OP 131 
#define  AML_INT_ACCESSFIELD_OP 130 
#define  AML_INT_CONNECTION_OP 129 
#define  AML_INT_RESERVEDFIELD_OP 128 
 int ANOBJ_IS_EXTERNAL ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_CORE_EXCEPTION ; 
 int /*<<< orphan*/  ASL_MSG_FOUND_HERE ; 
 int /*<<< orphan*/  ASL_MSG_NAME_EXISTS ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 scalar_t__ AcpiNsLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  AslDualParseOpError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_NOT_FOUND_DURING_LOAD ; 
 TYPE_4__* UtGetArg (TYPE_4__*,int) ; 

__attribute__((used)) static ACPI_STATUS
LdLoadFieldElements (
    UINT32                  AmlType,
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_PARSE_OBJECT       *Child = NULL;
    ACPI_PARSE_OBJECT       *SourceRegion;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;


    SourceRegion = UtGetArg (Op, 0);
    if (SourceRegion)
    {
        Status = AcpiNsLookup (WalkState->ScopeInfo,
            SourceRegion->Asl.Value.String,
            AmlType, ACPI_IMODE_EXECUTE,
            ACPI_NS_DONT_OPEN_SCOPE, NULL, &Node);
        if (Status == AE_NOT_FOUND)
        {
            /*
             * If the named object is not found, it means that it is either a
             * forward reference or the named object does not exist.
             */
            SourceRegion->Asl.CompileFlags |= OP_NOT_FOUND_DURING_LOAD;
        }
    }

    /* Get the first named field element */

    switch (Op->Asl.AmlOpcode)
    {
    case AML_BANK_FIELD_OP:

        Child = UtGetArg (Op, 6);
        break;

    case AML_INDEX_FIELD_OP:

        Child = UtGetArg (Op, 5);
        break;

    case AML_FIELD_OP:

        Child = UtGetArg (Op, 4);
        break;

    default:

        /* No other opcodes should arrive here */

        return (AE_BAD_PARAMETER);
    }

    /* Enter all elements into the namespace */

    while (Child)
    {
        switch (Child->Asl.AmlOpcode)
        {
        case AML_INT_RESERVEDFIELD_OP:
        case AML_INT_ACCESSFIELD_OP:
        case AML_INT_CONNECTION_OP:
            break;

        default:

            Status = AcpiNsLookup (WalkState->ScopeInfo,
                Child->Asl.Value.String,
                ACPI_TYPE_LOCAL_REGION_FIELD,
                ACPI_IMODE_LOAD_PASS1,
                ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
                    ACPI_NS_ERROR_IF_FOUND, NULL, &Node);
            if (ACPI_FAILURE (Status))
            {
                if (Status != AE_ALREADY_EXISTS)
                {
                    AslError (ASL_ERROR, ASL_MSG_CORE_EXCEPTION, Child,
                        Child->Asl.Value.String);
                    return (Status);
                }
                else if (Status == AE_ALREADY_EXISTS &&
                    (Node->Flags & ANOBJ_IS_EXTERNAL))
                {
                    Node->Type = (UINT8) ACPI_TYPE_LOCAL_REGION_FIELD;
                    Node->Flags &= ~ANOBJ_IS_EXTERNAL;
                }
                else
                {
                    /*
                     * The name already exists in this scope
                     * But continue processing the elements
                     */
                    AslDualParseOpError (ASL_WARNING, ASL_MSG_NAME_EXISTS, Child,
                        Child->Asl.Value.String, ASL_MSG_FOUND_HERE, Node->Op,
                        Node->Op->Asl.ExternalName);
                }
            }
            else
            {
                Child->Asl.Node = Node;
                Node->Op = Child;
            }
            break;
        }

        Child = Child->Asl.Next;
    }

    return (AE_OK);
}