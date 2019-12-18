#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * Arg; } ;
struct TYPE_6__ {scalar_t__ AmlOpcode; TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Common; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ AML_INT_NAMEPATH_OP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
AcpiDmIsValidTarget (
    ACPI_PARSE_OBJECT       *Target)
{

    if (!Target)
    {
        return (FALSE);
    }

    if ((Target->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
        (Target->Common.Value.Arg == NULL))
    {
        return (FALSE);
    }

    return (TRUE);
}