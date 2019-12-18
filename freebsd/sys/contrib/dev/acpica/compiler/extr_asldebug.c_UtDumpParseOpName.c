#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  ParseOpcode; int /*<<< orphan*/  LogicalLineNumber; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_TREE_OUTPUT ; 
 int DEBUG_FULL_LINE_LENGTH ; 
 int DEBUG_MAX_LINE_LENGTH ; 
 int DEBUG_SPACES_PER_INDENT ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
 char* UtGetOpName (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
UtDumpParseOpName (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    UINT32                  DataLength)
{
    char                    *ParseOpName;
    UINT32                  IndentLength;
    UINT32                  NameLength;
    UINT32                  LineLength;
    UINT32                  PaddingLength;


    /* Emit the LineNumber/IndentLevel prefix on each output line */

    DbgPrint (ASL_TREE_OUTPUT,
        "%5.5d [%2d]", Op->Asl.LogicalLineNumber, Level);

    ParseOpName = UtGetOpName (Op->Asl.ParseOpcode);

    /* Calculate various lengths for output alignment */

    IndentLength = Level * DEBUG_SPACES_PER_INDENT;
    NameLength = strlen (ParseOpName);
    LineLength = IndentLength + 1 + NameLength + 1 + DataLength;
    PaddingLength = (DEBUG_MAX_LINE_LENGTH + 1) - LineLength;

    /* Parse tree indentation is based upon the nesting/indent level */

    if (Level)
    {
        DbgPrint (ASL_TREE_OUTPUT, "%*s", IndentLength, " ");
    }

    /* Emit the actual name here */

    DbgPrint (ASL_TREE_OUTPUT, " %s", ParseOpName);

    /* Emit extra padding blanks for alignment of later data items */

    if (LineLength > DEBUG_MAX_LINE_LENGTH)
    {
        /* Split a long line immediately after the ParseOpName string */

        DbgPrint (ASL_TREE_OUTPUT, "\n%*s",
            (DEBUG_FULL_LINE_LENGTH - DataLength), " ");
    }
    else
    {
        DbgPrint (ASL_TREE_OUTPUT, "%*s", PaddingLength, " ");
    }
}