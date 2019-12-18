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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHAN_ON ; 
 int DMA_CHAN_RST ; 
 int DMA_CLK_DIV4 ; 
 int DMA_MAX_CHANNEL ; 
 int DMA_POLL ; 
 int /*<<< orphan*/  DMA_RESET ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  LTQ_DMA_CCTRL ; 
 int /*<<< orphan*/  LTQ_DMA_CPOLL ; 
 int /*<<< orphan*/  LTQ_DMA_CS ; 
 int /*<<< orphan*/  LTQ_DMA_CTRL ; 
 int /*<<< orphan*/  LTQ_DMA_ID ; 
 int /*<<< orphan*/  LTQ_DMA_IRNEN ; 
 int /*<<< orphan*/  clk_enable (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 struct clk* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct clk* ltq_dma_membase ; 
 unsigned int ltq_dma_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_w32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ltq_dma_init(struct platform_device *pdev)
{
	struct clk *clk;
	struct resource *res;
	unsigned id;
	int i;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ltq_dma_membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ltq_dma_membase))
		panic("Failed to remap dma resource");

	/* power up and reset the dma engine */
	clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk))
		panic("Failed to get dma clock");

	clk_enable(clk);
	ltq_dma_w32_mask(0, DMA_RESET, LTQ_DMA_CTRL);

	/* disable all interrupts */
	ltq_dma_w32(0, LTQ_DMA_IRNEN);

	/* reset/configure each channel */
	for (i = 0; i < DMA_MAX_CHANNEL; i++) {
		ltq_dma_w32(i, LTQ_DMA_CS);
		ltq_dma_w32(DMA_CHAN_RST, LTQ_DMA_CCTRL);
		ltq_dma_w32(DMA_POLL | DMA_CLK_DIV4, LTQ_DMA_CPOLL);
		ltq_dma_w32_mask(DMA_CHAN_ON, 0, LTQ_DMA_CCTRL);
	}

	id = ltq_dma_r32(LTQ_DMA_ID);
	dev_info(&pdev->dev,
		"Init done - hw rev: %X, ports: %d, channels: %d\n",
		id & 0x1f, (id >> 16) & 0xf, id >> 20);

	return 0;
}