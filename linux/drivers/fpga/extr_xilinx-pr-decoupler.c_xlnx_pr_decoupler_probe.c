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
struct xlnx_pr_decoupler_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  io_base; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fpga_bridge {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct fpga_bridge* devm_fpga_bridge_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct xlnx_pr_decoupler_data*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct xlnx_pr_decoupler_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fpga_bridge_register (struct fpga_bridge*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_bridge*) ; 
 int /*<<< orphan*/  xlnx_pr_decoupler_br_ops ; 

__attribute__((used)) static int xlnx_pr_decoupler_probe(struct platform_device *pdev)
{
	struct xlnx_pr_decoupler_data *priv;
	struct fpga_bridge *br;
	int err;
	struct resource *res;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->io_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->io_base))
		return PTR_ERR(priv->io_base);

	priv->clk = devm_clk_get(&pdev->dev, "aclk");
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "input clock not found\n");
		return PTR_ERR(priv->clk);
	}

	err = clk_prepare_enable(priv->clk);
	if (err) {
		dev_err(&pdev->dev, "unable to enable clock\n");
		return err;
	}

	clk_disable(priv->clk);

	br = devm_fpga_bridge_create(&pdev->dev, "Xilinx PR Decoupler",
				     &xlnx_pr_decoupler_br_ops, priv);
	if (!br) {
		err = -ENOMEM;
		goto err_clk;
	}

	platform_set_drvdata(pdev, br);

	err = fpga_bridge_register(br);
	if (err) {
		dev_err(&pdev->dev, "unable to register Xilinx PR Decoupler");
		goto err_clk;
	}

	return 0;

err_clk:
	clk_unprepare(priv->clk);

	return err;
}