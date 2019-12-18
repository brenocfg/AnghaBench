#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ Lo; scalar_t__ Hi; } ;
struct TYPE_4__ {int /*<<< orphan*/  Full; TYPE_1__ Part; } ;
typedef  TYPE_2__ UINT64_OVERLAY ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SHIFT_LEFT_64_BY_32 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  UtShortShiftLeft ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtShortShiftLeft (
    UINT64                  Operand,
    UINT32                  Count,
    UINT64                  *OutResult)
{
    UINT64_OVERLAY          OperandOvl;


    ACPI_FUNCTION_TRACE (UtShortShiftLeft);


    OperandOvl.Full = Operand;

    if ((Count & 63) >= 32)
    {
        OperandOvl.Part.Hi = OperandOvl.Part.Lo;
        OperandOvl.Part.Lo = 0;
        Count = (Count & 63) - 32;
    }
    ACPI_SHIFT_LEFT_64_BY_32 (OperandOvl.Part.Hi,
        OperandOvl.Part.Lo, Count);

    /* Return only what was requested */

    if (OutResult)
    {
        *OutResult = OperandOvl.Full;
    }

    return_ACPI_STATUS (AE_OK);
}