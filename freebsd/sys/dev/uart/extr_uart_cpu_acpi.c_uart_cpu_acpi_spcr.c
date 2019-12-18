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
typedef  scalar_t__ vm_paddr_t ;
struct TYPE_7__ {scalar_t__ regshft; int regiowidth; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; scalar_t__ rclk; scalar_t__ chan; } ;
struct uart_devinfo {int databits; int stopbits; int baudrate; TYPE_2__ bas; int /*<<< orphan*/  ops; int /*<<< orphan*/  parity; } ;
struct uart_class {int dummy; } ;
struct acpi_uart_compat_data {int cd_quirks; scalar_t__ cd_regshft; struct uart_class* cd_class; } ;
struct TYPE_6__ {int SpaceId; scalar_t__ AccessWidth; int BitWidth; int /*<<< orphan*/  Address; } ;
struct TYPE_8__ {int BaudRate; TYPE_1__ SerialPort; int /*<<< orphan*/  InterfaceType; } ;
typedef  TYPE_3__ ACPI_TABLE_SPCR ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_SPCR ; 
 int ENXIO ; 
 int UART_DEV_CONSOLE ; 
 int UART_F_IGNORE_SPCR_REGSHFT ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 scalar_t__ acpi_find_table (int /*<<< orphan*/ ) ; 
 TYPE_3__* acpi_map_table (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_unmap_table (TYPE_3__*) ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  uart_bus_space_io ; 
 int /*<<< orphan*/  uart_bus_space_mem ; 
 struct acpi_uart_compat_data* uart_cpu_acpi_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_getops (struct uart_class*) ; 
 int /*<<< orphan*/  uart_getrange (struct uart_class*) ; 

int
uart_cpu_acpi_spcr(int devtype, struct uart_devinfo *di)
{
	vm_paddr_t spcr_physaddr;
	ACPI_TABLE_SPCR *spcr;
	struct acpi_uart_compat_data *cd;
	struct uart_class *class;
	int error = ENXIO;

	/* SPCR only tells us about consoles. */
	if (devtype != UART_DEV_CONSOLE)
		return (error);

	/* Look for the SPCR table. */
	spcr_physaddr = acpi_find_table(ACPI_SIG_SPCR);
	if (spcr_physaddr == 0)
		return (error);
	spcr = acpi_map_table(spcr_physaddr, ACPI_SIG_SPCR);
	if (spcr == NULL) {
		printf("Unable to map the SPCR table!\n");
		return (error);
	}

	/* Search for information about this SPCR interface type. */
	cd = uart_cpu_acpi_scan(spcr->InterfaceType);
	if (cd == NULL)
		goto out;
	class = cd->cd_class;

	/* Fill in some fixed details. */
	di->bas.chan = 0;
	di->bas.rclk = 0;
	di->databits = 8;
	di->stopbits = 1;
	di->parity = UART_PARITY_NONE;
	di->ops = uart_getops(class);

	/* Fill in details from SPCR table. */
	switch (spcr->SerialPort.SpaceId) {
	case 0:
		di->bas.bst = uart_bus_space_mem;
		break;
	case 1:
		di->bas.bst = uart_bus_space_io;
		break;
	default:
		printf("UART in unrecognized address space: %d!\n",
		    (int)spcr->SerialPort.SpaceId);
		goto out;
	}
	if (spcr->SerialPort.AccessWidth == 0)
		di->bas.regshft = 0;
	else
		di->bas.regshft = spcr->SerialPort.AccessWidth - 1;
	di->bas.regiowidth = spcr->SerialPort.BitWidth / 8;
	switch (spcr->BaudRate) {
	case 0:
		/* Special value; means "keep current value unchanged". */
		di->baudrate = 0;
		break;
	case 3:
		di->baudrate = 9600;
		break;
	case 4:
		di->baudrate = 19200;
		break;
	case 6:
		di->baudrate = 57600;
		break;
	case 7:
		di->baudrate = 115200;
		break;
	default:
		printf("SPCR has reserved BaudRate value: %d!\n",
		    (int)spcr->BaudRate);
		goto out;
	}

	/* Apply device tweaks. */
	if ((cd->cd_quirks & UART_F_IGNORE_SPCR_REGSHFT) ==
	    UART_F_IGNORE_SPCR_REGSHFT) {
		di->bas.regshft = cd->cd_regshft;
	}

	/* Create a bus space handle. */
	error = bus_space_map(di->bas.bst, spcr->SerialPort.Address,
	    uart_getrange(class), 0, &di->bas.bsh);

out:
	acpi_unmap_table(spcr);
	return (error);
}