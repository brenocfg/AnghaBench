#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {int /*<<< orphan*/  Description; } ;
typedef  TYPE_1__ AH_DEVICE_ID ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_NAMESPACE_NODE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_FILE_MAP_OUTPUT ; 
 TYPE_1__* AcpiAhMatchHardwareId (char*) ; 
 char* AcpiNsGetExternalPathname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,...) ; 
 char* MpGetDdnValue (char*) ; 
 char* MpGetHidValue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
MpEmitOneDevice (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    char                    *DevicePathname;
    char                    *DdnString;
    char                    *HidString;
    const AH_DEVICE_ID      *HidInfo;


    /* Device pathname */

    DevicePathname = AcpiNsGetExternalPathname (
        ACPI_CAST_PTR (ACPI_NAMESPACE_NODE, ObjHandle));

    FlPrintFile (ASL_FILE_MAP_OUTPUT, "%-32s", DevicePathname);

    /* _HID or _DDN */

    HidString = MpGetHidValue (
        ACPI_CAST_PTR (ACPI_NAMESPACE_NODE, ObjHandle));
    FlPrintFile (ASL_FILE_MAP_OUTPUT, "%8s", HidString);

    HidInfo = AcpiAhMatchHardwareId (HidString);
    if (HidInfo)
    {
        FlPrintFile (ASL_FILE_MAP_OUTPUT, "    // %s",
            HidInfo->Description);
    }
    else if ((DdnString = MpGetDdnValue (DevicePathname)))
    {
        FlPrintFile (ASL_FILE_MAP_OUTPUT, "    // %s (_DDN)", DdnString);
    }

    FlPrintFile (ASL_FILE_MAP_OUTPUT, "\n");
    ACPI_FREE (DevicePathname);
    return (AE_OK);
}