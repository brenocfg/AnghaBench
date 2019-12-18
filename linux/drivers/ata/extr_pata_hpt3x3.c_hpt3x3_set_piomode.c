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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; int pio_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpt3x3_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 r1, r2;
	int dn = 2 * ap->port_no + adev->devno;

	pci_read_config_dword(pdev, 0x44, &r1);
	pci_read_config_dword(pdev, 0x48, &r2);
	/* Load the PIO timing number */
	r1 &= ~(7 << (3 * dn));
	r1 |= (adev->pio_mode - XFER_PIO_0) << (3 * dn);
	r2 &= ~(0x11 << dn);	/* Clear MWDMA and UDMA bits */

	pci_write_config_dword(pdev, 0x44, r1);
	pci_write_config_dword(pdev, 0x48, r2);
}