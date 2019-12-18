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
typedef  int UINT32 ;
struct TYPE_6__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_7__ {TYPE_1__ Value; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_TREE_OUTPUT ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  UtDumpParseOpName (TYPE_3__*,int,int) ; 

void
UtDumpIntegerOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    UINT32                  IntegerLength)
{

    /* Emit the ParseOp name, leaving room for the integer */

    UtDumpParseOpName (Op, Level, IntegerLength);

    /* Emit the integer based upon length */

    switch (IntegerLength)
    {
    case 2: /* Byte */
    case 4: /* Word */
    case 8: /* Dword */

        DbgPrint (ASL_TREE_OUTPUT,
            "%*.*X", IntegerLength, IntegerLength, (UINT32) Op->Asl.Value.Integer);
        break;

    case 16: /* Qword and Integer */

        DbgPrint (ASL_TREE_OUTPUT,
            "%8.8X%8.8X", ACPI_FORMAT_UINT64 (Op->Asl.Value.Integer));
        break;

    default:
        break;
    }
}