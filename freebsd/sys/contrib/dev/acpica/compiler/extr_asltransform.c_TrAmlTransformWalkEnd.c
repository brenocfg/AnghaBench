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
struct TYPE_5__ {int /*<<< orphan*/ * Arg; } ;
struct TYPE_6__ {scalar_t__ ParseOpcode; TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * AslGbl_ExternalsListHead ; 
 scalar_t__ PARSEOP_DEFINITION_BLOCK ; 

ACPI_STATUS
TrAmlTransformWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    /* Save possible Externals list in the DefintionBlock Op */

    if (Op->Asl.ParseOpcode == PARSEOP_DEFINITION_BLOCK)
    {
        Op->Asl.Value.Arg = AslGbl_ExternalsListHead;
        AslGbl_ExternalsListHead = NULL;
    }

    return (AE_OK);
}