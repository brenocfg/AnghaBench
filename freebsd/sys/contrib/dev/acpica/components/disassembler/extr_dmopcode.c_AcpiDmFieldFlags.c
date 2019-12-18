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
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_5__ {scalar_t__ Integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  DisasmFlags; TYPE_1__ Value; TYPE_3__* Next; } ;
struct TYPE_7__ {TYPE_2__ Common; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PARSEOP_IGNORE ; 
 int /*<<< orphan*/ * AcpiGbl_AccessTypes ; 
 int /*<<< orphan*/ * AcpiGbl_LockRule ; 
 int /*<<< orphan*/ * AcpiGbl_UpdateRules ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 

void
AcpiDmFieldFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Flags;


    Op = Op->Common.Next;
    Flags = (UINT8) Op->Common.Value.Integer;

    /* Mark the Op as completed */

    Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;

    AcpiOsPrintf ("%s, ", AcpiGbl_AccessTypes [Flags & 0x07]);
    AcpiOsPrintf ("%s, ", AcpiGbl_LockRule [(Flags & 0x10) >> 4]);
    AcpiOsPrintf ("%s)",  AcpiGbl_UpdateRules [(Flags & 0x60) >> 5]);
}