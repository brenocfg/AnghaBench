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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_19__ {int ParseOpcode; char* Namepath; int CompileFlags; char* ExternalName; TYPE_2__* Parent; TYPE_6__* Next; int /*<<< orphan*/  ParentMethod; } ;
struct TYPE_22__ {TYPE_3__ Asl; } ;
struct TYPE_21__ {TYPE_4__* MethodStack; } ;
struct TYPE_20__ {int /*<<< orphan*/  Op; int /*<<< orphan*/  NumReturnWithValue; int /*<<< orphan*/  NumReturnNoValue; struct TYPE_20__* Next; } ;
struct TYPE_17__ {int CompileFlags; } ;
struct TYPE_18__ {TYPE_1__ Asl; } ;
typedef  TYPE_4__ ASL_METHOD_INFO ;
typedef  TYPE_5__ ASL_ANALYSIS_WALK_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_6__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_4__*) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  ASL_MSG_RETURN_TYPES ; 
 int /*<<< orphan*/  ASL_MSG_UNREACHABLE_CODE ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AnLastStatementIsReturn (TYPE_6__*) ; 
 int /*<<< orphan*/  ApCheckForGpeNameConflict (TYPE_6__*) ; 
 int /*<<< orphan*/  ApCheckForPredefinedMethod (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ApCheckPredefinedReturnValue (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ApCheckRegMethod (TYPE_6__*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,char*) ; 
 int /*<<< orphan*/  CmCleanupAndExit () ; 
 int OP_HAS_NO_EXIT ; 
 int OP_IF_HAS_NO_EXIT ; 
 int OP_METHOD_NO_RETVAL ; 
 int OP_METHOD_SOME_NO_RETVAL ; 
#define  PARSEOP_ELSE 132 
#define  PARSEOP_IF 131 
#define  PARSEOP_METHOD 130 
#define  PARSEOP_NAME 129 
#define  PARSEOP_RETURN 128 
 int /*<<< orphan*/  printf (char*,char*) ; 

ACPI_STATUS
MtMethodAnalysisWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ASL_ANALYSIS_WALK_INFO  *WalkInfo = (ASL_ANALYSIS_WALK_INFO *) Context;
    ASL_METHOD_INFO         *MethodInfo = WalkInfo->MethodStack;


    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_METHOD:
    case PARSEOP_RETURN:

        if (!MethodInfo)
        {
            printf ("No method info for method! [%s]\n", Op->Asl.Namepath);
            AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL, Op,
                "No method info for this method");

            CmCleanupAndExit ();
            return (AE_AML_INTERNAL);
        }
        break;

    default:

        break;
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_METHOD:

        WalkInfo->MethodStack = MethodInfo->Next;

        /*
         * Check if there is no return statement at the end of the
         * method AND we can actually get there -- i.e., the execution
         * of the method can possibly terminate without a return statement.
         */
        if ((!AnLastStatementIsReturn (Op)) &&
            (!(Op->Asl.CompileFlags & OP_HAS_NO_EXIT)))
        {
            /*
             * No return statement, and execution can possibly exit
             * via this path. This is equivalent to Return ()
             */
            MethodInfo->NumReturnNoValue++;
        }

        /*
         * Check for case where some return statements have a return value
         * and some do not. Exit without a return statement is a return with
         * no value
         */
        if (MethodInfo->NumReturnNoValue &&
            MethodInfo->NumReturnWithValue)
        {
            AslError (ASL_WARNING, ASL_MSG_RETURN_TYPES, Op,
                Op->Asl.ExternalName);
        }

        /*
         * If there are any RETURN() statements with no value, or there is a
         * control path that allows the method to exit without a return value,
         * we mark the method as a method that does not return a value. This
         * knowledge can be used to check method invocations that expect a
         * returned value.
         */
        if (MethodInfo->NumReturnNoValue)
        {
            if (MethodInfo->NumReturnWithValue)
            {
                Op->Asl.CompileFlags |= OP_METHOD_SOME_NO_RETVAL;
            }
            else
            {
                Op->Asl.CompileFlags |= OP_METHOD_NO_RETVAL;
            }
        }

        /*
         * Check predefined method names for correct return behavior
         * and correct number of arguments. Also, some special checks
         * For GPE and _REG methods.
         */
        if (ApCheckForPredefinedMethod (Op, MethodInfo))
        {
            /* Special check for two names like _L01 and _E01 in same scope */

            ApCheckForGpeNameConflict (Op);

            /*
             * Special check for _REG: Must have an operation region definition
             * within the same scope!
             */
            ApCheckRegMethod (Op);
        }

        ACPI_FREE (MethodInfo);
        break;

    case PARSEOP_NAME:

         /* Special check for two names like _L01 and _E01 in same scope */

        ApCheckForGpeNameConflict (Op);
        break;

    case PARSEOP_RETURN:

        /*
         * If the parent is a predefined method name, attempt to typecheck
         * the return value. Only static types can be validated.
         */
        ApCheckPredefinedReturnValue (Op, MethodInfo);

        /*
         * The parent block does not "exit" and continue execution -- the
         * method is terminated here with the Return() statement.
         */
        Op->Asl.Parent->Asl.CompileFlags |= OP_HAS_NO_EXIT;

        /* Used in the "typing" pass later */

        Op->Asl.ParentMethod = MethodInfo->Op;

        /*
         * If there is a peer node after the return statement, then this
         * node is unreachable code -- i.e., it won't be executed because of
         * the preceding Return() statement.
         */
        if (Op->Asl.Next)
        {
            AslError (ASL_WARNING, ASL_MSG_UNREACHABLE_CODE,
                Op->Asl.Next, NULL);
        }
        break;

    case PARSEOP_IF:

        if ((Op->Asl.CompileFlags & OP_HAS_NO_EXIT) &&
            (Op->Asl.Next) &&
            (Op->Asl.Next->Asl.ParseOpcode == PARSEOP_ELSE))
        {
            /*
             * This IF has a corresponding ELSE. The IF block has no exit,
             * (it contains an unconditional Return)
             * mark the ELSE block to remember this fact.
             */
            Op->Asl.Next->Asl.CompileFlags |= OP_IF_HAS_NO_EXIT;
        }
        break;

    case PARSEOP_ELSE:

        if ((Op->Asl.CompileFlags & OP_HAS_NO_EXIT) &&
            (Op->Asl.CompileFlags & OP_IF_HAS_NO_EXIT))
        {
            /*
             * This ELSE block has no exit and the corresponding IF block
             * has no exit either. Therefore, the parent node has no exit.
             */
            Op->Asl.Parent->Asl.CompileFlags |= OP_HAS_NO_EXIT;
        }
        break;


    default:

        if ((Op->Asl.CompileFlags & OP_HAS_NO_EXIT) &&
            (Op->Asl.Parent))
        {
            /* If this node has no exit, then the parent has no exit either */

            Op->Asl.Parent->Asl.CompileFlags |= OP_HAS_NO_EXIT;
        }
        break;
    }

    return (AE_OK);
}