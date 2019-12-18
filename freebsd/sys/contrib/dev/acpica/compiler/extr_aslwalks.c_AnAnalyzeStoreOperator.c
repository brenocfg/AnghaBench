#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_9__ {int Flags; scalar_t__ Type; } ;
struct TYPE_7__ {int ParseOpcode; scalar_t__ AmlOpcode; TYPE_3__* Node; TYPE_2__* Next; TYPE_2__* Child; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int ACPI_BTYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_ANY ; 
 scalar_t__ AML_ARG6 ; 
 scalar_t__ AML_DEBUG_OP ; 
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 scalar_t__ AML_LOCAL0 ; 
 int ANOBJ_IS_EXTERNAL ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_DUPLICATE_ITEM ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_TYPE ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int AnGetBtype (TYPE_2__*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  AslGbl_EnableReferenceTypechecking ; 
#define  PARSEOP_COPYOBJECT 134 
#define  PARSEOP_DEBUG 133 
#define  PARSEOP_DEREFOF 132 
#define  PARSEOP_INDEX 131 
#define  PARSEOP_METHODCALL 130 
#define  PARSEOP_REFOF 129 
#define  PARSEOP_STORE 128 

__attribute__((used)) static void
AnAnalyzeStoreOperator (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_NAMESPACE_NODE     *SourceNode;
    ACPI_NAMESPACE_NODE     *TargetNode;
    ACPI_PARSE_OBJECT       *SourceOperandOp;
    ACPI_PARSE_OBJECT       *TargetOperandOp;
    UINT32                  SourceOperandBtype;
    UINT32                  TargetOperandBtype;


    /* Extract the two operands for STORE */

    SourceOperandOp = Op->Asl.Child;
    TargetOperandOp = SourceOperandOp->Asl.Next;

    /*
     * Ignore these Source operand opcodes, they cannot be typechecked,
     * the actual result is unknown here.
     */
    switch (SourceOperandOp->Asl.ParseOpcode)
    {
    /* For these, type of the returned value is unknown at compile time */

    case PARSEOP_DEREFOF:
    case PARSEOP_METHODCALL:
    case PARSEOP_STORE:
    case PARSEOP_COPYOBJECT:

        return;

    case PARSEOP_INDEX:
    case PARSEOP_REFOF:

        if (!AslGbl_EnableReferenceTypechecking)
        {
            return;
        }

        /*
         * These opcodes always return an object reference, and thus
         * the result can only be stored to a Local, Arg, or Debug.
         */
        if (TargetOperandOp->Asl.AmlOpcode == AML_DEBUG_OP)
        {
            return;
        }

        if ((TargetOperandOp->Asl.AmlOpcode < AML_LOCAL0) ||
            (TargetOperandOp->Asl.AmlOpcode > AML_ARG6))
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, TargetOperandOp,
                "Source [Reference], Target must be [Local/Arg/Debug]");
        }
        return;

    default:
        break;
    }

    /*
     * Ignore these Target operand opcodes, they cannot be typechecked
     */
    switch (TargetOperandOp->Asl.ParseOpcode)
    {
    case PARSEOP_DEBUG:
    case PARSEOP_DEREFOF:
    case PARSEOP_REFOF:
    case PARSEOP_INDEX:
    case PARSEOP_STORE:

        return;

    default:
        break;
    }

    /*
     * Ignore typecheck for External() operands of type "UnknownObj",
     * we don't know the actual type (source or target).
     */
    SourceNode = SourceOperandOp->Asl.Node;
    if (SourceNode &&
        (SourceNode->Flags & ANOBJ_IS_EXTERNAL) &&
        (SourceNode->Type == ACPI_TYPE_ANY))
    {
        return;
    }

    TargetNode = TargetOperandOp->Asl.Node;
    if (TargetNode &&
        (TargetNode->Flags & ANOBJ_IS_EXTERNAL) &&
        (TargetNode->Type == ACPI_TYPE_ANY))
    {
        return;
    }

    /*
     * A NULL node with a namepath AML opcode indicates non-existent
     * name. Just return, the error message is generated elsewhere.
     */
    if ((!SourceNode && (SourceOperandOp->Asl.AmlOpcode == AML_INT_NAMEPATH_OP)) ||
        (!TargetNode && (TargetOperandOp->Asl.AmlOpcode == AML_INT_NAMEPATH_OP)))
    {
        return;
    }

    /*
     * Simple check for source same as target via NS node.
     * -- Could be expanded to locals and args.
     */
    if (SourceNode && TargetNode)
    {
        if (SourceNode == TargetNode)
        {
            AslError (ASL_WARNING, ASL_MSG_DUPLICATE_ITEM,
                TargetOperandOp, "Source is the same as Target");
            return;
        }
    }

    /* Ignore typecheck if either source or target is a local or arg */

    if ((SourceOperandOp->Asl.AmlOpcode >= AML_LOCAL0) &&
        (SourceOperandOp->Asl.AmlOpcode <= AML_ARG6))
    {
        return; /* Cannot type a local/arg at compile time */
    }

    if ((TargetOperandOp->Asl.AmlOpcode >= AML_LOCAL0) &&
        (TargetOperandOp->Asl.AmlOpcode <= AML_ARG6))
    {
        return; /* Cannot type a local/arg at compile time */
    }

    /*
     * Package objects are a special case because they cannot by implicitly
     * converted to/from anything. Check for these two illegal cases:
     *
     *      Store (non-package, package)
     *      Store (package, non-package)
     */
    SourceOperandBtype = AnGetBtype (SourceOperandOp);
    TargetOperandBtype = AnGetBtype (TargetOperandOp);

    /* Check source first for (package, non-package) case */

    if (SourceOperandBtype & ACPI_BTYPE_PACKAGE)
    {
        /* If Source is PACKAGE-->Target must be PACKAGE */

        if (!(TargetOperandBtype & ACPI_BTYPE_PACKAGE))
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, TargetOperandOp,
                "Source is [Package], Target must be a package also");
        }
    }

    /* Else check target for (non-package, package) case */

    else if (TargetOperandBtype & ACPI_BTYPE_PACKAGE)
    {
        /* If Target is PACKAGE, Source must be PACKAGE */

        if (!(SourceOperandBtype & ACPI_BTYPE_PACKAGE))
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE, SourceOperandOp,
                "Target is [Package], Source must be a package also");
        }
    }
}