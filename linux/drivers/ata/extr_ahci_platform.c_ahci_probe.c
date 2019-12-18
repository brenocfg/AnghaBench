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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct ata_port_info {int dummy; } ;
struct ahci_host_priv {int flags; int /*<<< orphan*/  force_port_map; } ;

/* Variables and functions */
 int AHCI_HFLAG_NO_FBS ; 
 int AHCI_HFLAG_NO_NCQ ; 
 int /*<<< orphan*/  AHCI_PLATFORM_GET_RESETS ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 struct ata_port_info* acpi_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,struct ata_port_info const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 struct ata_port_info ahci_port_info ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ahci_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ahci_host_priv *hpriv;
	const struct ata_port_info *port;
	int rc;

	hpriv = ahci_platform_get_resources(pdev,
					    AHCI_PLATFORM_GET_RESETS);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	rc = ahci_platform_enable_resources(hpriv);
	if (rc)
		return rc;

	of_property_read_u32(dev->of_node,
			     "ports-implemented", &hpriv->force_port_map);

	if (of_device_is_compatible(dev->of_node, "hisilicon,hisi-ahci"))
		hpriv->flags |= AHCI_HFLAG_NO_FBS | AHCI_HFLAG_NO_NCQ;

	port = acpi_device_get_match_data(dev);
	if (!port)
		port = &ahci_port_info;

	rc = ahci_platform_init_host(pdev, hpriv, port,
				     &ahci_platform_sht);
	if (rc)
		goto disable_resources;

	return 0;
disable_resources:
	ahci_platform_disable_resources(hpriv);
	return rc;
}