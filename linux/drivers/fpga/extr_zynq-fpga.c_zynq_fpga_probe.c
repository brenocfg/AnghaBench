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
struct zynq_fpga_priv {scalar_t__ irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_done; int /*<<< orphan*/  slcr; int /*<<< orphan*/  io_base; int /*<<< orphan*/  dma_lock; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_STS_OFFSET ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXR_ALL_MASK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK_MASK ; 
 int /*<<< orphan*/  UNLOCK_OFFSET ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 struct fpga_manager* devm_fpga_mgr_create (struct device*,char*,int /*<<< orphan*/ *,struct zynq_fpga_priv*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct zynq_fpga_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zynq_fpga_priv*) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_manager*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zynq_fpga_isr ; 
 int /*<<< orphan*/  zynq_fpga_ops ; 
 int /*<<< orphan*/  zynq_fpga_set_irq (struct zynq_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_fpga_write (struct zynq_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zynq_fpga_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct zynq_fpga_priv *priv;
	struct fpga_manager *mgr;
	struct resource *res;
	int err;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	spin_lock_init(&priv->dma_lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->io_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->io_base))
		return PTR_ERR(priv->io_base);

	priv->slcr = syscon_regmap_lookup_by_phandle(dev->of_node,
		"syscon");
	if (IS_ERR(priv->slcr)) {
		dev_err(dev, "unable to get zynq-slcr regmap\n");
		return PTR_ERR(priv->slcr);
	}

	init_completion(&priv->dma_done);

	priv->irq = platform_get_irq(pdev, 0);
	if (priv->irq < 0) {
		dev_err(dev, "No IRQ available\n");
		return priv->irq;
	}

	priv->clk = devm_clk_get(dev, "ref_clk");
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "input clock not found\n");
		return PTR_ERR(priv->clk);
	}

	err = clk_prepare_enable(priv->clk);
	if (err) {
		dev_err(dev, "unable to enable clock\n");
		return err;
	}

	/* unlock the device */
	zynq_fpga_write(priv, UNLOCK_OFFSET, UNLOCK_MASK);

	zynq_fpga_set_irq(priv, 0);
	zynq_fpga_write(priv, INT_STS_OFFSET, IXR_ALL_MASK);
	err = devm_request_irq(dev, priv->irq, zynq_fpga_isr, 0, dev_name(dev),
			       priv);
	if (err) {
		dev_err(dev, "unable to request IRQ\n");
		clk_disable_unprepare(priv->clk);
		return err;
	}

	clk_disable(priv->clk);

	mgr = devm_fpga_mgr_create(dev, "Xilinx Zynq FPGA Manager",
				   &zynq_fpga_ops, priv);
	if (!mgr)
		return -ENOMEM;

	platform_set_drvdata(pdev, mgr);

	err = fpga_mgr_register(mgr);
	if (err) {
		dev_err(dev, "unable to register FPGA manager\n");
		clk_unprepare(priv->clk);
		return err;
	}

	return 0;
}