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
struct ahci_host_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int ahci_dm816_phy_init (struct ahci_host_priv*,struct device*) ; 
 int /*<<< orphan*/  ahci_dm816_platform_sht ; 
 int /*<<< orphan*/  ahci_dm816_port_info ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ahci_dm816_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ahci_host_priv *hpriv;
	int rc;

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	rc = ahci_platform_enable_resources(hpriv);
	if (rc)
		return rc;

	rc = ahci_dm816_phy_init(hpriv, dev);
	if (rc)
		goto disable_resources;

	rc = ahci_platform_init_host(pdev, hpriv,
				     &ahci_dm816_port_info,
				     &ahci_dm816_platform_sht);
	if (rc)
		goto disable_resources;

	return 0;

disable_resources:
	ahci_platform_disable_resources(hpriv);

	return rc;
}