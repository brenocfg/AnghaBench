#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_32__ {char* String; } ;
struct TYPE_33__ {int CompileFlags; scalar_t__ AmlOpcode; scalar_t__ AmlLength; TYPE_6__ Value; TYPE_9__* Next; TYPE_9__* Child; int /*<<< orphan*/ * Node; TYPE_9__* Parent; int /*<<< orphan*/  LogicalLineNumber; } ;
struct TYPE_29__ {int /*<<< orphan*/  AmlOpcode; TYPE_2__* Parent; } ;
struct TYPE_35__ {TYPE_7__ Asl; TYPE_3__ Common; } ;
struct TYPE_34__ {TYPE_5__* ScopeInfo; } ;
struct TYPE_30__ {int /*<<< orphan*/ * Node; } ;
struct TYPE_31__ {TYPE_4__ Scope; } ;
struct TYPE_27__ {int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_28__ {TYPE_1__ Common; } ;
struct TYPE_26__ {char* Pointer; void* Length; } ;
typedef  TYPE_8__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_9__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_10__ ACPI_BUFFER ;

/* Variables and functions */
 void* ACPI_ALLOCATE_LOCAL_BUFFER ; 
 int /*<<< orphan*/  ACPI_DB_OPTIMIZATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (void (*) (TYPE_9__*,int,TYPE_8__*,char*,int /*<<< orphan*/ *)) ; 
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 scalar_t__ AML_ALIAS_OP ; 
 int AML_CREATE ; 
 int AML_NAMED ; 
 int /*<<< orphan*/  ASL_NO_ABORT ; 
 int /*<<< orphan*/ * AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiNsExternalizeName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  AcpiNsHandleToPathname (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslCoreSubsystemError (TYPE_9__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_ReferenceOptimizationFlag ; 
 int /*<<< orphan*/  FALSE ; 
 int OP_IS_NAME_DECLARATION ; 
 int /*<<< orphan*/  OptBuildShortestPath (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_10__*,TYPE_10__*,scalar_t__,int,char**) ; 
 int /*<<< orphan*/  OptOptimizeNameDeclaration (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  OptSearchToRoot (TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_10__*,char**) ; 
 int /*<<< orphan*/  OptTotal ; 
 int /*<<< orphan*/  return_VOID ; 
 scalar_t__ strlen (char*) ; 

void
OptOptimizeNamePath (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Flags,
    ACPI_WALK_STATE         *WalkState,
    char                    *AmlNameString,
    ACPI_NAMESPACE_NODE     *TargetNode)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             TargetPath;
    ACPI_BUFFER             CurrentPath;
    ACPI_SIZE               AmlNameStringLength;
    ACPI_NAMESPACE_NODE     *CurrentNode;
    char                    *ExternalNameString;
    char                    *NewPath = NULL;
    ACPI_SIZE               HowMuchShorter;
    ACPI_PARSE_OBJECT       *NextOp;


    ACPI_FUNCTION_TRACE (OptOptimizeNamePath);


    /* This is an optional optimization */

    if (!AslGbl_ReferenceOptimizationFlag)
    {
        return_VOID;
    }

    /* Various required items */

    if (!TargetNode || !WalkState || !AmlNameString || !Op->Common.Parent)
    {
        return_VOID;
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
        "PATH OPTIMIZE: Line %5d ParentOp [%12.12s] ThisOp [%12.12s] ",
        Op->Asl.LogicalLineNumber,
        AcpiPsGetOpcodeName (Op->Common.Parent->Common.AmlOpcode),
        AcpiPsGetOpcodeName (Op->Common.AmlOpcode)));

    if (!(Flags & (AML_NAMED | AML_CREATE)))
    {
        if (Op->Asl.CompileFlags & OP_IS_NAME_DECLARATION)
        {
            /* We don't want to fuss with actual name declaration nodes here */

            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
                "******* NAME DECLARATION\n"));
            return_VOID;
        }
    }

    /*
     * The original path must be longer than one NameSeg (4 chars) for there
     * to be any possibility that it can be optimized to a shorter string
     */
    AmlNameStringLength = strlen (AmlNameString);
    if (AmlNameStringLength <= ACPI_NAMESEG_SIZE)
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
            "NAMESEG %4.4s\n", AmlNameString));
        return_VOID;
    }

    /*
     * We need to obtain the node that represents the current scope -- where
     * we are right now in the namespace. We will compare this path
     * against the Namepath, looking for commonality.
     */
    CurrentNode = AcpiGbl_RootNode;
    if (WalkState->ScopeInfo)
    {
        CurrentNode = WalkState->ScopeInfo->Scope.Node;
    }

    if (Flags & (AML_NAMED | AML_CREATE))
    {
        /* This is the declaration of a new name */

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "NAME\n"));

        /*
         * The node of interest is the parent of this node (the containing
         * scope). The actual namespace node may be up more than one level
         * of parse op or it may not exist at all (if we traverse back
         * up to the root.)
         */
        NextOp = Op->Asl.Parent;
        while (NextOp && (!NextOp->Asl.Node))
        {
            NextOp = NextOp->Asl.Parent;
        }

        if (NextOp && NextOp->Asl.Node)
        {
            CurrentNode = NextOp->Asl.Node;
        }
        else
        {
            CurrentNode = AcpiGbl_RootNode;
        }
    }
    else
    {
        /* This is a reference to an existing named object */

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "REFERENCE\n"));
    }

    /*
     * Obtain the full paths to the two nodes that we are interested in
     * (Target and current namespace location) in external
     * format -- something we can easily manipulate
     */
    TargetPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (TargetNode, &TargetPath, FALSE);
    if (ACPI_FAILURE (Status))
    {
        AslCoreSubsystemError (Op, Status, "Getting Target NamePath",
            ASL_NO_ABORT);
        return_VOID;
    }

    TargetPath.Length--;    /* Subtract one for null terminator */

    /* CurrentPath is the path to this scope (where we are in the namespace) */

    CurrentPath.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (CurrentNode, &CurrentPath, FALSE);
    if (ACPI_FAILURE (Status))
    {
        AslCoreSubsystemError (Op, Status, "Getting Current NamePath",
            ASL_NO_ABORT);
        return_VOID;
    }

    CurrentPath.Length--;   /* Subtract one for null terminator */

    /* Debug output only */

    Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, AmlNameString,
        NULL, &ExternalNameString);
    if (ACPI_FAILURE (Status))
    {
        AslCoreSubsystemError (Op, Status, "Externalizing NamePath",
            ASL_NO_ABORT);
        return_VOID;
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
        "CURRENT SCOPE: (%2u) %-37s FULL PATH TO NAME: (%2u) %-32s ACTUAL AML:%-32s\n",
        (UINT32) CurrentPath.Length, (char *) CurrentPath.Pointer,
        (UINT32) TargetPath.Length, (char *) TargetPath.Pointer,
        ExternalNameString));

    ACPI_FREE (ExternalNameString);

    /*
     * Attempt an optimization depending on the type of namepath
     */
    if (Flags & (AML_NAMED | AML_CREATE))
    {
        /*
         * This is a named opcode and the namepath is a name declaration, not
         * a reference.
         */
        Status = OptOptimizeNameDeclaration (Op, WalkState, CurrentNode,
            TargetNode, AmlNameString, &NewPath);
        if (ACPI_FAILURE (Status))
        {
            /*
             * 2) now attempt to
             *    optimize the namestring with carats (up-arrow)
             */
            Status = OptBuildShortestPath (Op, WalkState, CurrentNode,
                TargetNode, &CurrentPath, &TargetPath,
                AmlNameStringLength, 1, &NewPath);
        }
    }
    else
    {
        /*
         * This is a reference to an existing named object
         *
         * 1) Check if search-to-root can be utilized using the last
         *    NameSeg of the NamePath
         */
        Status = OptSearchToRoot (Op, WalkState, CurrentNode,
            TargetNode, &TargetPath, &NewPath);
        if (ACPI_FAILURE (Status))
        {
            /*
             * 2) Search-to-root could not be used, now attempt to
             *    optimize the namestring with carats (up-arrow)
             */
            Status = OptBuildShortestPath (Op, WalkState, CurrentNode,
                TargetNode, &CurrentPath, &TargetPath,
                AmlNameStringLength, 0, &NewPath);
        }
    }

    /*
     * Success from above indicates that the NamePath was successfully
     * optimized. We need to update the parse op with the new name
     */
    if (ACPI_SUCCESS (Status))
    {
        HowMuchShorter = (AmlNameStringLength - strlen (NewPath));
        OptTotal += HowMuchShorter;

        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
            " REDUCED BY %2u (TOTAL SAVED %2u)",
            (UINT32) HowMuchShorter, OptTotal));

        if (Flags & AML_NAMED)
        {
            if (Op->Asl.AmlOpcode == AML_ALIAS_OP)
            {
                /*
                 * ALIAS is the only oddball opcode, the name declaration
                 * (alias name) is the second operand
                 */
                Op->Asl.Child->Asl.Next->Asl.Value.String = NewPath;
                Op->Asl.Child->Asl.Next->Asl.AmlLength = strlen (NewPath);
            }
            else
            {
                Op->Asl.Child->Asl.Value.String = NewPath;
                Op->Asl.Child->Asl.AmlLength = strlen (NewPath);
            }
        }
        else if (Flags & AML_CREATE)
        {
            /* Name must appear as the last parameter */

            NextOp = Op->Asl.Child;
            while (!(NextOp->Asl.CompileFlags & OP_IS_NAME_DECLARATION))
            {
                NextOp = NextOp->Asl.Next;
            }
            /* Update the parse node with the new NamePath */

            NextOp->Asl.Value.String = NewPath;
            NextOp->Asl.AmlLength = strlen (NewPath);
        }
        else
        {
            /* Update the parse node with the new NamePath */

            Op->Asl.Value.String = NewPath;
            Op->Asl.AmlLength = strlen (NewPath);
        }
    }
    else
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, " ALREADY OPTIMAL"));
    }

    /* Cleanup path buffers */

    ACPI_FREE (TargetPath.Pointer);
    ACPI_FREE (CurrentPath.Pointer);

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS, "\n"));
    return_VOID;
}