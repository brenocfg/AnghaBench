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
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {scalar_t__ Integer; } ;
struct TYPE_6__ {TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Common; } ;
typedef  size_t ACPI_SIZE ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_MAX_MATCH_OPCODE ; 
 int /*<<< orphan*/ * AcpiGbl_MatchOps ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

__attribute__((used)) static void
AcpiDmMatchKeyword (
    ACPI_PARSE_OBJECT       *Op)
{

    if (((UINT32) Op->Common.Value.Integer) > ACPI_MAX_MATCH_OPCODE)
    {
        AcpiOsPrintf ("/* Unknown Match Keyword encoding */");
    }
    else
    {
        AcpiOsPrintf ("%s",
            AcpiGbl_MatchOps[(ACPI_SIZE) Op->Common.Value.Integer]);
    }
}