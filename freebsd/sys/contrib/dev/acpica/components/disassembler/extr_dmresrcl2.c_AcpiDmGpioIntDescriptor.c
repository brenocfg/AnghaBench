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
struct TYPE_5__ {int PinConfig; size_t DebounceTimeout; int /*<<< orphan*/  IntFlags; } ;
struct TYPE_6__ {TYPE_1__ Gpio; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
 size_t ACPI_EXTRACT_2BIT_FLAG (int /*<<< orphan*/ ,int) ; 
 size_t ACPI_GET_1BIT_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmGpioCommon (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AcpiGbl_HeDecode ; 
 int /*<<< orphan*/ * AcpiGbl_LlDecode ; 
 size_t* AcpiGbl_PpcDecode ; 
 int /*<<< orphan*/ * AcpiGbl_ShrDecode ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,size_t,...) ; 

__attribute__((used)) static void
AcpiDmGpioIntDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{

    /* Dump the GpioInt-specific portion of the descriptor */

    /* EdgeLevel, ActiveLevel, Shared */

    AcpiDmIndent (Level);
    AcpiOsPrintf ("GpioInt (%s, %s, %s, ",
        AcpiGbl_HeDecode [ACPI_GET_1BIT_FLAG (Resource->Gpio.IntFlags)],
        AcpiGbl_LlDecode [ACPI_EXTRACT_2BIT_FLAG (Resource->Gpio.IntFlags, 1)],
        AcpiGbl_ShrDecode [ACPI_EXTRACT_2BIT_FLAG (Resource->Gpio.IntFlags, 3)]);

    /* PinConfig, DebounceTimeout */

    if (Resource->Gpio.PinConfig <= 3)
    {
        AcpiOsPrintf ("%s, ",
            AcpiGbl_PpcDecode[Resource->Gpio.PinConfig]);
    }
    else
    {
        AcpiOsPrintf ("0x%2.2X, ", Resource->Gpio.PinConfig);
    }
    AcpiOsPrintf ("0x%4.4X,\n", Resource->Gpio.DebounceTimeout);

    /* Dump the GpioInt/GpioIo common portion of the descriptor */

    AcpiDmGpioCommon (Info, Resource, Level);
}