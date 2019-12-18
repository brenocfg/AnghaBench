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
struct ata_device {int dma_mode; scalar_t__ devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 int XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,unsigned int,int) ; 
 int sc1200_clock () ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc1200_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	static const u32 udma_timing[3][3] = {
		{ 0x00921250, 0x00911140, 0x00911030 },
		{ 0x00932470, 0x00922260, 0x00922140 },
		{ 0x009436A1, 0x00933481, 0x00923261 }
	};

	static const u32 mwdma_timing[3][3] = {
		{ 0x00077771, 0x00012121, 0x00002020 },
		{ 0x000BBBB2, 0x00024241, 0x00013131 },
		{ 0x000FFFF3, 0x00035352, 0x00015151 }
	};

	int clock = sc1200_clock();
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned int reg = 0x40 + 0x10 * ap->port_no;
	int mode = adev->dma_mode;
	u32 format;

	if (mode >= XFER_UDMA_0)
		format = udma_timing[clock][mode - XFER_UDMA_0];
	else
		format = mwdma_timing[clock][mode - XFER_MW_DMA_0];

	if (adev->devno == 0) {
		u32 timings;

		pci_read_config_dword(pdev, reg + 4, &timings);
		timings &= 0x80000000UL;
		timings |= format;
		pci_write_config_dword(pdev, reg + 4, timings);
	} else
		pci_write_config_dword(pdev, reg + 12, format);
}