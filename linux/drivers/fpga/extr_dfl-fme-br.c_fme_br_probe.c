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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct fpga_bridge {int dummy; } ;
struct fme_br_priv {int /*<<< orphan*/  pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_get_platdata (struct device*) ; 
 struct fpga_bridge* devm_fpga_bridge_create (struct device*,char*,int /*<<< orphan*/ *,struct fme_br_priv*) ; 
 struct fme_br_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fme_bridge_ops ; 
 int fpga_bridge_register (struct fpga_bridge*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_bridge*) ; 

__attribute__((used)) static int fme_br_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fme_br_priv *priv;
	struct fpga_bridge *br;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->pdata = dev_get_platdata(dev);

	br = devm_fpga_bridge_create(dev, "DFL FPGA FME Bridge",
				     &fme_bridge_ops, priv);
	if (!br)
		return -ENOMEM;

	platform_set_drvdata(pdev, br);

	return fpga_bridge_register(br);
}