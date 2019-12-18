#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* DeviceName; int Type; size_t Polarity; size_t Direction; struct TYPE_7__* Next; int /*<<< orphan*/  TargetNode; int /*<<< orphan*/  Op; int /*<<< orphan*/  PinIndex; int /*<<< orphan*/  PinNumber; } ;
struct TYPE_6__ {int /*<<< orphan*/  Description; } ;
typedef  TYPE_1__ AH_DEVICE_ID ;
typedef  TYPE_2__ ACPI_GPIO_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
#define  AML_RESOURCE_GPIO_TYPE_INT 129 
#define  AML_RESOURCE_GPIO_TYPE_IO 128 
 int /*<<< orphan*/  ASL_FILE_MAP_OUTPUT ; 
 TYPE_1__* AcpiAhMatchHardwareId (char*) ; 
 TYPE_2__* AslGbl_GpioList ; 
 char** DirectionDecode ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,...) ; 
 char* MpGetConnectionInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 char* MpGetDdnValue (char*) ; 
 char* MpGetHidViaNamestring (char*) ; 
 char* MpGetParentDeviceHid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  MpXrefDevices (TYPE_2__*) ; 
 char** PolarityDecode ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
MpEmitGpioInfo (
    void)
{
    ACPI_GPIO_INFO          *Info;
    char                    *Type;
    char                    *PrevDeviceName = NULL;
    const char              *Direction;
    const char              *Polarity;
    char                    *ParentPathname;
    const char              *Description;
    char                    *HidString;
    const AH_DEVICE_ID      *HidInfo;


    /* Walk the GPIO descriptor list */

    Info = AslGbl_GpioList;
    while (Info)
    {
        HidString = MpGetHidViaNamestring (Info->DeviceName);

        /* Print header info for the controller itself */

        if (!PrevDeviceName ||
            strcmp (PrevDeviceName, Info->DeviceName))
        {
            FlPrintFile (ASL_FILE_MAP_OUTPUT,
                "\n\nGPIO Controller:  %-8s  %-28s",
                HidString, Info->DeviceName);

            HidInfo = AcpiAhMatchHardwareId (HidString);
            if (HidInfo)
            {
                FlPrintFile (ASL_FILE_MAP_OUTPUT, "  // %s",
                    HidInfo->Description);
            }

            FlPrintFile (ASL_FILE_MAP_OUTPUT,
                "\n\nPin   Type     Direction    Polarity"
                "    Dest _HID  Destination\n");
        }

        PrevDeviceName = Info->DeviceName;

        /* Setup various strings based upon the type (GpioInt or GpioIo) */

        switch (Info->Type)
        {
        case AML_RESOURCE_GPIO_TYPE_INT:

            Type = "GpioInt";
            Direction = "-Interrupt-";
            Polarity = PolarityDecode[Info->Polarity];
            break;

        case AML_RESOURCE_GPIO_TYPE_IO:

            Type = "GpioIo ";
            Direction = DirectionDecode[Info->Direction];
            Polarity = "          ";
            break;

        default:
            continue;
        }

        /* Emit the GPIO info */

        FlPrintFile (ASL_FILE_MAP_OUTPUT, "%4.4X  %s  %s  %s  ",
            Info->PinNumber, Type, Direction, Polarity);

        ParentPathname = NULL;
        HidString = MpGetConnectionInfo (Info->Op, Info->PinIndex,
            &Info->TargetNode, &ParentPathname);
        if (HidString)
        {
            /*
             * This is a Connection() field
             * Attempt to find all references to the field.
             */
            FlPrintFile (ASL_FILE_MAP_OUTPUT, "%8s   %-28s",
                HidString, ParentPathname);

            MpXrefDevices (Info);
        }
        else
        {
            /*
             * For Devices, attempt to get the _HID description string.
             * Failing that (many _HIDs are not recognized), attempt to
             * get the _DDN description string.
             */
            HidString = MpGetParentDeviceHid (Info->Op, &Info->TargetNode,
                &ParentPathname);

            FlPrintFile (ASL_FILE_MAP_OUTPUT, "%8s   %-28s",
                HidString, ParentPathname);

            /* Get the _HID description or _DDN string */

            HidInfo = AcpiAhMatchHardwareId (HidString);
            if (HidInfo)
            {
                FlPrintFile (ASL_FILE_MAP_OUTPUT, "  // %s",
                    HidInfo->Description);
            }
            else if ((Description = MpGetDdnValue (ParentPathname)))
            {
                FlPrintFile (ASL_FILE_MAP_OUTPUT, "  // %s (_DDN)",
                    Description);
            }
        }

        FlPrintFile (ASL_FILE_MAP_OUTPUT, "\n");
        ACPI_FREE (ParentPathname);
        Info = Info->Next;
    }
}