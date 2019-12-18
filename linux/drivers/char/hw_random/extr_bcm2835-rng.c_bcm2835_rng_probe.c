#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct of_device_id {struct bcm2835_rng_of_data* data; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cleanup; int /*<<< orphan*/  read; int /*<<< orphan*/  init; int /*<<< orphan*/  name; } ;
struct bcm2835_rng_priv {TYPE_1__ rng; int /*<<< orphan*/  mask_interrupts; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct bcm2835_rng_of_data {int /*<<< orphan*/  mask_interrupts; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_rng_cleanup ; 
 int /*<<< orphan*/  bcm2835_rng_init ; 
 int /*<<< orphan*/  bcm2835_rng_of_match ; 
 int /*<<< orphan*/  bcm2835_rng_read ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ dev_of_node (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int devm_hwrng_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm2835_rng_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_rng_priv*) ; 

__attribute__((used)) static int bcm2835_rng_probe(struct platform_device *pdev)
{
	const struct bcm2835_rng_of_data *of_data;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	const struct of_device_id *rng_id;
	struct bcm2835_rng_priv *priv;
	struct resource *r;
	int err;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	/* map peripheral */
	priv->base = devm_ioremap_resource(dev, r);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	/* Clock is optional on most platforms */
	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk) && PTR_ERR(priv->clk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	priv->rng.name = pdev->name;
	priv->rng.init = bcm2835_rng_init;
	priv->rng.read = bcm2835_rng_read;
	priv->rng.cleanup = bcm2835_rng_cleanup;

	if (dev_of_node(dev)) {
		rng_id = of_match_node(bcm2835_rng_of_match, np);
		if (!rng_id)
			return -EINVAL;

		/* Check for rng init function, execute it */
		of_data = rng_id->data;
		if (of_data)
			priv->mask_interrupts = of_data->mask_interrupts;
	}

	/* register driver */
	err = devm_hwrng_register(dev, &priv->rng);
	if (err)
		dev_err(dev, "hwrng registration failed\n");
	else
		dev_info(dev, "hwrng registered\n");

	return err;
}