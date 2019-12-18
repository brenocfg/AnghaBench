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
struct st_ahci_drv_data {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct ahci_host_priv {int /*<<< orphan*/  force_port_map; int /*<<< orphan*/  mmio; struct st_ahci_drv_data* plat_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 struct st_ahci_drv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_ahci_configure_oob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_ahci_port_info ; 
 int st_ahci_probe_resets (struct ahci_host_priv*,struct device*) ; 

__attribute__((used)) static int st_ahci_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct st_ahci_drv_data *drv_data;
	struct ahci_host_priv *hpriv;
	int err;

	drv_data = devm_kzalloc(&pdev->dev, sizeof(*drv_data), GFP_KERNEL);
	if (!drv_data)
		return -ENOMEM;

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);
	hpriv->plat_data = drv_data;

	err = st_ahci_probe_resets(hpriv, &pdev->dev);
	if (err)
		return err;

	err = ahci_platform_enable_resources(hpriv);
	if (err)
		return err;

	st_ahci_configure_oob(hpriv->mmio);

	of_property_read_u32(dev->of_node,
			     "ports-implemented", &hpriv->force_port_map);

	err = ahci_platform_init_host(pdev, hpriv, &st_ahci_port_info,
				      &ahci_platform_sht);
	if (err) {
		ahci_platform_disable_resources(hpriv);
		return err;
	}

	return 0;
}