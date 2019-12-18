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
struct s3c24xx_dma_phy {int /*<<< orphan*/  irq; } ;
struct s3c24xx_dma_engine {struct s3c24xx_dma_phy* phy_chans; TYPE_1__* pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int num_phy_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct s3c24xx_dma_phy*) ; 

__attribute__((used)) static void s3c24xx_dma_free_irq(struct platform_device *pdev,
				struct s3c24xx_dma_engine *s3cdma)
{
	int i;

	for (i = 0; i < s3cdma->pdata->num_phy_channels; i++) {
		struct s3c24xx_dma_phy *phy = &s3cdma->phy_chans[i];

		devm_free_irq(&pdev->dev, phy->irq, phy);
	}
}