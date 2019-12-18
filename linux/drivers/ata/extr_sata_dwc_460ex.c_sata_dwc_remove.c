#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sata_dwc_device {int /*<<< orphan*/  phy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct ata_host {struct sata_dwc_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct ata_host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_dwc_dma_exit_old (struct sata_dwc_device*) ; 

__attribute__((used)) static int sata_dwc_remove(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct ata_host *host = dev_get_drvdata(dev);
	struct sata_dwc_device *hsdev = host->private_data;

	ata_host_detach(host);

	phy_exit(hsdev->phy);

#ifdef CONFIG_SATA_DWC_OLD_DMA
	/* Free SATA DMA resources */
	sata_dwc_dma_exit_old(hsdev);
#endif

	dev_dbg(&ofdev->dev, "done\n");
	return 0;
}