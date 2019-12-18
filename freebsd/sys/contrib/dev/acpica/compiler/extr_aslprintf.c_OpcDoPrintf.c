#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  LogicalLineNumber; TYPE_2__* Parent; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_DEBUG_OP ; 
 int /*<<< orphan*/  OpcParsePrintf (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PARSEOP_DEBUG ; 
 TYPE_2__* TrAllocateOp (int /*<<< orphan*/ ) ; 

void
OpcDoPrintf (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *DestOp;


    /* Store destination is the Debug op */

    DestOp = TrAllocateOp (PARSEOP_DEBUG);
    DestOp->Asl.AmlOpcode = AML_DEBUG_OP;
    DestOp->Asl.Parent = Op;
    DestOp->Asl.LogicalLineNumber = Op->Asl.LogicalLineNumber;

    OpcParsePrintf (Op, DestOp);
}