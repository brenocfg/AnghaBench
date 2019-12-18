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
typedef  int u32 ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct fpga_bridge {int dummy; } ;
struct altera_hps2fpga_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  name; int /*<<< orphan*/  l3reg; scalar_t__ remap_mask; int /*<<< orphan*/  bridge_reset; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int _alt_hps2fpga_enable_set (struct altera_hps2fpga_data*,int) ; 
 int /*<<< orphan*/  altera_fpga_of_match ; 
 int /*<<< orphan*/  altera_hps2fpga_br_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct fpga_bridge* devm_fpga_bridge_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct altera_hps2fpga_data*) ; 
 int fpga_bridge_register (struct fpga_bridge*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  of_reset_control_get_exclusive_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_bridge*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int alt_fpga_bridge_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct altera_hps2fpga_data *priv;
	const struct of_device_id *of_id;
	struct fpga_bridge *br;
	u32 enable;
	int ret;

	of_id = of_match_device(altera_fpga_of_match, dev);
	if (!of_id) {
		dev_err(dev, "failed to match device\n");
		return -ENODEV;
	}

	priv = (struct altera_hps2fpga_data *)of_id->data;

	priv->bridge_reset = of_reset_control_get_exclusive_by_index(dev->of_node,
								     0);
	if (IS_ERR(priv->bridge_reset)) {
		dev_err(dev, "Could not get %s reset control\n", priv->name);
		return PTR_ERR(priv->bridge_reset);
	}

	if (priv->remap_mask) {
		priv->l3reg = syscon_regmap_lookup_by_compatible("altr,l3regs");
		if (IS_ERR(priv->l3reg)) {
			dev_err(dev, "regmap for altr,l3regs lookup failed\n");
			return PTR_ERR(priv->l3reg);
		}
	}

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "no clock specified\n");
		return PTR_ERR(priv->clk);
	}

	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(dev, "could not enable clock\n");
		return -EBUSY;
	}

	if (!of_property_read_u32(dev->of_node, "bridge-enable", &enable)) {
		if (enable > 1) {
			dev_warn(dev, "invalid bridge-enable %u > 1\n", enable);
		} else {
			dev_info(dev, "%s bridge\n",
				 (enable ? "enabling" : "disabling"));

			ret = _alt_hps2fpga_enable_set(priv, enable);
			if (ret)
				goto err;
		}
	}

	br = devm_fpga_bridge_create(dev, priv->name,
				     &altera_hps2fpga_br_ops, priv);
	if (!br) {
		ret = -ENOMEM;
		goto err;
	}

	platform_set_drvdata(pdev, br);

	ret = fpga_bridge_register(br);
	if (ret)
		goto err;

	return 0;

err:
	clk_disable_unprepare(priv->clk);

	return ret;
}