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
struct s3c24xx_dma_engine {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_free; } ;
struct s3c24xx_dma_chan {int id; int slave; TYPE_1__ vc; void* name; int /*<<< orphan*/  state; struct s3c24xx_dma_engine* host; } ;
struct dma_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S3C24XX_DMA_CHAN_IDLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,char*) ; 
 struct s3c24xx_dma_chan* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s3c24xx_dma_desc_free ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,struct dma_device*) ; 

__attribute__((used)) static int s3c24xx_dma_init_virtual_channels(struct s3c24xx_dma_engine *s3cdma,
		struct dma_device *dmadev, unsigned int channels, bool slave)
{
	struct s3c24xx_dma_chan *chan;
	int i;

	INIT_LIST_HEAD(&dmadev->channels);

	/*
	 * Register as many many memcpy as we have physical channels,
	 * we won't always be able to use all but the code will have
	 * to cope with that situation.
	 */
	for (i = 0; i < channels; i++) {
		chan = devm_kzalloc(dmadev->dev, sizeof(*chan), GFP_KERNEL);
		if (!chan)
			return -ENOMEM;

		chan->id = i;
		chan->host = s3cdma;
		chan->state = S3C24XX_DMA_CHAN_IDLE;

		if (slave) {
			chan->slave = true;
			chan->name = kasprintf(GFP_KERNEL, "slave%d", i);
			if (!chan->name)
				return -ENOMEM;
		} else {
			chan->name = kasprintf(GFP_KERNEL, "memcpy%d", i);
			if (!chan->name)
				return -ENOMEM;
		}
		dev_dbg(dmadev->dev,
			 "initialize virtual channel \"%s\"\n",
			 chan->name);

		chan->vc.desc_free = s3c24xx_dma_desc_free;
		vchan_init(&chan->vc, dmadev);
	}
	dev_info(dmadev->dev, "initialized %d virtual %s channels\n",
		 i, slave ? "slave" : "memcpy");
	return i;
}