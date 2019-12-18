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
typedef  unsigned long u32 ;
struct sunxi_rsb {scalar_t__ clk; scalar_t__ rstc; scalar_t__ regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ RSB_CCR ; 
 unsigned long RSB_CCR_CLK_DIV (int) ; 
 int RSB_CCR_MAX_CLK_DIV ; 
 unsigned long RSB_CCR_SDA_OUT_DELAY (unsigned long) ; 
 scalar_t__ RSB_CTRL ; 
 int /*<<< orphan*/  RSB_CTRL_NAME ; 
 unsigned long RSB_CTRL_SOFT_RST ; 
 unsigned long RSB_MAX_FREQ ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 scalar_t__ devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct sunxi_rsb* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sunxi_rsb*) ; 
 scalar_t__ devm_reset_control_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,unsigned long*) ; 
 int /*<<< orphan*/  of_rsb_register_devices (struct sunxi_rsb*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sunxi_rsb*) ; 
 int /*<<< orphan*/  readl_poll_timeout (scalar_t__,unsigned long,int,int,int) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 int reset_control_deassert (scalar_t__) ; 
 int sunxi_rsb_init_device_mode (struct sunxi_rsb*) ; 
 int /*<<< orphan*/  sunxi_rsb_irq ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int sunxi_rsb_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct resource *r;
	struct sunxi_rsb *rsb;
	unsigned long p_clk_freq;
	u32 clk_delay, clk_freq = 3000000;
	int clk_div, irq, ret;
	u32 reg;

	of_property_read_u32(np, "clock-frequency", &clk_freq);
	if (clk_freq > RSB_MAX_FREQ) {
		dev_err(dev,
			"clock-frequency (%u Hz) is too high (max = 20MHz)\n",
			clk_freq);
		return -EINVAL;
	}

	rsb = devm_kzalloc(dev, sizeof(*rsb), GFP_KERNEL);
	if (!rsb)
		return -ENOMEM;

	rsb->dev = dev;
	platform_set_drvdata(pdev, rsb);
	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rsb->regs = devm_ioremap_resource(dev, r);
	if (IS_ERR(rsb->regs))
		return PTR_ERR(rsb->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	rsb->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(rsb->clk)) {
		ret = PTR_ERR(rsb->clk);
		dev_err(dev, "failed to retrieve clk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(rsb->clk);
	if (ret) {
		dev_err(dev, "failed to enable clk: %d\n", ret);
		return ret;
	}

	p_clk_freq = clk_get_rate(rsb->clk);

	rsb->rstc = devm_reset_control_get(dev, NULL);
	if (IS_ERR(rsb->rstc)) {
		ret = PTR_ERR(rsb->rstc);
		dev_err(dev, "failed to retrieve reset controller: %d\n", ret);
		goto err_clk_disable;
	}

	ret = reset_control_deassert(rsb->rstc);
	if (ret) {
		dev_err(dev, "failed to deassert reset line: %d\n", ret);
		goto err_clk_disable;
	}

	init_completion(&rsb->complete);
	mutex_init(&rsb->lock);

	/* reset the controller */
	writel(RSB_CTRL_SOFT_RST, rsb->regs + RSB_CTRL);
	readl_poll_timeout(rsb->regs + RSB_CTRL, reg,
			   !(reg & RSB_CTRL_SOFT_RST), 1000, 100000);

	/*
	 * Clock frequency and delay calculation code is from
	 * Allwinner U-boot sources.
	 *
	 * From A83 user manual:
	 * bus clock frequency = parent clock frequency / (2 * (divider + 1))
	 */
	clk_div = p_clk_freq / clk_freq / 2;
	if (!clk_div)
		clk_div = 1;
	else if (clk_div > RSB_CCR_MAX_CLK_DIV + 1)
		clk_div = RSB_CCR_MAX_CLK_DIV + 1;

	clk_delay = clk_div >> 1;
	if (!clk_delay)
		clk_delay = 1;

	dev_info(dev, "RSB running at %lu Hz\n", p_clk_freq / clk_div / 2);
	writel(RSB_CCR_SDA_OUT_DELAY(clk_delay) | RSB_CCR_CLK_DIV(clk_div - 1),
	       rsb->regs + RSB_CCR);

	ret = devm_request_irq(dev, irq, sunxi_rsb_irq, 0, RSB_CTRL_NAME, rsb);
	if (ret) {
		dev_err(dev, "can't register interrupt handler irq %d: %d\n",
			irq, ret);
		goto err_reset_assert;
	}

	/* initialize all devices on the bus into RSB mode */
	ret = sunxi_rsb_init_device_mode(rsb);
	if (ret)
		dev_warn(dev, "Initialize device mode failed: %d\n", ret);

	of_rsb_register_devices(rsb);

	return 0;

err_reset_assert:
	reset_control_assert(rsb->rstc);

err_clk_disable:
	clk_disable_unprepare(rsb->clk);

	return ret;
}