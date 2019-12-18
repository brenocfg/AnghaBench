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
 int /*<<< orphan*/  OpnDoPackage (TYPE_2__*) ; 
 scalar_t__ PARSEOP_VAR_PACKAGE ; 

ACPI_STATUS
OpcAmlOpcodeUpdateWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    /*
     * Handle the Package() case where the actual opcode cannot be determined
     * until the PackageLength operand has been folded and minimized.
     * (PackageOp versus VarPackageOp)
     *
     * This is (as of ACPI 3.0) the only case where the AML opcode can change
     * based upon the value of a parameter.
     *
     * The parser always inserts a VarPackage opcode, which can possibly be
     * optimized to a Package opcode.
     */
    if (Op->Asl.ParseOpcode == PARSEOP_VAR_PACKAGE)
    {
        OpnDoPackage (Op);
    }

    return (AE_OK);
}