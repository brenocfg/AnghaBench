#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_10__ {scalar_t__ Integer; } ;
struct TYPE_13__ {int ParseOpcode; int /*<<< orphan*/  CompileFlags; int /*<<< orphan*/  EndLogicalLine; int /*<<< orphan*/  LogicalLineNumber; int /*<<< orphan*/  EndLine; int /*<<< orphan*/  LineNumber; int /*<<< orphan*/  Column; int /*<<< orphan*/  FinalAmlLength; int /*<<< orphan*/  AcpiBtype; int /*<<< orphan*/  Next; int /*<<< orphan*/  Child; TYPE_3__* Parent; int /*<<< orphan*/  AmlSubtreeLength; int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  AmlPkgLenBytes; int /*<<< orphan*/  AmlOpcodeLength; int /*<<< orphan*/  AmlOpcode; TYPE_1__ Value; } ;
struct TYPE_14__ {TYPE_4__ Asl; } ;
struct TYPE_11__ {int /*<<< orphan*/  AmlSubtreeLength; } ;
struct TYPE_12__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_PARSE_TREE_DEBUG2 ; 
 char* ASL_PARSE_TREE_HEADER2 ; 
 int /*<<< orphan*/  ASL_TREE_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_DebugFlag ; 
 int /*<<< orphan*/  CgWriteNode (TYPE_5__*) ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,...) ; 
#define  PARSEOP_METHODCALL 131 
#define  PARSEOP_NAMESEG 130 
#define  PARSEOP_NAMESTRING 129 
#define  PARSEOP_STRING_LITERAL 128 
 int /*<<< orphan*/  TrPrintOpFlags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtDumpBasicOp (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UtDumpStringOp (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
CgAmlWriteWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    /* Generate the AML for this node */

    CgWriteNode (Op);

    if (!AslGbl_DebugFlag)
    {
        return (AE_OK);
    }

    /* Print header at level 0. Alignment assumes 32-bit pointers */

    if (!Level)
    {
        DbgPrint (ASL_TREE_OUTPUT,
            "\nFinal parse tree used for AML output:\n");
        DbgPrint (ASL_TREE_OUTPUT, ASL_PARSE_TREE_HEADER2);
    }

    /* Dump ParseOp name and possible value */

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_NAMESEG:
    case PARSEOP_NAMESTRING:
    case PARSEOP_METHODCALL:
    case PARSEOP_STRING_LITERAL:

        UtDumpStringOp (Op, Level);
        break;

    default:

        UtDumpBasicOp (Op, Level);
        break;
    }

    DbgPrint (ASL_TREE_OUTPUT, ASL_PARSE_TREE_DEBUG2,
        /* 1  */ (UINT32) Op->Asl.Value.Integer,
        /* 2  */ Op->Asl.ParseOpcode,
        /* 3  */ Op->Asl.AmlOpcode,
        /* 4  */ Op->Asl.AmlOpcodeLength,
        /* 5  */ Op->Asl.AmlPkgLenBytes,
        /* 6  */ Op->Asl.AmlLength,
        /* 7  */ Op->Asl.AmlSubtreeLength,
        /* 8  */ Op->Asl.Parent ? Op->Asl.Parent->Asl.AmlSubtreeLength : 0,
        /* 9  */ Op,
        /* 10 */ Op->Asl.Parent,
        /* 11 */ Op->Asl.Child,
        /* 12 */ Op->Asl.Next,
        /* 13 */ Op->Asl.CompileFlags,
        /* 14 */ Op->Asl.AcpiBtype,
        /* 15 */ Op->Asl.FinalAmlLength,
        /* 16 */ Op->Asl.Column,
        /* 17 */ Op->Asl.LineNumber,
        /* 18 */ Op->Asl.EndLine,
        /* 19 */ Op->Asl.LogicalLineNumber,
        /* 20 */ Op->Asl.EndLogicalLine);

    TrPrintOpFlags (Op->Asl.CompileFlags, ASL_TREE_OUTPUT);
    DbgPrint (ASL_TREE_OUTPUT, "\n");
    return (AE_OK);
}