#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;struct arasan_cf_dev* callback_param; int /*<<< orphan*/  callback; } ;
struct arasan_cf_dev {TYPE_2__* host; int /*<<< orphan*/  dma_completion; struct dma_chan* dma_chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* device_issue_pending ) (struct dma_chan*) ;struct dma_async_tx_descriptor* (* device_prep_dma_memcpy ) (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 unsigned long DMA_PREP_INTERRUPT ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_callback ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* stub1 (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub3 (struct dma_chan*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dma_xfer(struct arasan_cf_dev *acdev, dma_addr_t src, dma_addr_t dest, u32 len)
{
	struct dma_async_tx_descriptor *tx;
	struct dma_chan *chan = acdev->dma_chan;
	dma_cookie_t cookie;
	unsigned long flags = DMA_PREP_INTERRUPT;
	int ret = 0;

	tx = chan->device->device_prep_dma_memcpy(chan, dest, src, len, flags);
	if (!tx) {
		dev_err(acdev->host->dev, "device_prep_dma_memcpy failed\n");
		return -EAGAIN;
	}

	tx->callback = dma_callback;
	tx->callback_param = acdev;
	cookie = tx->tx_submit(tx);

	ret = dma_submit_error(cookie);
	if (ret) {
		dev_err(acdev->host->dev, "dma_submit_error\n");
		return ret;
	}

	chan->device->device_issue_pending(chan);

	/* Wait for DMA to complete */
	if (!wait_for_completion_timeout(&acdev->dma_completion, TIMEOUT)) {
		dmaengine_terminate_all(chan);
		dev_err(acdev->host->dev, "wait_for_completion_timeout\n");
		return -ETIMEDOUT;
	}

	return ret;
}