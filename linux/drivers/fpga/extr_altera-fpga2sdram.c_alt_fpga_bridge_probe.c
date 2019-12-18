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
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct fpga_bridge {int dummy; } ;
struct alt_fpga2sdram_data {char* mask; struct regmap* sdrctl; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  F2S_BRIDGE_NAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  SYSMGR_ISWGRP_HANDOFF3 ; 
 int _alt_fpga2sdram_enable_set (struct alt_fpga2sdram_data*,int) ; 
 int /*<<< orphan*/  altera_fpga2sdram_br_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct fpga_bridge* devm_fpga_bridge_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct alt_fpga2sdram_data*) ; 
 struct alt_fpga2sdram_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fpga_bridge_register (struct fpga_bridge*) ; 
 int /*<<< orphan*/  fpga_bridge_unregister (struct fpga_bridge*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_bridge*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,char**) ; 
 void* syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int alt_fpga_bridge_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct alt_fpga2sdram_data *priv;
	struct fpga_bridge *br;
	u32 enable;
	struct regmap *sysmgr;
	int ret = 0;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;

	priv->sdrctl = syscon_regmap_lookup_by_compatible("altr,sdr-ctl");
	if (IS_ERR(priv->sdrctl)) {
		dev_err(dev, "regmap for altr,sdr-ctl lookup failed.\n");
		return PTR_ERR(priv->sdrctl);
	}

	sysmgr = syscon_regmap_lookup_by_compatible("altr,sys-mgr");
	if (IS_ERR(sysmgr)) {
		dev_err(dev, "regmap for altr,sys-mgr lookup failed.\n");
		return PTR_ERR(sysmgr);
	}

	/* Get f2s bridge configuration saved in handoff register */
	regmap_read(sysmgr, SYSMGR_ISWGRP_HANDOFF3, &priv->mask);

	br = devm_fpga_bridge_create(dev, F2S_BRIDGE_NAME,
				     &altera_fpga2sdram_br_ops, priv);
	if (!br)
		return -ENOMEM;

	platform_set_drvdata(pdev, br);

	ret = fpga_bridge_register(br);
	if (ret)
		return ret;

	dev_info(dev, "driver initialized with handoff %08x\n", priv->mask);

	if (!of_property_read_u32(dev->of_node, "bridge-enable", &enable)) {
		if (enable > 1) {
			dev_warn(dev, "invalid bridge-enable %u > 1\n", enable);
		} else {
			dev_info(dev, "%s bridge\n",
				 (enable ? "enabling" : "disabling"));
			ret = _alt_fpga2sdram_enable_set(priv, enable);
			if (ret) {
				fpga_bridge_unregister(br);
				return ret;
			}
		}
	}

	return ret;
}