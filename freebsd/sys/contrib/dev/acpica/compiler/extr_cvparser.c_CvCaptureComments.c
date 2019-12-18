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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {int /*<<< orphan*/ * Aml; } ;
struct TYPE_7__ {int Flags; } ;
struct TYPE_6__ {scalar_t__ PassNumber; TYPE_3__ ParserState; int /*<<< orphan*/ * Aml; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  TYPE_2__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_GET8 (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_IMODE_LOAD_PASS1 ; 
 int AML_DEFER ; 
 int /*<<< orphan*/  AcpiGbl_CaptureComments ; 
 TYPE_2__* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int /*<<< orphan*/  CvCaptureCommentsOnly (TYPE_3__*) ; 

void
CvCaptureComments (
    ACPI_WALK_STATE         *WalkState)
{
    UINT8                   *Aml;
    UINT16                  Opcode;
    const ACPI_OPCODE_INFO  *OpInfo;


    if (!AcpiGbl_CaptureComments)
    {
        return;
    }

    /*
     * Before parsing, check to see that comments that come directly
     * after deferred opcodes aren't being processed.
     */
    Aml = WalkState->ParserState.Aml;
    Opcode = (UINT16) ACPI_GET8 (Aml);
    OpInfo = AcpiPsGetOpcodeInfo (Opcode);

    if (!(OpInfo->Flags & AML_DEFER) ||
        ((OpInfo->Flags & AML_DEFER) &&
        (WalkState->PassNumber != ACPI_IMODE_LOAD_PASS1)))
    {
        CvCaptureCommentsOnly (&WalkState->ParserState);
        WalkState->Aml = WalkState->ParserState.Aml;
    }

}