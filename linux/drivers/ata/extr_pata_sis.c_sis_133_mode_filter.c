#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {TYPE_2__* host; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct ata_port* ap; } ;

/* Variables and functions */
 int ATA_SHIFT_UDMA ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int sis_port_base (struct ata_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long sis_133_mode_filter(struct ata_device *adev, unsigned long mask)
{
	struct ata_port *ap = adev->link->ap;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int port = sis_port_base(adev);
	u32 t1;

	pci_read_config_dword(pdev, port, &t1);
	/* if ATA133 is disabled, mask it out */
	if (!(t1 & 0x08))
		mask &= ~(0xC0 << ATA_SHIFT_UDMA);
	return mask;
}