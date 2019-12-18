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
struct socfpga_fpga_priv {scalar_t__ irq; void* fpga_data_addr; void* fpga_base_addr; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct fpga_manager* devm_fpga_mgr_create (struct device*,char*,int /*<<< orphan*/ *,struct socfpga_fpga_priv*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct socfpga_fpga_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socfpga_fpga_priv*) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_manager*) ; 
 int /*<<< orphan*/  socfpga_fpga_isr ; 
 int /*<<< orphan*/  socfpga_fpga_ops ; 

__attribute__((used)) static int socfpga_fpga_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct socfpga_fpga_priv *priv;
	struct fpga_manager *mgr;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->fpga_base_addr = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->fpga_base_addr))
		return PTR_ERR(priv->fpga_base_addr);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->fpga_data_addr = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->fpga_data_addr))
		return PTR_ERR(priv->fpga_data_addr);

	priv->irq = platform_get_irq(pdev, 0);
	if (priv->irq < 0)
		return priv->irq;

	ret = devm_request_irq(dev, priv->irq, socfpga_fpga_isr, 0,
			       dev_name(dev), priv);
	if (ret)
		return ret;

	mgr = devm_fpga_mgr_create(dev, "Altera SOCFPGA FPGA Manager",
				   &socfpga_fpga_ops, priv);
	if (!mgr)
		return -ENOMEM;

	platform_set_drvdata(pdev, mgr);

	return fpga_mgr_register(mgr);
}