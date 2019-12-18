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
typedef  void* u32 ;
struct dma_slave_config {int direction; int src_addr_width; int dst_addr_width; scalar_t__ src_addr; scalar_t__ dst_addr; void* dst_maxburst; void* src_maxburst; } ;
struct dma_async_tx_descriptor {struct atmel_aes_dev* callback_param; int /*<<< orphan*/ * callback; } ;
struct atmel_aes_dma {int /*<<< orphan*/  chan; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct atmel_aes_dev {scalar_t__ phys_base; struct atmel_aes_dma dst; struct atmel_aes_dma src; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
typedef  int /*<<< orphan*/ * dma_async_tx_callback ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 scalar_t__ AES_IDATAR (int /*<<< orphan*/ ) ; 
 scalar_t__ AES_ODATAR (int /*<<< orphan*/ ) ; 
 int DMA_CTRL_ACK ; 
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int DMA_PREP_INTERRUPT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * atmel_aes_dma_callback ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atmel_aes_dma_transfer_start(struct atmel_aes_dev *dd,
					enum dma_slave_buswidth addr_width,
					enum dma_transfer_direction dir,
					u32 maxburst)
{
	struct dma_async_tx_descriptor *desc;
	struct dma_slave_config config;
	dma_async_tx_callback callback;
	struct atmel_aes_dma *dma;
	int err;

	memset(&config, 0, sizeof(config));
	config.direction = dir;
	config.src_addr_width = addr_width;
	config.dst_addr_width = addr_width;
	config.src_maxburst = maxburst;
	config.dst_maxburst = maxburst;

	switch (dir) {
	case DMA_MEM_TO_DEV:
		dma = &dd->src;
		callback = NULL;
		config.dst_addr = dd->phys_base + AES_IDATAR(0);
		break;

	case DMA_DEV_TO_MEM:
		dma = &dd->dst;
		callback = atmel_aes_dma_callback;
		config.src_addr = dd->phys_base + AES_ODATAR(0);
		break;

	default:
		return -EINVAL;
	}

	err = dmaengine_slave_config(dma->chan, &config);
	if (err)
		return err;

	desc = dmaengine_prep_slave_sg(dma->chan, dma->sg, dma->sg_len, dir,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc)
		return -ENOMEM;

	desc->callback = callback;
	desc->callback_param = dd;
	dmaengine_submit(desc);
	dma_async_issue_pending(dma->chan);

	return 0;
}