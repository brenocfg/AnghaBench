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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_6__ {int ConnectionType; } ;
struct TYPE_7__ {TYPE_1__ Gpio; } ;
typedef  TYPE_2__ AML_RESOURCE ;
typedef  int /*<<< orphan*/  ACPI_OP_WALK_INFO ;

/* Variables and functions */
#define  AML_RESOURCE_GPIO_TYPE_INT 129 
#define  AML_RESOURCE_GPIO_TYPE_IO 128 
 int /*<<< orphan*/  AcpiDmGpioIntDescriptor (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmGpioIoDescriptor (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 

void
AcpiDmGpioDescriptor (
    ACPI_OP_WALK_INFO       *Info,
    AML_RESOURCE            *Resource,
    UINT32                  Length,
    UINT32                  Level)
{
    UINT8                   ConnectionType;


    ConnectionType = Resource->Gpio.ConnectionType;

    switch (ConnectionType)
    {
    case AML_RESOURCE_GPIO_TYPE_INT:

        AcpiDmGpioIntDescriptor (Info, Resource, Length, Level);
        break;

    case AML_RESOURCE_GPIO_TYPE_IO:

        AcpiDmGpioIoDescriptor (Info, Resource, Length, Level);
        break;

    default:

        AcpiOsPrintf ("Unknown GPIO type\n");
        break;
    }
}