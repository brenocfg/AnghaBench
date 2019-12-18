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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct it821x_dev {int** want; int* mwdma; int* udma; scalar_t__ timing10; } ;
struct ata_port {int port_no; struct it821x_dev* private_data; TYPE_1__* host; } ;
struct ata_device {int devno; scalar_t__ dma_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ATA_50 130 
#define  ATA_66 129 
#define  ATA_ANY 128 
 int MWDMA_OFF ; 
 int UDMA_OFF ; 
 int XFER_MW_DMA_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  it821x_clock_strategy (struct ata_port*,struct ata_device*) ; 
 int /*<<< orphan*/  it821x_program_udma (struct ata_port*,struct ata_device*,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it821x_passthru_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	static const u16 dma[]	= 	{ 0x8866, 0x3222, 0x3121 };
	static const u8 mwdma_want[] =  { ATA_ANY, ATA_66, ATA_ANY };
	static const u16 udma[]	= 	{ 0x4433, 0x4231, 0x3121, 0x2121, 0x1111, 0x2211, 0x1111 };
	static const u8 udma_want[] =   { ATA_ANY, ATA_50, ATA_ANY, ATA_66, ATA_66, ATA_50, ATA_66 };

	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	struct it821x_dev *itdev = ap->private_data;
	int channel = ap->port_no;
	int unit = adev->devno;
	u8 conf;

	if (adev->dma_mode >= XFER_UDMA_0) {
		int mode_wanted = adev->dma_mode - XFER_UDMA_0;

		itdev->want[unit][1] = udma_want[mode_wanted];
		itdev->want[unit][0] = 3;	/* UDMA is high priority */
		itdev->mwdma[unit] = MWDMA_OFF;
		itdev->udma[unit] = udma[mode_wanted];
		if (mode_wanted >= 5)
			itdev->udma[unit] |= 0x8080;	/* UDMA 5/6 select on */

		/* UDMA on. Again revision 0x10 must do the pair */
		pci_read_config_byte(pdev, 0x50, &conf);
		if (itdev->timing10)
			conf &= channel ? 0x9F: 0xE7;
		else
			conf &= ~ (1 << (3 + 2 * channel + unit));
		pci_write_config_byte(pdev, 0x50, conf);
		it821x_clock_strategy(ap, adev);
		it821x_program_udma(ap, adev, itdev->udma[unit]);
	} else {
		int mode_wanted = adev->dma_mode - XFER_MW_DMA_0;

		itdev->want[unit][1] = mwdma_want[mode_wanted];
		itdev->want[unit][0] = 2;	/* MWDMA is low priority */
		itdev->mwdma[unit] = dma[mode_wanted];
		itdev->udma[unit] = UDMA_OFF;

		/* UDMA bits off - Revision 0x10 do them in pairs */
		pci_read_config_byte(pdev, 0x50, &conf);
		if (itdev->timing10)
			conf |= channel ? 0x60: 0x18;
		else
			conf |= 1 << (3 + 2 * channel + unit);
		pci_write_config_byte(pdev, 0x50, conf);
		it821x_clock_strategy(ap, adev);
	}
}