#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_14__ {char* DeviceName; int /*<<< orphan*/  Speed; int /*<<< orphan*/  Address; TYPE_5__* Resource; int /*<<< orphan*/ * Op; } ;
struct TYPE_12__ {int /*<<< orphan*/  DefaultBaudRate; } ;
struct TYPE_11__ {int /*<<< orphan*/  ConnectionSpeed; int /*<<< orphan*/  DeviceSelection; } ;
struct TYPE_10__ {int /*<<< orphan*/  ConnectionSpeed; int /*<<< orphan*/  SlaveAddress; } ;
struct TYPE_9__ {int Type; } ;
struct TYPE_13__ {scalar_t__ DescriptorType; TYPE_4__ UartSerialBus; TYPE_3__ SpiSerialBus; TYPE_2__ I2cSerialBus; TYPE_1__ CommonSerialBus; } ;
typedef  TYPE_5__ AML_RESOURCE ;
typedef  TYPE_6__ ACPI_SERIAL_INFO ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_NAME_SERIAL_BUS ; 
#define  AML_RESOURCE_I2C_SERIALBUSTYPE 130 
#define  AML_RESOURCE_SPI_SERIALBUSTYPE 129 
#define  AML_RESOURCE_UART_SERIALBUSTYPE 128 
 int /*<<< orphan*/  AslGbl_MapfileFlag ; 
 TYPE_6__* MpCreateSerialInfo (char*,int /*<<< orphan*/ ) ; 

void
MpSaveSerialInfo (
    ACPI_PARSE_OBJECT       *Op,
    AML_RESOURCE            *Resource,
    char                    *DeviceName)
{
    ACPI_SERIAL_INFO        *Info;
    UINT16                  Address;
    UINT32                  Speed;


    /* Mapfile option enabled? */

    if (!AslGbl_MapfileFlag)
    {
        return;
    }

    if (Resource->DescriptorType != ACPI_RESOURCE_NAME_SERIAL_BUS)
    {
        return;
    }

    /* Extract address and speed from the resource descriptor */

    switch (Resource->CommonSerialBus.Type)
    {
    case AML_RESOURCE_I2C_SERIALBUSTYPE:

        Address = Resource->I2cSerialBus.SlaveAddress;
        Speed = Resource->I2cSerialBus.ConnectionSpeed;
        break;

    case AML_RESOURCE_SPI_SERIALBUSTYPE:

        Address = Resource->SpiSerialBus.DeviceSelection;
        Speed = Resource->SpiSerialBus.ConnectionSpeed;
        break;

    case AML_RESOURCE_UART_SERIALBUSTYPE:

        Address = 0;
        Speed = Resource->UartSerialBus.DefaultBaudRate;
        break;

    default:    /* Invalid bus subtype */
        return;
    }

    Info = MpCreateSerialInfo (DeviceName, Address);

    Info->Op = Op;
    Info->DeviceName = DeviceName;
    Info->Resource = Resource;
    Info->Address = Address;
    Info->Speed = Speed;
}