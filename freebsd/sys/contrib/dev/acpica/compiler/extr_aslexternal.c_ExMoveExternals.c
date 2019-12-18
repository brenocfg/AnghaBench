#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_9__ {scalar_t__ Integer; int /*<<< orphan*/  String; } ;
struct TYPE_10__ {char* ExternalName; char* Namepath; scalar_t__ ParseOpcode; int CompileFlags; TYPE_3__* Parent; TYPE_3__* Next; TYPE_3__* Child; scalar_t__ LogicalLineNumber; scalar_t__ LineNumber; int /*<<< orphan*/  AmlOpcode; TYPE_1__ Value; int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  Node; } ;
struct TYPE_11__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AML_IF_OP ; 
 int /*<<< orphan*/  AML_ZERO_OP ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 char* AcpiNsGetNormalizedPathname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 TYPE_3__* AslGbl_ExternalsListHead ; 
 int OP_AML_PACKAGE ; 
 int OP_VISITED ; 
 scalar_t__ PARSEOP_IF ; 
 scalar_t__ PARSEOP_NAMESEG ; 
 scalar_t__ PARSEOP_NAMESTRING ; 
 int /*<<< orphan*/  PARSEOP_ZERO ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* TrAllocateOp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtInternalizeName (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExMoveExternals (
    ACPI_PARSE_OBJECT       *DefinitionBlockOp)
{
    ACPI_PARSE_OBJECT       *ParentOp;
    ACPI_PARSE_OBJECT       *ExternalOp;
    ACPI_PARSE_OBJECT       *PredicateOp;
    ACPI_PARSE_OBJECT       *NextOp;
    ACPI_PARSE_OBJECT       *Prev;
    ACPI_PARSE_OBJECT       *Next;
    char                    *ExternalName;
    ACPI_OBJECT_TYPE        ObjType;
    ACPI_STATUS             Status;
    UINT32                  i;


    if (!AslGbl_ExternalsListHead)
    {
        return;
    }

    /* Remove the External nodes from the tree */

    NextOp = AslGbl_ExternalsListHead;
    while (NextOp)
    {
        /*
         * The External is stored in child pointer of each node in the
         * list
         */
        ExternalOp = NextOp->Asl.Child;

        /* Get/set the fully qualified name */

        ExternalName = AcpiNsGetNormalizedPathname (ExternalOp->Asl.Node, TRUE);
        ExternalOp->Asl.ExternalName = ExternalName;
        ExternalOp->Asl.Namepath = ExternalName;

        /* Set line numbers (for listings, etc.) */

        ExternalOp->Asl.LineNumber = 0;
        ExternalOp->Asl.LogicalLineNumber = 0;

        Next = ExternalOp->Asl.Child;
        Next->Asl.LineNumber = 0;
        Next->Asl.LogicalLineNumber = 0;

        if (Next->Asl.ParseOpcode == PARSEOP_NAMESEG)
        {
            Next->Asl.ParseOpcode = PARSEOP_NAMESTRING;
        }

        Next->Asl.ExternalName = ExternalName;
        Status = UtInternalizeName (ExternalName, &Next->Asl.Value.String);
        if (ACPI_FAILURE (Status))
        {
            AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL,
                Next, "Could not internalize namestring");
            return;
        }

        Next->Asl.AmlLength = strlen (Next->Asl.Value.String);

        Next = Next->Asl.Next;
        Next->Asl.LineNumber = 0;
        Next->Asl.LogicalLineNumber = 0;

        Next = Next->Asl.Next;
        Next->Asl.LineNumber = 0;
        Next->Asl.LogicalLineNumber = 0;

        Next = Next->Asl.Next;
        Next->Asl.LineNumber = 0;
        Next->Asl.LogicalLineNumber = 0;

        ParentOp = ExternalOp->Asl.Parent;
        Prev = Next = ParentOp->Asl.Child;

        /* Now find the External node's position in parse tree */

        while (Next != ExternalOp)
        {
            Prev = Next;
            Next = Next->Asl.Next;
        }

        /* Remove the External from the parse tree */

        if (Prev == ExternalOp)
        {
            /* External was the first child node */

            ParentOp->Asl.Child = ExternalOp->Asl.Next;
        }

        Prev->Asl.Next = ExternalOp->Asl.Next;
        ExternalOp->Asl.Next = NULL;
        ExternalOp->Asl.Parent = AslGbl_ExternalsListHead;

        /* Point the External to the next in the list */

        if (NextOp->Asl.Next)
        {
            ExternalOp->Asl.Next = NextOp->Asl.Next->Asl.Child;
        }

        NextOp = NextOp->Asl.Next;
    }

    /*
     * Loop again to remove MethodObj Externals for which
     * a MethodCall was not found (dead external reference)
     */
    Prev = AslGbl_ExternalsListHead->Asl.Child;
    Next = Prev;
    while (Next)
    {
        ObjType = (ACPI_OBJECT_TYPE)
            Next->Asl.Child->Asl.Next->Asl.Value.Integer;

        if (ObjType == ACPI_TYPE_METHOD &&
            !(Next->Asl.CompileFlags & OP_VISITED))
        {
            if (Next == Prev)
            {
                AslGbl_ExternalsListHead->Asl.Child = Next->Asl.Next;
                Next->Asl.Next = NULL;
                Prev = AslGbl_ExternalsListHead->Asl.Child;
                Next = Prev;
                continue;
            }
            else
            {
                Prev->Asl.Next = Next->Asl.Next;
                Next->Asl.Next = NULL;
                Next = Prev->Asl.Next;
                continue;
            }
        }

        Prev = Next;
        Next = Next->Asl.Next;
    }

    /* If list is now empty, don't bother to make If (0) block */

    if (!AslGbl_ExternalsListHead->Asl.Child)
    {
        return;
    }

    /* Convert Gbl_ExternalsListHead parent to If(). */

    AslGbl_ExternalsListHead->Asl.ParseOpcode = PARSEOP_IF;
    AslGbl_ExternalsListHead->Asl.AmlOpcode = AML_IF_OP;
    AslGbl_ExternalsListHead->Asl.CompileFlags = OP_AML_PACKAGE;
    UtSetParseOpName (AslGbl_ExternalsListHead);

    /* Create a Zero op for the If predicate */

    PredicateOp = TrAllocateOp (PARSEOP_ZERO);
    PredicateOp->Asl.AmlOpcode = AML_ZERO_OP;

    PredicateOp->Asl.Parent = AslGbl_ExternalsListHead;
    PredicateOp->Asl.Child = NULL;
    PredicateOp->Asl.Next = AslGbl_ExternalsListHead->Asl.Child;
    AslGbl_ExternalsListHead->Asl.Child = PredicateOp;

    /* Set line numbers (for listings, etc.) */

    AslGbl_ExternalsListHead->Asl.LineNumber = 0;
    AslGbl_ExternalsListHead->Asl.LogicalLineNumber = 0;

    PredicateOp->Asl.LineNumber = 0;
    PredicateOp->Asl.LogicalLineNumber = 0;

    /* Insert block back in the list */

    Prev = DefinitionBlockOp->Asl.Child;
    Next = Prev;

    /* Find last default arg */

    for (i = 0; i < 6; i++)
    {
        Prev = Next;
        Next = Prev->Asl.Next;
    }

    if (Next)
    {
        /* Definition Block is not empty */

        AslGbl_ExternalsListHead->Asl.Next = Next;
    }
    else
    {
        /* Definition Block is empty. */

        AslGbl_ExternalsListHead->Asl.Next = NULL;
    }

    Prev->Asl.Next = AslGbl_ExternalsListHead;
    AslGbl_ExternalsListHead->Asl.Parent = Prev->Asl.Parent;
}