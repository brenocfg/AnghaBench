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
struct img_hash_dev {int /*<<< orphan*/  dma_lch; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_addr; } ;
struct dma_slave_config {int device_fc; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IMG_HASH_DMA_BURST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel (int /*<<< orphan*/ ,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 

__attribute__((used)) static int img_hash_dma_init(struct img_hash_dev *hdev)
{
	struct dma_slave_config dma_conf;
	int err = -EINVAL;

	hdev->dma_lch = dma_request_slave_channel(hdev->dev, "tx");
	if (!hdev->dma_lch) {
		dev_err(hdev->dev, "Couldn't acquire a slave DMA channel.\n");
		return -EBUSY;
	}
	dma_conf.direction = DMA_MEM_TO_DEV;
	dma_conf.dst_addr = hdev->bus_addr;
	dma_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	dma_conf.dst_maxburst = IMG_HASH_DMA_BURST;
	dma_conf.device_fc = false;

	err = dmaengine_slave_config(hdev->dma_lch,  &dma_conf);
	if (err) {
		dev_err(hdev->dev, "Couldn't configure DMA slave.\n");
		dma_release_channel(hdev->dma_lch);
		return err;
	}

	return 0;
}