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
struct ahci_host_priv {int flags; int /*<<< orphan*/  mmio; int /*<<< orphan*/  start_engine; } ;

/* Variables and functions */
 int AHCI_HFLAG_32BIT_ONLY ; 
 int AHCI_HFLAG_NO_MSI ; 
 int AHCI_HFLAG_NO_PMP ; 
 int AHCI_HFLAG_YES_NCQ ; 
 int /*<<< orphan*/  AHCI_PLATFORM_GET_RESETS ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 int ahci_sunxi_phy_init (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_sunxi_port_info ; 
 int /*<<< orphan*/  ahci_sunxi_start_engine ; 
 int /*<<< orphan*/  enable_pmp ; 

__attribute__((used)) static int ahci_sunxi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ahci_host_priv *hpriv;
	int rc;

	hpriv = ahci_platform_get_resources(pdev, AHCI_PLATFORM_GET_RESETS);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	hpriv->start_engine = ahci_sunxi_start_engine;

	rc = ahci_platform_enable_resources(hpriv);
	if (rc)
		return rc;

	rc = ahci_sunxi_phy_init(dev, hpriv->mmio);
	if (rc)
		goto disable_resources;

	hpriv->flags = AHCI_HFLAG_32BIT_ONLY | AHCI_HFLAG_NO_MSI |
		       AHCI_HFLAG_YES_NCQ;

	/*
	 * The sunxi sata controller seems to be unable to successfully do a
	 * soft reset if no pmp is attached, so disable pmp use unless
	 * requested, otherwise directly attached disks do not work.
	 */
	if (!enable_pmp)
		hpriv->flags |= AHCI_HFLAG_NO_PMP;

	rc = ahci_platform_init_host(pdev, hpriv, &ahci_sunxi_port_info,
				     &ahci_platform_sht);
	if (rc)
		goto disable_resources;

	return 0;

disable_resources:
	ahci_platform_disable_resources(hpriv);
	return rc;
}