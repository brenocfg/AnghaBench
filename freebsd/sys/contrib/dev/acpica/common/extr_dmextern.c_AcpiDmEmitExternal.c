#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  Path; } ;
struct TYPE_7__ {scalar_t__ Integer; } ;
struct TYPE_8__ {TYPE_1__ Value; } ;
struct TYPE_10__ {TYPE_3__ Named; TYPE_2__ Common; } ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmCheckForExternalConflict (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmGetObjectTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmNamestring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmEmitExternal (
    ACPI_PARSE_OBJECT       *NameOp,
    ACPI_PARSE_OBJECT       *TypeOp)
{
    AcpiOsPrintf ("External (");
    AcpiDmNamestring (NameOp->Named.Path);
    AcpiOsPrintf ("%s)",
        AcpiDmGetObjectTypeName ((ACPI_OBJECT_TYPE) TypeOp->Common.Value.Integer));
    AcpiDmCheckForExternalConflict (NameOp->Named.Path);
    AcpiOsPrintf ("\n");
}