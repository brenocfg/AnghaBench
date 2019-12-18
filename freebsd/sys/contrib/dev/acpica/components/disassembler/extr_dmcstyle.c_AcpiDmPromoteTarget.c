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
struct TYPE_6__ {TYPE_3__* Arg; } ;
struct TYPE_7__ {TYPE_3__* Next; TYPE_1__ Value; } ;
struct TYPE_8__ {TYPE_2__ Common; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */

__attribute__((used)) static void
AcpiDmPromoteTarget (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_PARSE_OBJECT       *Target)
{
    ACPI_PARSE_OBJECT       *Child;


    /* Link target directly to the Op as first child */

    Child = Op->Common.Value.Arg;
    Op->Common.Value.Arg = Target;
    Target->Common.Next = Child;

    /* Find the last peer, it is linked to the target. Unlink it. */

    while (Child->Common.Next != Target)
    {
        Child = Child->Common.Next;
    }

    Child->Common.Next = NULL;
}