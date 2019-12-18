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
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {int Type; scalar_t__ TypeDataLength; } ;
struct TYPE_6__ {TYPE_1__ CommonSerialBus; } ;
typedef  int /*<<< orphan*/  AML_RESOURCE_UART_SERIALBUS ;
typedef  int /*<<< orphan*/  AML_RESOURCE_SPI_SERIALBUS ;
typedef  int /*<<< orphan*/  AML_RESOURCE_I2C_SERIALBUS ;
typedef  TYPE_2__ AML_RESOURCE ;

/* Variables and functions */
 int ACPI_ADD_PTR (int,TYPE_2__*,int) ; 
 scalar_t__ AML_RESOURCE_I2C_MIN_DATA_LEN ; 
#define  AML_RESOURCE_I2C_SERIALBUSTYPE 130 
 scalar_t__ AML_RESOURCE_SPI_MIN_DATA_LEN ; 
#define  AML_RESOURCE_SPI_SERIALBUSTYPE 129 
 scalar_t__ AML_RESOURCE_UART_MIN_DATA_LEN ; 
#define  AML_RESOURCE_UART_SERIALBUSTYPE 128 
 int /*<<< orphan*/  AcpiDmDumpRawDataBuffer (int,scalar_t__,scalar_t__) ; 
 int UINT8 ; 
 int VendorData ; 

__attribute__((used)) static void
AcpiDmDumpSerialBusVendorData (
    AML_RESOURCE            *Resource,
    UINT32                  Level)
{
    UINT8                   *VendorData;
    UINT32                  VendorLength;


    /* Get the (optional) vendor data and length */

    switch (Resource->CommonSerialBus.Type)
    {
    case AML_RESOURCE_I2C_SERIALBUSTYPE:

        VendorLength = Resource->CommonSerialBus.TypeDataLength -
            AML_RESOURCE_I2C_MIN_DATA_LEN;

        VendorData = ACPI_ADD_PTR (UINT8, Resource,
            sizeof (AML_RESOURCE_I2C_SERIALBUS));
        break;

    case AML_RESOURCE_SPI_SERIALBUSTYPE:

        VendorLength = Resource->CommonSerialBus.TypeDataLength -
            AML_RESOURCE_SPI_MIN_DATA_LEN;

        VendorData = ACPI_ADD_PTR (UINT8, Resource,
            sizeof (AML_RESOURCE_SPI_SERIALBUS));
        break;

    case AML_RESOURCE_UART_SERIALBUSTYPE:

        VendorLength = Resource->CommonSerialBus.TypeDataLength -
            AML_RESOURCE_UART_MIN_DATA_LEN;

        VendorData = ACPI_ADD_PTR (UINT8, Resource,
            sizeof (AML_RESOURCE_UART_SERIALBUS));
        break;

    default:

        return;
    }

    /* Dump the vendor bytes as a RawDataBuffer object */

    AcpiDmDumpRawDataBuffer (VendorData, VendorLength, Level);
}