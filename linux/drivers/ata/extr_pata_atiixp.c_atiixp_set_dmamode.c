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
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int dma_mode; int devno; int pio_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIIXP_IDE_MWDMA_TIMING ; 
 int /*<<< orphan*/  ATIIXP_IDE_UDMA_MODE ; 
 int /*<<< orphan*/  BUG () ; 
 int XFER_MW_DMA_0 ; 
 int XFER_MW_DMA_1 ; 
 int XFER_MW_DMA_2 ; 
 int XFER_UDMA_0 ; 
 int /*<<< orphan*/  atiixp_lock ; 
 int /*<<< orphan*/  atiixp_set_pio_timing (struct ata_port*,struct ata_device*,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atiixp_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	static u8 mwdma_timings[5] = { 0x77, 0x21, 0x20 };

	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int dma = adev->dma_mode;
	int dn = 2 * ap->port_no + adev->devno;
	int wanted_pio;
	unsigned long flags;

	spin_lock_irqsave(&atiixp_lock, flags);

	if (adev->dma_mode >= XFER_UDMA_0) {
		u16 udma_mode_data;

		dma -= XFER_UDMA_0;

		pci_read_config_word(pdev, ATIIXP_IDE_UDMA_MODE, &udma_mode_data);
		udma_mode_data &= ~(0x7 << (4 * dn));
		udma_mode_data |= dma << (4 * dn);
		pci_write_config_word(pdev, ATIIXP_IDE_UDMA_MODE, udma_mode_data);
	} else {
		int timing_shift = (16 * ap->port_no) + 8 * (adev->devno ^ 1);
		u32 mwdma_timing_data;

		dma -= XFER_MW_DMA_0;

		pci_read_config_dword(pdev, ATIIXP_IDE_MWDMA_TIMING,
				      &mwdma_timing_data);
		mwdma_timing_data &= ~(0xFF << timing_shift);
		mwdma_timing_data |= (mwdma_timings[dma] << timing_shift);
		pci_write_config_dword(pdev, ATIIXP_IDE_MWDMA_TIMING,
				       mwdma_timing_data);
	}
	/*
	 *	We must now look at the PIO mode situation. We may need to
	 *	adjust the PIO mode to keep the timings acceptable
	 */
	if (adev->dma_mode >= XFER_MW_DMA_2)
		wanted_pio = 4;
	else if (adev->dma_mode == XFER_MW_DMA_1)
		wanted_pio = 3;
	else if (adev->dma_mode == XFER_MW_DMA_0)
		wanted_pio = 0;
	else BUG();

	if (adev->pio_mode != wanted_pio)
		atiixp_set_pio_timing(ap, adev, wanted_pio);
	spin_unlock_irqrestore(&atiixp_lock, flags);
}