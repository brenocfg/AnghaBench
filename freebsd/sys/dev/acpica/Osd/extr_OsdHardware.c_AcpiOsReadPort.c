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
 int iodev_read_1 (int /*<<< orphan*/ ) ; 
 int iodev_read_2 (int /*<<< orphan*/ ) ; 
 int iodev_read_4 (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiOsReadPort(ACPI_IO_ADDRESS InPort, UINT32 *Value, UINT32 Width)
{

    switch (Width) {
    case 8:
	*Value = iodev_read_1(InPort);
	break;
    case 16:
	*Value = iodev_read_2(InPort);
	break;
    case 32:
	*Value = iodev_read_4(InPort);
	break;
    }

    return (AE_OK);
}