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
struct mic_dma_device {int /*<<< orphan*/  dbg_dir; } ;
struct TYPE_2__ {scalar_t__ device; } ;
struct mbus_device {int /*<<< orphan*/  dev; TYPE_1__ id; } ;
typedef  enum mic_dma_chan_owner { ____Placeholder_mic_dma_chan_owner } mic_dma_chan_owner ;

/* Variables and functions */
 scalar_t__ MBUS_DEV_DMA_MIC ; 
 int MIC_DMA_CHAN_HOST ; 
 int MIC_DMA_CHAN_MIC ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mic_dma_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct mic_dma_device*) ; 
 scalar_t__ mic_dma_dbg ; 
 struct mic_dma_device* mic_dma_dev_reg (struct mbus_device*,int) ; 
 int /*<<< orphan*/  mic_dma_reg_fops ; 

__attribute__((used)) static int mic_dma_driver_probe(struct mbus_device *mbdev)
{
	struct mic_dma_device *mic_dma_dev;
	enum mic_dma_chan_owner owner;

	if (MBUS_DEV_DMA_MIC == mbdev->id.device)
		owner = MIC_DMA_CHAN_MIC;
	else
		owner = MIC_DMA_CHAN_HOST;

	mic_dma_dev = mic_dma_dev_reg(mbdev, owner);
	dev_set_drvdata(&mbdev->dev, mic_dma_dev);

	if (mic_dma_dbg) {
		mic_dma_dev->dbg_dir = debugfs_create_dir(dev_name(&mbdev->dev),
							  mic_dma_dbg);
		debugfs_create_file("mic_dma_reg", 0444, mic_dma_dev->dbg_dir,
				    mic_dma_dev, &mic_dma_reg_fops);
	}
	return 0;
}