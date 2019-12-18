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
typedef  int uint32_t ;
struct dcp_dma_desc {int dummy; } ;
struct dcp_async_ctx {int chan; } ;
struct dcp {int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/ * completion; TYPE_1__* coh; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {struct dcp_dma_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ MXS_DCP_CH_N_CMDPTR (int const) ; 
 scalar_t__ MXS_DCP_CH_N_SEMA (int const) ; 
 scalar_t__ MXS_DCP_CH_N_STAT (int const) ; 
 scalar_t__ MXS_DCP_CH_N_STAT_CLR (int const) ; 
 scalar_t__ MXS_DCP_STAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int const,int) ; 
 int dma_map_single (int /*<<< orphan*/ ,struct dcp_dma_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct dcp* global_sdcp ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_dcp_start_dma(struct dcp_async_ctx *actx)
{
	struct dcp *sdcp = global_sdcp;
	const int chan = actx->chan;
	uint32_t stat;
	unsigned long ret;
	struct dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];

	dma_addr_t desc_phys = dma_map_single(sdcp->dev, desc, sizeof(*desc),
					      DMA_TO_DEVICE);

	reinit_completion(&sdcp->completion[chan]);

	/* Clear status register. */
	writel(0xffffffff, sdcp->base + MXS_DCP_CH_N_STAT_CLR(chan));

	/* Load the DMA descriptor. */
	writel(desc_phys, sdcp->base + MXS_DCP_CH_N_CMDPTR(chan));

	/* Increment the semaphore to start the DMA transfer. */
	writel(1, sdcp->base + MXS_DCP_CH_N_SEMA(chan));

	ret = wait_for_completion_timeout(&sdcp->completion[chan],
					  msecs_to_jiffies(1000));
	if (!ret) {
		dev_err(sdcp->dev, "Channel %i timeout (DCP_STAT=0x%08x)\n",
			chan, readl(sdcp->base + MXS_DCP_STAT));
		return -ETIMEDOUT;
	}

	stat = readl(sdcp->base + MXS_DCP_CH_N_STAT(chan));
	if (stat & 0xff) {
		dev_err(sdcp->dev, "Channel %i error (CH_STAT=0x%08x)\n",
			chan, stat);
		return -EINVAL;
	}

	dma_unmap_single(sdcp->dev, desc_phys, sizeof(*desc), DMA_TO_DEVICE);

	return 0;
}