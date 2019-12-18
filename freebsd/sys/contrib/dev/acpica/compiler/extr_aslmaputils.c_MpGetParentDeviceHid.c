#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ AmlOpcode; int /*<<< orphan*/ * Node; TYPE_2__* Parent; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ AML_DEVICE_OP ; 
 scalar_t__ AML_SCOPE_OP ; 
 int /*<<< orphan*/  ASL_FILE_MAP_OUTPUT ; 
 char* AcpiNsGetExternalPathname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*) ; 
 char* MpGetHidValue (int /*<<< orphan*/ *) ; 

char *
MpGetParentDeviceHid (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_NAMESPACE_NODE     **TargetNode,
    char                    **ParentDeviceName)
{
    ACPI_NAMESPACE_NODE     *DeviceNode;


    /* Find parent Device() or Scope() Op */

    while (Op &&
        (Op->Asl.AmlOpcode != AML_DEVICE_OP) &&
        (Op->Asl.AmlOpcode != AML_SCOPE_OP))
    {
        Op = Op->Asl.Parent;
    }

    if (!Op)
    {
        FlPrintFile (ASL_FILE_MAP_OUTPUT, " No_Parent_Device ");
        goto ErrorExit;
    }

    /* Get the full pathname to the device and the _HID */

    DeviceNode = Op->Asl.Node;
    if (!DeviceNode)
    {
        FlPrintFile (ASL_FILE_MAP_OUTPUT, " No_Device_Node ");
        goto ErrorExit;
    }

    *ParentDeviceName = AcpiNsGetExternalPathname (DeviceNode);
    return (MpGetHidValue (DeviceNode));


ErrorExit:
    return ("-No HID-");
}