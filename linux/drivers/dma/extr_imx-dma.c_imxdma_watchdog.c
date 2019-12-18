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
struct timer_list {int dummy; } ;
struct imxdma_engine {int /*<<< orphan*/  dev; } ;
struct imxdma_channel {int channel; int /*<<< orphan*/  dma_tasklet; struct imxdma_engine* imxdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CCR (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct imxdma_channel* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_dmav1_writel (struct imxdma_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imxdma_channel* imxdmac ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog ; 

__attribute__((used)) static void imxdma_watchdog(struct timer_list *t)
{
	struct imxdma_channel *imxdmac = from_timer(imxdmac, t, watchdog);
	struct imxdma_engine *imxdma = imxdmac->imxdma;
	int channel = imxdmac->channel;

	imx_dmav1_writel(imxdma, 0, DMA_CCR(channel));

	/* Tasklet watchdog error handler */
	tasklet_schedule(&imxdmac->dma_tasklet);
	dev_dbg(imxdma->dev, "channel %d: watchdog timeout!\n",
		imxdmac->channel);
}