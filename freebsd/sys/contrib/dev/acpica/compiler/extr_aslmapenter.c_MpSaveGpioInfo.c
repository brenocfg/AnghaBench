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
typedef  void* UINT8 ;
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_8__ {char* DeviceName; size_t PinCount; size_t PinIndex; void* Polarity; void* Direction; int /*<<< orphan*/  Type; int /*<<< orphan*/  PinNumber; int /*<<< orphan*/ * Op; } ;
struct TYPE_6__ {int IntFlags; int /*<<< orphan*/  ConnectionType; } ;
struct TYPE_7__ {TYPE_1__ Gpio; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_GPIO_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AslGbl_MapfileFlag ; 
 TYPE_3__* MpCreateGpioInfo (int /*<<< orphan*/ ,char*) ; 

void
MpSaveGpioInfo (
    ACPI_PARSE_OBJECT       *Op,
    AML_RESOURCE            *Resource,
    UINT32                  PinCount,
    UINT16                  *PinList,
    char                    *DeviceName)
{
    ACPI_GPIO_INFO          *Info;
    UINT32                  i;


    /* Mapfile option enabled? */

    if (!AslGbl_MapfileFlag)
    {
        return;
    }

    /* Create an info block for each pin defined in the descriptor */

    for (i = 0; i < PinCount; i++)
    {
        Info = MpCreateGpioInfo (PinList[i], DeviceName);

        Info->Op = Op;
        Info->DeviceName = DeviceName;
        Info->PinCount = PinCount;
        Info->PinIndex = i;
        Info->PinNumber = PinList[i];
        Info->Type = Resource->Gpio.ConnectionType;
        Info->Direction = (UINT8) (Resource->Gpio.IntFlags & 0x0003);       /* _IOR, for IO descriptor */
        Info->Polarity = (UINT8) ((Resource->Gpio.IntFlags >> 1) & 0x0003); /* _POL, for INT descriptor */
    }
}