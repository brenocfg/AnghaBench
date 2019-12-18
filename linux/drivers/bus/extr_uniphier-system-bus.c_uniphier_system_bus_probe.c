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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct uniphier_system_bus_priv {struct device* dev; int /*<<< orphan*/  membase; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_BAD_ADDR ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct uniphier_system_bus_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int of_n_addr_cells (int /*<<< orphan*/ ) ; 
 int of_platform_default_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ of_translate_address (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_system_bus_priv*) ; 
 int uniphier_system_bus_add_bank (struct uniphier_system_bus_priv*,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  uniphier_system_bus_check_boot_swap (struct uniphier_system_bus_priv*) ; 
 int uniphier_system_bus_check_overlap (struct uniphier_system_bus_priv*) ; 
 int /*<<< orphan*/  uniphier_system_bus_set_reg (struct uniphier_system_bus_priv*) ; 

__attribute__((used)) static int uniphier_system_bus_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uniphier_system_bus_priv *priv;
	const __be32 *ranges;
	u32 cells, addr, size;
	u64 paddr;
	int pna, bank, rlen, rone, ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->membase = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->membase))
		return PTR_ERR(priv->membase);

	priv->dev = dev;

	pna = of_n_addr_cells(dev->of_node);

	ret = of_property_read_u32(dev->of_node, "#address-cells", &cells);
	if (ret) {
		dev_err(dev, "failed to get #address-cells\n");
		return ret;
	}
	if (cells != 2) {
		dev_err(dev, "#address-cells must be 2\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(dev->of_node, "#size-cells", &cells);
	if (ret) {
		dev_err(dev, "failed to get #size-cells\n");
		return ret;
	}
	if (cells != 1) {
		dev_err(dev, "#size-cells must be 1\n");
		return -EINVAL;
	}

	ranges = of_get_property(dev->of_node, "ranges", &rlen);
	if (!ranges) {
		dev_err(dev, "failed to get ranges property\n");
		return -ENOENT;
	}

	rlen /= sizeof(*ranges);
	rone = pna + 2;

	for (; rlen >= rone; rlen -= rone) {
		bank = be32_to_cpup(ranges++);
		addr = be32_to_cpup(ranges++);
		paddr = of_translate_address(dev->of_node, ranges);
		if (paddr == OF_BAD_ADDR)
			return -EINVAL;
		ranges += pna;
		size = be32_to_cpup(ranges++);

		ret = uniphier_system_bus_add_bank(priv, bank, addr,
						   paddr, size);
		if (ret)
			return ret;
	}

	ret = uniphier_system_bus_check_overlap(priv);
	if (ret)
		return ret;

	uniphier_system_bus_check_boot_swap(priv);

	uniphier_system_bus_set_reg(priv);

	platform_set_drvdata(pdev, priv);

	/* Now, the bus is configured.  Populate platform_devices below it */
	return of_platform_default_populate(dev->of_node, NULL, dev);
}