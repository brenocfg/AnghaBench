#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_10__ {int AmlLength; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_8__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_9__ {TYPE_1__ Value; } ;
struct TYPE_11__ {TYPE_3__ Asl; TYPE_2__ Common; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RAW_DATA_BYTE ; 
 int /*<<< orphan*/  AML_RAW_DATA_DWORD ; 
 int /*<<< orphan*/  AML_RAW_DATA_QWORD ; 
 int /*<<< orphan*/  AML_RAW_DATA_WORD ; 
 int /*<<< orphan*/  OpcSetOptimalIntegerSize (TYPE_4__*) ; 
 int /*<<< orphan*/  PARSEOP_BYTECONST ; 
 int /*<<< orphan*/  PARSEOP_DWORDCONST ; 
 int /*<<< orphan*/  PARSEOP_INTEGER ; 
 int /*<<< orphan*/  PARSEOP_QWORDCONST ; 
 int /*<<< orphan*/  PARSEOP_WORDCONST ; 
 int /*<<< orphan*/  TrSetOpIntegerValue (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
OpcUpdateIntegerNode (
    ACPI_PARSE_OBJECT       *Op,
    UINT64                  Value)
{

    Op->Common.Value.Integer = Value;

    /*
     * The AmlLength is used by the parser to indicate a constant,
     * (if non-zero). Length is either (1/2/4/8)
     */
    switch (Op->Asl.AmlLength)
    {
    case 1:

        TrSetOpIntegerValue (PARSEOP_BYTECONST, Op);
        Op->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
        break;

    case 2:

        TrSetOpIntegerValue (PARSEOP_WORDCONST, Op);
        Op->Asl.AmlOpcode = AML_RAW_DATA_WORD;
        break;

    case 4:

        TrSetOpIntegerValue (PARSEOP_DWORDCONST, Op);
        Op->Asl.AmlOpcode = AML_RAW_DATA_DWORD;
        break;

    case 8:

        TrSetOpIntegerValue (PARSEOP_QWORDCONST, Op);
        Op->Asl.AmlOpcode = AML_RAW_DATA_QWORD;
        break;

    case 0:
    default:

        OpcSetOptimalIntegerSize (Op);
        TrSetOpIntegerValue (PARSEOP_INTEGER, Op);
        break;
    }

    Op->Asl.AmlLength = 0;
}