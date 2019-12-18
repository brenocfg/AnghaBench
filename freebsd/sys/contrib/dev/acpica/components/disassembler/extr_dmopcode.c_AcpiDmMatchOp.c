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
struct TYPE_6__ {void* DisasmOpcode; TYPE_2__* Next; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 void* ACPI_DASM_MATCHOP ; 
 TYPE_2__* AcpiPsGetDepthNext (int /*<<< orphan*/ *,TYPE_2__*) ; 

void
AcpiDmMatchOp (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *NextOp;


    NextOp = AcpiPsGetDepthNext (NULL, Op);
    NextOp = NextOp->Common.Next;

    if (!NextOp)
    {
        /* Handle partial tree during single-step */

        return;
    }

    /* Mark the two nodes that contain the encoding for the match keywords */

    NextOp->Common.DisasmOpcode = ACPI_DASM_MATCHOP;

    NextOp = NextOp->Common.Next;
    NextOp = NextOp->Common.Next;
    NextOp->Common.DisasmOpcode = ACPI_DASM_MATCHOP;
}