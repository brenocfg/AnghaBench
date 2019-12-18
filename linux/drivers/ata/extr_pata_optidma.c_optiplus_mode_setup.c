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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; int /*<<< orphan*/  dma_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  optidma_mode_setup (struct ata_port*,struct ata_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,scalar_t__) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void optiplus_mode_setup(struct ata_port *ap, struct ata_device *adev, u8 mode)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 udcfg;
	u8 udslave;
	int dev2 = 2 * adev->devno;
	int unit = 2 * ap->port_no + adev->devno;
	int udma = mode - XFER_UDMA_0;

	pci_read_config_byte(pdev, 0x44, &udcfg);
	if (mode <= XFER_UDMA_0) {
		udcfg &= ~(1 << unit);
		optidma_mode_setup(ap, adev, adev->dma_mode);
	} else {
		udcfg |=  (1 << unit);
		if (ap->port_no) {
			pci_read_config_byte(pdev, 0x45, &udslave);
			udslave &= ~(0x03 << dev2);
			udslave |= (udma << dev2);
			pci_write_config_byte(pdev, 0x45, udslave);
		} else {
			udcfg &= ~(0x30 << dev2);
			udcfg |= (udma << dev2);
		}
	}
	pci_write_config_byte(pdev, 0x44, udcfg);
}