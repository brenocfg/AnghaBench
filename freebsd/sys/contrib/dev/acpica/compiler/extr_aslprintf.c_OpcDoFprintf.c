#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* Next; TYPE_2__* Child; } ;
struct TYPE_7__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  OpcParsePrintf (TYPE_2__*,TYPE_2__*) ; 

void
OpcDoFprintf (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *DestOp;


    /* Store destination is the first argument of fprintf */

    DestOp = Op->Asl.Child;
    Op->Asl.Child = DestOp->Asl.Next;
    DestOp->Asl.Next = NULL;

    OpcParsePrintf (Op, DestOp);
}