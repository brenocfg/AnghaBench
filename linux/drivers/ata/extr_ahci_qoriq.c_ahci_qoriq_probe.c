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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct ahci_qoriq_priv {int type; int /*<<< orphan*/  is_dmacoherent; struct ahci_host_priv* ecc_addr; } ;
struct ahci_host_priv {struct ahci_qoriq_priv* plat_data; } ;
typedef  enum ahci_qoriq_type { ____Placeholder_ahci_qoriq_type } ahci_qoriq_type ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_qoriq_of_match ; 
 int ahci_qoriq_phy_init (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_qoriq_port_info ; 
 int /*<<< orphan*/  ahci_qoriq_sht ; 
 struct ahci_host_priv* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ahci_qoriq_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecc_initialized ; 
 int /*<<< orphan*/  of_dma_is_coherent (struct device_node*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ahci_qoriq_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct ahci_host_priv *hpriv;
	struct ahci_qoriq_priv *qoriq_priv;
	const struct of_device_id *of_id;
	struct resource *res;
	int rc;

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	of_id = of_match_node(ahci_qoriq_of_match, np);
	if (!of_id)
		return -ENODEV;

	qoriq_priv = devm_kzalloc(dev, sizeof(*qoriq_priv), GFP_KERNEL);
	if (!qoriq_priv)
		return -ENOMEM;

	qoriq_priv->type = (enum ahci_qoriq_type)of_id->data;

	if (unlikely(!ecc_initialized)) {
		res = platform_get_resource_byname(pdev,
						   IORESOURCE_MEM,
						   "sata-ecc");
		if (res) {
			qoriq_priv->ecc_addr =
				devm_ioremap_resource(dev, res);
			if (IS_ERR(qoriq_priv->ecc_addr))
				return PTR_ERR(qoriq_priv->ecc_addr);
		}
	}

	qoriq_priv->is_dmacoherent = of_dma_is_coherent(np);

	rc = ahci_platform_enable_resources(hpriv);
	if (rc)
		return rc;

	hpriv->plat_data = qoriq_priv;
	rc = ahci_qoriq_phy_init(hpriv);
	if (rc)
		goto disable_resources;

	rc = ahci_platform_init_host(pdev, hpriv, &ahci_qoriq_port_info,
				     &ahci_qoriq_sht);
	if (rc)
		goto disable_resources;

	return 0;

disable_resources:
	ahci_platform_disable_resources(hpriv);

	return rc;
}