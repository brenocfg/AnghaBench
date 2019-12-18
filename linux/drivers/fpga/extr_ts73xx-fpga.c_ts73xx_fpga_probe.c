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
struct ts73xx_fpga_priv {int /*<<< orphan*/  io_base; struct device* dev; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct fpga_manager* devm_fpga_mgr_create (struct device*,char*,int /*<<< orphan*/ *,struct ts73xx_fpga_priv*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ts73xx_fpga_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_manager*) ; 
 int /*<<< orphan*/  ts73xx_fpga_ops ; 

__attribute__((used)) static int ts73xx_fpga_probe(struct platform_device *pdev)
{
	struct device *kdev = &pdev->dev;
	struct ts73xx_fpga_priv *priv;
	struct fpga_manager *mgr;
	struct resource *res;

	priv = devm_kzalloc(kdev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = kdev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->io_base = devm_ioremap_resource(kdev, res);
	if (IS_ERR(priv->io_base)) {
		dev_err(kdev, "unable to remap registers\n");
		return PTR_ERR(priv->io_base);
	}

	mgr = devm_fpga_mgr_create(kdev, "TS-73xx FPGA Manager",
				   &ts73xx_fpga_ops, priv);
	if (!mgr)
		return -ENOMEM;

	platform_set_drvdata(pdev, mgr);

	return fpga_mgr_register(mgr);
}