#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_13__ {int /*<<< orphan*/  ObjectType; int /*<<< orphan*/  Class; } ;
struct TYPE_10__ {int /*<<< orphan*/  String; TYPE_3__* Arg; } ;
struct TYPE_11__ {int AmlOpcode; int AmlOpName; TYPE_1__ Value; int /*<<< orphan*/  Node; TYPE_3__* Parent; TYPE_3__* Next; } ;
struct TYPE_12__ {TYPE_2__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_ALIAS ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_ADD_OP 130 
 int /*<<< orphan*/  AML_CLASS_CREATE ; 
 int /*<<< orphan*/  AML_CLASS_EXECUTE ; 
 int AML_IF_OP ; 
 int AML_INT_METHODCALL_OP ; 
#define  AML_INT_NAMEPATH_OP 129 
 int AML_RETURN_OP ; 
#define  AML_STORE_OP 128 
 int AML_WHILE_OP ; 
 int /*<<< orphan*/  AcpiDmAddOpToExternalList (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmCountChildren (TYPE_3__*) ; 
 int AcpiDmInspectPossibleArgs (int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiNsExternalizeName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* AcpiPsGetOpcodeInfo (int) ; 
 int /*<<< orphan*/  Path ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmFindOrphanDescending (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    const ACPI_OPCODE_INFO  *OpInfo;
    ACPI_PARSE_OBJECT       *ChildOp;
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_PARSE_OBJECT       *ParentOp;
    UINT32                  ArgCount;


    if (!Op)
    {
        return (AE_OK);
    }

#ifdef ACPI_UNDER_DEVELOPMENT
    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
#endif

    switch (Op->Common.AmlOpcode)
    {
#ifdef ACPI_UNDER_DEVELOPMENT
    case AML_ADD_OP:

        ChildOp = Op->Common.Value.Arg;
        if ((ChildOp->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
            !ChildOp->Common.Node)
        {
            AcpiNsExternalizeName (ACPI_UINT32_MAX, ChildOp->Common.Value.String,
                NULL, &Path);
            AcpiOsPrintf ("/* %-16s A-NAMEPATH: %s  */\n",
                Op->Common.AmlOpName, Path);
            ACPI_FREE (Path);

            NextOp = Op->Common.Next;
            if (!NextOp)
            {
                /* This NamePath has no args, assume it is an integer */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            ArgCount = AcpiDmInspectPossibleArgs (3, 1, NextOp);
            AcpiOsPrintf ("/* A-CHILDREN: %u Actual %u */\n",
                ArgCount, AcpiDmCountChildren (Op));

            if (ArgCount < 1)
            {
                /* One Arg means this is just a Store(Name,Target) */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            AcpiDmAddOpToExternalList (ChildOp,
                ChildOp->Common.Value.String, ACPI_TYPE_METHOD, ArgCount, 0);
        }
        break;

#endif

    case AML_STORE_OP:

        ChildOp = Op->Common.Value.Arg;
        if ((ChildOp->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
            !ChildOp->Common.Node)
        {
            NextOp = Op->Common.Next;
            if (!NextOp)
            {
                /* This NamePath has no args, assume it is an integer */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            ArgCount = AcpiDmInspectPossibleArgs (2, 1, NextOp);
            if (ArgCount <= 1)
            {
                /* One Arg means this is just a Store(Name,Target) */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, ArgCount, 0);
                return (AE_OK);
            }

            AcpiDmAddOpToExternalList (ChildOp,
                ChildOp->Common.Value.String, ACPI_TYPE_METHOD, ArgCount, 0);
        }
        break;

    case AML_INT_NAMEPATH_OP:

        /* Must examine parent to see if this namepath is an argument */

        ParentOp = Op->Common.Parent;
        OpInfo = AcpiPsGetOpcodeInfo (ParentOp->Common.AmlOpcode);

        if ((OpInfo->Class != AML_CLASS_EXECUTE) &&
            (OpInfo->Class != AML_CLASS_CREATE) &&
            (OpInfo->ObjectType != ACPI_TYPE_LOCAL_ALIAS) &&
            (ParentOp->Common.AmlOpcode != AML_INT_METHODCALL_OP) &&
            !Op->Common.Node)
        {
            ArgCount = AcpiDmInspectPossibleArgs (0, 0, Op);

            /*
             * Check if namepath is a predicate for if/while or lone parameter to
             * a return.
             */
            if (ArgCount == 0)
            {
                if (((ParentOp->Common.AmlOpcode == AML_IF_OP) ||
                     (ParentOp->Common.AmlOpcode == AML_WHILE_OP) ||
                     (ParentOp->Common.AmlOpcode == AML_RETURN_OP)) &&

                     /* And namepath is the first argument */
                     (ParentOp->Common.Value.Arg == Op))
                {
                    AcpiDmAddOpToExternalList (Op,
                        Op->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                    break;
                }
            }

            /*
             * This is a standalone namestring (not a parameter to another
             * operator) - it *must* be a method invocation, nothing else is
             * grammatically possible.
             */
            AcpiDmAddOpToExternalList (Op,
                Op->Common.Value.String, ACPI_TYPE_METHOD, ArgCount, 0);
        }
        break;

    default:

        break;
    }

    return (AE_OK);
}