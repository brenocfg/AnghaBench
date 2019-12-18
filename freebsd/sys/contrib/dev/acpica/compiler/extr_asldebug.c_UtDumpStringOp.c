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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_6__ {char* String; } ;
struct TYPE_7__ {scalar_t__ ParseOpcode; char* ExternalName; TYPE_1__ Value; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_TREE_OUTPUT ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ PARSEOP_STRING_LITERAL ; 
 char* UtCreateEscapeSequences (char*) ; 
 int /*<<< orphan*/  UtDumpParseOpName (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
UtDumpStringOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level)
{
    char                    *String;


    String = Op->Asl.Value.String;
    if (Op->Asl.ParseOpcode != PARSEOP_STRING_LITERAL)
    {
        /*
         * For the "path" ops NAMEPATH, NAMESEG, METHODCALL -- if the
         * ExternalName is valid, it takes precedence. In these cases the
         * Value.String is the raw "internal" name from the AML code, which
         * we don't want to use, because it contains non-ascii characters.
         */
        if (Op->Asl.ExternalName)
        {
            String = Op->Asl.ExternalName;
        }
    }

    if (!String)
    {
        DbgPrint (ASL_TREE_OUTPUT,
            " ERROR: Could not find a valid String/Path pointer\n");
        return;
    }

    String = UtCreateEscapeSequences (String);

    /* Emit the ParseOp name, leaving room for the string */

    UtDumpParseOpName (Op, Level, strlen (String));
    DbgPrint (ASL_TREE_OUTPUT, "%s", String);
}