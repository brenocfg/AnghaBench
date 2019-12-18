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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct mcs814x_rng_priv {unsigned long priv; int /*<<< orphan*/  regs; int /*<<< orphan*/  data_read; int /*<<< orphan*/  name; } ;
struct hwrng {unsigned long priv; int /*<<< orphan*/  regs; int /*<<< orphan*/  data_read; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int hwrng_register (struct mcs814x_rng_priv*) ; 
 int /*<<< orphan*/  kfree (struct mcs814x_rng_priv*) ; 
 struct mcs814x_rng_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs814x_rng_data_read ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mcs814x_rng_priv*) ; 

__attribute__((used)) static int mcs814x_rng_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct mcs814x_rng_priv *priv;
	struct hwrng *rng;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		ret = -ENOMEM;
		goto out;
	}

	rng = kzalloc(sizeof(*rng), GFP_KERNEL);
	if (!rng) {
		ret = -ENOMEM;
		goto out_priv;
	}

	platform_set_drvdata(pdev, rng);
	rng->priv = (unsigned long)priv;
	rng->name = pdev->name;
	rng->data_read = mcs814x_rng_data_read;

	priv->regs = devm_ioremap_resource(&pdev->dev, res);
	if (!priv->regs) {
		ret = -ENOMEM;
		goto out_rng;
	}

	ret = hwrng_register(rng);
	if (ret) {
		dev_err(&pdev->dev, "failed to register hwrng driver\n");
		goto out;
	}

	dev_info(&pdev->dev, "registered\n");

	return ret;

out_rng:
	platform_set_drvdata(pdev, NULL);
	kfree(rng);
out_priv:
	kfree(priv);
out:
	return ret;
}