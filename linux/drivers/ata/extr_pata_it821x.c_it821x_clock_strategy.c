#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct it821x_dev {int** want; int clock_mode; scalar_t__* udma; int /*<<< orphan*/ * pio; } ;
struct ata_port {int port_no; struct it821x_dev* private_data; TYPE_1__* host; } ;
struct ata_device {int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATA_50 ; 
 int ATA_66 ; 
 int ATA_ANY ; 
 scalar_t__ UDMA_OFF ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 int /*<<< orphan*/  it821x_program (struct ata_port*,struct ata_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it821x_program_udma (struct ata_port*,struct ata_device*,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it821x_clock_strategy(struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct it821x_dev *itdev = ap->private_data;
	u8 unit = adev->devno;
	struct ata_device *pair = ata_dev_pair(adev);

	int clock, altclock;
	u8 v;
	int sel = 0;

	/* Look for the most wanted clocking */
	if (itdev->want[0][0] > itdev->want[1][0]) {
		clock = itdev->want[0][1];
		altclock = itdev->want[1][1];
	} else {
		clock = itdev->want[1][1];
		altclock = itdev->want[0][1];
	}

	/* Master doesn't care does the slave ? */
	if (clock == ATA_ANY)
		clock = altclock;

	/* Nobody cares - keep the same clock */
	if (clock == ATA_ANY)
		return;
	/* No change */
	if (clock == itdev->clock_mode)
		return;

	/* Load this into the controller */
	if (clock == ATA_66)
		itdev->clock_mode = ATA_66;
	else {
		itdev->clock_mode = ATA_50;
		sel = 1;
	}
	pci_read_config_byte(pdev, 0x50, &v);
	v &= ~(1 << (1 + ap->port_no));
	v |= sel << (1 + ap->port_no);
	pci_write_config_byte(pdev, 0x50, v);

	/*
	 *	Reprogram the UDMA/PIO of the pair drive for the switch
	 *	MWDMA will be dealt with by the dma switcher
	 */
	if (pair && itdev->udma[1-unit] != UDMA_OFF) {
		it821x_program_udma(ap, pair, itdev->udma[1-unit]);
		it821x_program(ap, pair, itdev->pio[1-unit]);
	}
	/*
	 *	Reprogram the UDMA/PIO of our drive for the switch.
	 *	MWDMA will be dealt with by the dma switcher
	 */
	if (itdev->udma[unit] != UDMA_OFF) {
		it821x_program_udma(ap, adev, itdev->udma[unit]);
		it821x_program(ap, adev, itdev->pio[unit]);
	}
}