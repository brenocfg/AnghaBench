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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct brcm_ahci_priv {int version; int quirks; int /*<<< orphan*/  port_mask; int /*<<< orphan*/  rcdev; struct ahci_host_priv* top_ctrl; struct device* dev; } ;
struct ahci_host_priv {int /*<<< orphan*/  flags; struct brcm_ahci_priv* plat_data; } ;
typedef  enum brcm_ahci_version { ____Placeholder_brcm_ahci_version } brcm_ahci_version ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_HFLAG_NO_NCQ ; 
 int /*<<< orphan*/  AHCI_HFLAG_NO_WRITE_TO_RO ; 
 int /*<<< orphan*/  AHCI_HFLAG_WAKE_BEFORE_STOP ; 
 int BRCM_AHCI_QUIRK_NO_NCQ ; 
 int BRCM_AHCI_QUIRK_SKIP_PHY_ENABLE ; 
 scalar_t__ BRCM_SATA_BCM7425 ; 
 scalar_t__ BRCM_SATA_NSP ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_brcm_port_info ; 
 int /*<<< orphan*/  ahci_of_match ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 int /*<<< orphan*/  brcm_ahci_get_portmask (struct platform_device*,struct brcm_ahci_priv*) ; 
 int /*<<< orphan*/  brcm_sata_alpm_init (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  brcm_sata_init (struct brcm_ahci_priv*) ; 
 int /*<<< orphan*/  brcm_sata_phys_enable (struct brcm_ahci_priv*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct ahci_host_priv* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct brcm_ahci_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcm_ahci_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id;
	struct device *dev = &pdev->dev;
	struct brcm_ahci_priv *priv;
	struct ahci_host_priv *hpriv;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	of_id = of_match_node(ahci_of_match, pdev->dev.of_node);
	if (!of_id)
		return -ENODEV;

	priv->version = (enum brcm_ahci_version)of_id->data;
	priv->dev = dev;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "top-ctrl");
	priv->top_ctrl = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->top_ctrl))
		return PTR_ERR(priv->top_ctrl);

	/* Reset is optional depending on platform */
	priv->rcdev = devm_reset_control_get(&pdev->dev, "ahci");
	if (!IS_ERR_OR_NULL(priv->rcdev))
		reset_control_deassert(priv->rcdev);

	if ((priv->version == BRCM_SATA_BCM7425) ||
		(priv->version == BRCM_SATA_NSP)) {
		priv->quirks |= BRCM_AHCI_QUIRK_NO_NCQ;
		priv->quirks |= BRCM_AHCI_QUIRK_SKIP_PHY_ENABLE;
	}

	brcm_sata_init(priv);

	priv->port_mask = brcm_ahci_get_portmask(pdev, priv);
	if (!priv->port_mask)
		return -ENODEV;

	brcm_sata_phys_enable(priv);

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);
	hpriv->plat_data = priv;
	hpriv->flags = AHCI_HFLAG_WAKE_BEFORE_STOP;

	brcm_sata_alpm_init(hpriv);

	ret = ahci_platform_enable_resources(hpriv);
	if (ret)
		return ret;

	if (priv->quirks & BRCM_AHCI_QUIRK_NO_NCQ)
		hpriv->flags |= AHCI_HFLAG_NO_NCQ;
	hpriv->flags |= AHCI_HFLAG_NO_WRITE_TO_RO;

	ret = ahci_platform_init_host(pdev, hpriv, &ahci_brcm_port_info,
				      &ahci_platform_sht);
	if (ret)
		return ret;

	dev_info(dev, "Broadcom AHCI SATA3 registered\n");

	return 0;
}