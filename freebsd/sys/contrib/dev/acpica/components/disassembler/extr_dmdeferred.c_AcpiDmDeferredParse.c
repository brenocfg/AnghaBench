#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_17__ {TYPE_5__* Arg; } ;
struct TYPE_18__ {int AmlOpcode; TYPE_5__* Parent; TYPE_2__ Value; TYPE_5__* Next; int /*<<< orphan*/  AmlOpName; } ;
struct TYPE_16__ {int /*<<< orphan*/  Name; } ;
struct TYPE_20__ {TYPE_3__ Common; TYPE_1__ Named; } ;
struct TYPE_19__ {int /*<<< orphan*/  ParseFlags; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_5__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int /*<<< orphan*/  ACPI_PARSE_DELETE_TREE ; 
 int /*<<< orphan*/  ACPI_PARSE_DISASSEMBLE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_BUFFER_OP 130 
#define  AML_PACKAGE_OP 129 
#define  AML_VARIABLE_PACKAGE_OP 128 
 TYPE_4__* AcpiDsCreateWalkState (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsInitAmlWalk (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* AcpiPsGetDepthNext (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiPsParseAml (TYPE_4__*) ; 
 int /*<<< orphan*/  DmDeferredParse ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmDeferredParse (
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   *Aml,
    UINT32                  AmlLength)
{
    ACPI_WALK_STATE         *WalkState;
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *SearchOp;
    ACPI_PARSE_OBJECT       *StartOp;
    ACPI_PARSE_OBJECT       *NewRootOp;
    ACPI_PARSE_OBJECT       *ExtraOp;


    ACPI_FUNCTION_TRACE (DmDeferredParse);


    if (!Aml || !AmlLength)
    {
        return_ACPI_STATUS (AE_OK);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Parsing deferred opcode %s [%4.4s]\n",
        Op->Common.AmlOpName, (char *) &Op->Named.Name));

    /* Need a new walk state to parse the AML */

    WalkState = AcpiDsCreateWalkState (0, Op, NULL, NULL);
    if (!WalkState)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    Status = AcpiDsInitAmlWalk (WalkState, Op, NULL, Aml,
        AmlLength, NULL, ACPI_IMODE_LOAD_PASS1);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Parse the AML for this deferred opcode */

    WalkState->ParseFlags &= ~ACPI_PARSE_DELETE_TREE;
    WalkState->ParseFlags |= ACPI_PARSE_DISASSEMBLE;
    Status = AcpiPsParseAml (WalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS(Status);
    }

    StartOp = (Op->Common.Value.Arg)->Common.Next;
    SearchOp = StartOp;
    while (SearchOp)
    {
        SearchOp = AcpiPsGetDepthNext (StartOp, SearchOp);
    }

    /*
     * For Buffer and Package opcodes, link the newly parsed subtree
     * into the main parse tree
     */
    switch (Op->Common.AmlOpcode)
    {
    case AML_BUFFER_OP:
    case AML_PACKAGE_OP:
    case AML_VARIABLE_PACKAGE_OP:

        switch (Op->Common.AmlOpcode)
        {
        case AML_PACKAGE_OP:

            ExtraOp = Op->Common.Value.Arg;
            NewRootOp = ExtraOp->Common.Next;
            ACPI_FREE (ExtraOp);
            break;

        case AML_VARIABLE_PACKAGE_OP:
        case AML_BUFFER_OP:
        default:

            NewRootOp = Op->Common.Value.Arg;
            break;
        }

        Op->Common.Value.Arg = NewRootOp->Common.Value.Arg;

        /* Must point all parents to the main tree */

        StartOp = Op;
        SearchOp = StartOp;
        while (SearchOp)
        {
            if (SearchOp->Common.Parent == NewRootOp)
            {
                SearchOp->Common.Parent = Op;
            }

            SearchOp = AcpiPsGetDepthNext (StartOp, SearchOp);
        }

        ACPI_FREE (NewRootOp);
        break;

    default:

        break;
    }

    return_ACPI_STATUS (AE_OK);
}