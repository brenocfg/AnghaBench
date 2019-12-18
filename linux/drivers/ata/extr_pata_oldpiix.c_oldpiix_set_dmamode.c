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
struct ata_port {struct ata_device* private_data; scalar_t__ port_no; TYPE_1__* host; } ;
struct ata_device {unsigned int dma_mode; scalar_t__ class; unsigned int const pio_mode; scalar_t__ devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 unsigned int XFER_MW_DMA_0 ; 
 unsigned int const XFER_PIO_0 ; 
 unsigned int const XFER_PIO_3 ; 
 unsigned int const XFER_PIO_4 ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void oldpiix_set_dmamode (struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	u8 idetm_port		= ap->port_no ? 0x42 : 0x40;
	u16 idetm_data;

	static const	 /* ISP  RTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	/*
	 * MWDMA is driven by the PIO timings. We must also enable
	 * IORDY unconditionally along with TIME1. PPE has already
	 * been set when the PIO timing was set.
	 */

	unsigned int mwdma	= adev->dma_mode - XFER_MW_DMA_0;
	unsigned int control;
	const unsigned int needed_pio[3] = {
		XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
	};
	int pio = needed_pio[mwdma] - XFER_PIO_0;

	pci_read_config_word(dev, idetm_port, &idetm_data);

	control = 3;	/* IORDY|TIME0 */
	/* Intel specifies that the PPE functionality is for disk only */
	if (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE enable */

	/* If the drive MWDMA is faster than it can do PIO then
	   we must force PIO into PIO0 */

	if (adev->pio_mode < needed_pio[mwdma])
		/* Enable DMA timing only */
		control |= 8;	/* PIO cycles in PIO0 */

	/* Mask out the relevant control and timing bits we will load. Also
	   clear the other drive TIME register as a precaution */
	if (adev->devno == 0) {
		idetm_data &= 0xCCE0;
		idetm_data |= control;
	} else {
		idetm_data &= 0xCC0E;
		idetm_data |= (control << 4);
	}
	idetm_data |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	pci_write_config_word(dev, idetm_port, idetm_data);

	/* Track which port is configured */
	ap->private_data = adev;
}