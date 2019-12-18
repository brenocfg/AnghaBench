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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_IO_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  iodev_write_1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iodev_write_2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iodev_write_4 (int /*<<< orphan*/ ,int) ; 

ACPI_STATUS
AcpiOsWritePort(ACPI_IO_ADDRESS OutPort, UINT32	Value, UINT32 Width)
{

    switch (Width) {
    case 8:
	iodev_write_1(OutPort, Value);
	break;
    case 16:
	iodev_write_2(OutPort, Value);
	break;
    case 32:
	iodev_write_4(OutPort, Value);
	break;
    }

    return (AE_OK);
}