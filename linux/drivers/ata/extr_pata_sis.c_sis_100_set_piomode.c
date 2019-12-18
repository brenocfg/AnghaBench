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
struct ata_port {TYPE_1__* host; } ;
struct ata_device {int pio_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int const) ; 
 int sis_old_port_base (struct ata_device*) ; 
 int /*<<< orphan*/  sis_set_fifo (struct ata_port*,struct ata_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_100_set_piomode (struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int port = sis_old_port_base(adev);
	int speed = adev->pio_mode - XFER_PIO_0;

	static const u8 actrec[] = { 0x00, 0x67, 0x44, 0x33, 0x31 };

	sis_set_fifo(ap, adev);

	pci_write_config_byte(pdev, port, actrec[speed]);
}