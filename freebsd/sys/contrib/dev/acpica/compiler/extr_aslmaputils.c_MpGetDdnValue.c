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
struct TYPE_8__ {scalar_t__ Type; TYPE_2__* Object; } ;
struct TYPE_6__ {char* Pointer; } ;
struct TYPE_7__ {TYPE_1__ String; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int /*<<< orphan*/  AcpiNsGetNode (TYPE_3__*,char*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 char* METHOD_NAME__DDN ; 

char *
MpGetDdnValue (
    char                    *DeviceName)
{
    ACPI_NAMESPACE_NODE     *DeviceNode;
    ACPI_NAMESPACE_NODE     *DdnNode;
    ACPI_STATUS             Status;


    Status = AcpiNsGetNode (NULL, DeviceName, ACPI_NS_NO_UPSEARCH,
        &DeviceNode);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    Status = AcpiNsGetNode (DeviceNode, METHOD_NAME__DDN, ACPI_NS_NO_UPSEARCH,
        &DdnNode);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    if ((DdnNode->Type != ACPI_TYPE_STRING) ||
        !DdnNode->Object)
    {
        goto ErrorExit;
    }

    return (DdnNode->Object->String.Pointer);


ErrorExit:
    return (NULL);
}