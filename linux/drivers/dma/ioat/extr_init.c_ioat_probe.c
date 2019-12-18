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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct dma_device {int /*<<< orphan*/  chancnt; struct device* dev; int /*<<< orphan*/  cap_mask; } ;
struct ioatdma_device {int /*<<< orphan*/  completion_pool; struct pci_dev* pdev; struct dma_device dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_create (char*,struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int ioat3_dma_self_test (struct ioatdma_device*) ; 
 int /*<<< orphan*/  ioat_disable_interrupts (struct ioatdma_device*) ; 
 int ioat_dma_setup_interrupts (struct ioatdma_device*) ; 
 int /*<<< orphan*/  ioat_enumerate_channels (struct ioatdma_device*) ; 

__attribute__((used)) static int ioat_probe(struct ioatdma_device *ioat_dma)
{
	int err = -ENODEV;
	struct dma_device *dma = &ioat_dma->dma_dev;
	struct pci_dev *pdev = ioat_dma->pdev;
	struct device *dev = &pdev->dev;

	ioat_dma->completion_pool = dma_pool_create("completion_pool", dev,
						    sizeof(u64),
						    SMP_CACHE_BYTES,
						    SMP_CACHE_BYTES);

	if (!ioat_dma->completion_pool) {
		err = -ENOMEM;
		goto err_out;
	}

	ioat_enumerate_channels(ioat_dma);

	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma->dev = &pdev->dev;

	if (!dma->chancnt) {
		dev_err(dev, "channel enumeration error\n");
		goto err_setup_interrupts;
	}

	err = ioat_dma_setup_interrupts(ioat_dma);
	if (err)
		goto err_setup_interrupts;

	err = ioat3_dma_self_test(ioat_dma);
	if (err)
		goto err_self_test;

	return 0;

err_self_test:
	ioat_disable_interrupts(ioat_dma);
err_setup_interrupts:
	dma_pool_destroy(ioat_dma->completion_pool);
err_out:
	return err;
}