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
struct s3c24xx_dma_phy {struct s3c24xx_dma_chan* serving; int /*<<< orphan*/  id; } ;
struct s3c24xx_dma_engine {TYPE_1__* pdev; } ;
struct s3c24xx_dma_chan {int /*<<< orphan*/  state; struct s3c24xx_dma_phy* phy; int /*<<< orphan*/  name; struct s3c24xx_dma_engine* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C24XX_DMA_CHAN_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c24xx_dma_start_next_txd (struct s3c24xx_dma_chan*) ; 

__attribute__((used)) static void s3c24xx_dma_phy_reassign_start(struct s3c24xx_dma_phy *phy,
	struct s3c24xx_dma_chan *s3cchan)
{
	struct s3c24xx_dma_engine *s3cdma = s3cchan->host;

	dev_dbg(&s3cdma->pdev->dev, "reassigned physical channel %d for xfer on %s\n",
		phy->id, s3cchan->name);

	/*
	 * We do this without taking the lock; we're really only concerned
	 * about whether this pointer is NULL or not, and we're guaranteed
	 * that this will only be called when it _already_ is non-NULL.
	 */
	phy->serving = s3cchan;
	s3cchan->phy = phy;
	s3cchan->state = S3C24XX_DMA_CHAN_RUNNING;
	s3c24xx_dma_start_next_txd(s3cchan);
}