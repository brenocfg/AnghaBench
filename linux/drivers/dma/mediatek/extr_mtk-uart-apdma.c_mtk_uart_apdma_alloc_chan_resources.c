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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mtk_uart_apdmadev {scalar_t__ support_33bits; TYPE_1__ ddev; } ;
struct mtk_chan {int /*<<< orphan*/  irq; scalar_t__ base; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  VFF_4G_SUPPORT ; 
 int /*<<< orphan*/  VFF_4G_SUPPORT_CLR_B ; 
 int /*<<< orphan*/  VFF_ADDR ; 
 scalar_t__ VFF_EN ; 
 int /*<<< orphan*/  VFF_LEN ; 
 int /*<<< orphan*/  VFF_RST ; 
 int /*<<< orphan*/  VFF_THRE ; 
 int /*<<< orphan*/  VFF_WARM_RST_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtk_uart_apdma_irq_handler ; 
 int /*<<< orphan*/  mtk_uart_apdma_write (struct mtk_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,unsigned int,int,int,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_chan*) ; 
 struct mtk_chan* to_mtk_uart_apdma_chan (struct dma_chan*) ; 
 struct mtk_uart_apdmadev* to_mtk_uart_apdma_dev (TYPE_2__*) ; 

__attribute__((used)) static int mtk_uart_apdma_alloc_chan_resources(struct dma_chan *chan)
{
	struct mtk_uart_apdmadev *mtkd = to_mtk_uart_apdma_dev(chan->device);
	struct mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	unsigned int status;
	int ret;

	ret = pm_runtime_get_sync(mtkd->ddev.dev);
	if (ret < 0) {
		pm_runtime_put_noidle(chan->device->dev);
		return ret;
	}

	mtk_uart_apdma_write(c, VFF_ADDR, 0);
	mtk_uart_apdma_write(c, VFF_THRE, 0);
	mtk_uart_apdma_write(c, VFF_LEN, 0);
	mtk_uart_apdma_write(c, VFF_RST, VFF_WARM_RST_B);

	ret = readx_poll_timeout(readl, c->base + VFF_EN,
			  status, !status, 10, 100);
	if (ret)
		return ret;

	ret = request_irq(c->irq, mtk_uart_apdma_irq_handler,
			  IRQF_TRIGGER_NONE, KBUILD_MODNAME, chan);
	if (ret < 0) {
		dev_err(chan->device->dev, "Can't request dma IRQ\n");
		return -EINVAL;
	}

	if (mtkd->support_33bits)
		mtk_uart_apdma_write(c, VFF_4G_SUPPORT, VFF_4G_SUPPORT_CLR_B);

	return ret;
}