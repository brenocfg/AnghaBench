#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int /*<<< orphan*/  Child; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
struct TYPE_7__ {void* ParserErrorDetected; } ;
typedef  TYPE_2__ ASL_GLOBAL_FILE_NODE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int /*<<< orphan*/  ASL_DEFINE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_TWICE ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_UPWARD ; 
 int /*<<< orphan*/  AslCompilerparse () ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int AslGbl_CurrentLineNumber ; 
 int AslGbl_LogicalLineNumber ; 
 TYPE_3__* AslGbl_ParseTreeRoot ; 
 void* AslGbl_ParserErrorDetected ; 
 scalar_t__ AslGbl_PreprocessFlag ; 
 scalar_t__ AslGbl_PreprocessOnly ; 
 int /*<<< orphan*/  AslGbl_PruneDepth ; 
 scalar_t__ AslGbl_PruneParseTree ; 
 int /*<<< orphan*/  AslGbl_PruneType ; 
 scalar_t__ AslGbl_SyntaxError ; 
 int /*<<< orphan*/  AslPruneParseTree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CmFlushSourceCode () ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* FlGetCurrentFileNode () ; 
 int /*<<< orphan*/  LsDumpParseTree () ; 
 int /*<<< orphan*/  OpcAmlOpcodeWalk ; 
 int /*<<< orphan*/  OpcGetIntegerWidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrAddDefine (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrDoPreprocess () ; 
 void* TRUE ; 
 int /*<<< orphan*/ * TrAmlTransformWalkBegin ; 
 int /*<<< orphan*/  TrAmlTransformWalkEnd ; 
 int /*<<< orphan*/  TrWalkParseTree (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtBeginEvent (char*) ; 
 int /*<<< orphan*/  UtEndEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

ACPI_STATUS
CmDoCompile (
    void)
{
    UINT8                   FullCompile;
    UINT8                   Event;
    ASL_GLOBAL_FILE_NODE    *FileNode;


    FullCompile = UtBeginEvent ("*** Total Compile time ***");
    Event = UtBeginEvent ("Open input and output files");
    UtEndEvent (Event);

    Event = UtBeginEvent ("Preprocess input file");
    if (AslGbl_PreprocessFlag)
    {
        /* Enter compiler name as a #define */

        PrAddDefine (ASL_DEFINE, "", FALSE);

        /* Preprocessor */

        PrDoPreprocess ();
        AslGbl_CurrentLineNumber = 1;
        AslGbl_LogicalLineNumber = 1;

        if (AslGbl_PreprocessOnly)
        {
            UtEndEvent (Event);
            return (AE_OK);
        }
    }
    UtEndEvent (Event);


    /* Build the parse tree */

    Event = UtBeginEvent ("Parse source code and build parse tree");
    AslCompilerparse();
    UtEndEvent (Event);

    /* Check for parser-detected syntax errors */

    if (AslGbl_SyntaxError)
    {
        fprintf (stderr,
            "Compiler aborting due to parser-detected syntax error(s)\n");

        /* Flag this error in the FileNode for compilation summary */

        FileNode = FlGetCurrentFileNode ();
        FileNode->ParserErrorDetected = TRUE;
        AslGbl_ParserErrorDetected = TRUE;
        LsDumpParseTree ();
        goto ErrorExit;
    }

    /* Did the parse tree get successfully constructed? */

    if (!AslGbl_ParseTreeRoot)
    {
        /*
         * If there are no errors, then we have some sort of
         * internal problem.
         */
        AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL,
            NULL, "- Could not resolve parse tree root node");

        goto ErrorExit;
    }

    /* Flush out any remaining source after parse tree is complete */

    Event = UtBeginEvent ("Flush source input");
    CmFlushSourceCode ();

    /* Prune the parse tree if requested (debug purposes only) */

    if (AslGbl_PruneParseTree)
    {
        AslPruneParseTree (AslGbl_PruneDepth, AslGbl_PruneType);
    }

    /* Optional parse tree dump, compiler debug output only */

    LsDumpParseTree ();

    OpcGetIntegerWidth (AslGbl_ParseTreeRoot->Asl.Child);
    UtEndEvent (Event);

    /* Pre-process parse tree for any operator transforms */

    Event = UtBeginEvent ("Parse tree transforms");
    DbgPrint (ASL_DEBUG_OUTPUT, "\nParse tree transforms\n\n");
    TrWalkParseTree (AslGbl_ParseTreeRoot, ASL_WALK_VISIT_TWICE,
        TrAmlTransformWalkBegin, TrAmlTransformWalkEnd, NULL);
    UtEndEvent (Event);

    /* Generate AML opcodes corresponding to the parse tokens */

    Event = UtBeginEvent ("Generate AML opcodes");
    DbgPrint (ASL_DEBUG_OUTPUT, "Generating AML opcodes\n\n");
    TrWalkParseTree (AslGbl_ParseTreeRoot, ASL_WALK_VISIT_UPWARD, NULL,
        OpcAmlOpcodeWalk, NULL);
    UtEndEvent (Event);

    UtEndEvent (FullCompile);
    return (AE_OK);

ErrorExit:
    UtEndEvent (FullCompile);
    return (AE_ERROR);
}