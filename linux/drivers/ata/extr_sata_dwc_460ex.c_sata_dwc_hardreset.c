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
struct sata_dwc_device {TYPE_1__* sata_dwc_regs; } ;
struct ata_link {int /*<<< orphan*/  ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbtsr; int /*<<< orphan*/  dmacr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHB_DMA_BRST_DFLT ; 
 struct sata_dwc_device* HSDEV_FROM_AP (int /*<<< orphan*/ ) ; 
 int SATA_DWC_DBTSR_MRD (int /*<<< orphan*/ ) ; 
 int SATA_DWC_DBTSR_MWR (int /*<<< orphan*/ ) ; 
 int SATA_DWC_DMACR_TXRXCH_CLEAR ; 
 int /*<<< orphan*/  sata_dwc_enable_interrupts (struct sata_dwc_device*) ; 
 int /*<<< orphan*/  sata_dwc_writel (int /*<<< orphan*/ *,int) ; 
 int sata_sff_hardreset (struct ata_link*,unsigned int*,unsigned long) ; 

__attribute__((used)) static int sata_dwc_hardreset(struct ata_link *link, unsigned int *class,
			      unsigned long deadline)
{
	struct sata_dwc_device *hsdev = HSDEV_FROM_AP(link->ap);
	int ret;

	ret = sata_sff_hardreset(link, class, deadline);

	sata_dwc_enable_interrupts(hsdev);

	/* Reconfigure the DMA control register */
	sata_dwc_writel(&hsdev->sata_dwc_regs->dmacr,
			SATA_DWC_DMACR_TXRXCH_CLEAR);

	/* Reconfigure the DMA Burst Transaction Size register */
	sata_dwc_writel(&hsdev->sata_dwc_regs->dbtsr,
			SATA_DWC_DBTSR_MWR(AHB_DMA_BRST_DFLT) |
			SATA_DWC_DBTSR_MRD(AHB_DMA_BRST_DFLT));

	return ret;
}