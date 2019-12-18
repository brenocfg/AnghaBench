#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {int Flags; int /*<<< orphan*/  ObjectType; } ;
struct TYPE_7__ {scalar_t__ ParseOpcode; int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  AE_OK ; 
 int AML_NAMED ; 
 int /*<<< orphan*/  AcpiDsScopeStackPop (int /*<<< orphan*/ *) ; 
 scalar_t__ AcpiNsOpensScope (int /*<<< orphan*/ ) ; 
 TYPE_3__* AcpiPsGetOpcodeInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslMapNamedOpcodeToDataType (int /*<<< orphan*/ ) ; 
 scalar_t__ PARSEOP_EXTERNAL ; 
 scalar_t__ PARSEOP_METHODCALL ; 
 scalar_t__ PARSEOP_NAMESEG ; 
 scalar_t__ PARSEOP_NAMESTRING ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
XfNamespaceLocateEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    const ACPI_OPCODE_INFO  *OpInfo;


    ACPI_FUNCTION_TRACE (XfNamespaceLocateEnd);


    /* We are only interested in opcodes that have an associated name */

    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);
    if (!(OpInfo->Flags & AML_NAMED))
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Not interested in name references, we did not open a scope for them */

    if ((Op->Asl.ParseOpcode == PARSEOP_NAMESTRING) ||
        (Op->Asl.ParseOpcode == PARSEOP_NAMESEG)    ||
        (Op->Asl.ParseOpcode == PARSEOP_METHODCALL) ||
        (Op->Asl.ParseOpcode == PARSEOP_EXTERNAL))
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Pop the scope stack if necessary */

    if (AcpiNsOpensScope (AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode)))
    {

        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "%s: Popping scope for Op %p\n",
            AcpiUtGetTypeName (OpInfo->ObjectType), Op));

        (void) AcpiDsScopeStackPop (WalkState);
    }

    return_ACPI_STATUS (AE_OK);
}