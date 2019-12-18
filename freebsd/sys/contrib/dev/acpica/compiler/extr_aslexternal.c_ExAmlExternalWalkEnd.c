#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {scalar_t__ ParseOpcode; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * AslGbl_ExternalsListHead ; 
 int /*<<< orphan*/  ExMoveExternals (TYPE_2__*) ; 
 scalar_t__ PARSEOP_DEFINITION_BLOCK ; 

ACPI_STATUS
ExAmlExternalWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    if (Op->Asl.ParseOpcode == PARSEOP_DEFINITION_BLOCK)
    {
        /*
         * Process any existing external list. (Support for
         * multiple definition blocks in a single file/compile)
         */
        ExMoveExternals (Op);
        AslGbl_ExternalsListHead = NULL;
    }

    return (AE_OK);
}