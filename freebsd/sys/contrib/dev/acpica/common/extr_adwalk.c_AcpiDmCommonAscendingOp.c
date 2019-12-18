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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  WalkState; } ;
struct TYPE_5__ {int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_OP_WALK_INFO ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDsScopeStackPop (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiNsOpensScope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslMapNamedOpcodeToDataType (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmCommonAscendingOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_OP_WALK_INFO       *Info = Context;
    ACPI_OBJECT_TYPE        ObjectType;


    /* Close scope if necessary */

    ObjectType = AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode);

    if (AcpiNsOpensScope (ObjectType))
    {
        (void) AcpiDsScopeStackPop (Info->WalkState);
    }

    return (AE_OK);
}