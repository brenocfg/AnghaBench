#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  AcpiNsGetNode (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* MpGetHidValue (int /*<<< orphan*/ *) ; 

char *
MpGetHidViaNamestring (
    char                    *DeviceName)
{
    ACPI_NAMESPACE_NODE     *DeviceNode;
    ACPI_STATUS             Status;


    Status = AcpiNsGetNode (NULL, DeviceName, ACPI_NS_NO_UPSEARCH,
        &DeviceNode);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    return (MpGetHidValue (DeviceNode));


ErrorExit:
    return ("-No HID-");
}