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
struct ahci_host_priv {int /*<<< orphan*/  rsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahci_platform_disable_clks (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_platform_disable_regulators (struct ahci_host_priv*) ; 
 int ahci_platform_enable_clks (struct ahci_host_priv*) ; 
 int ahci_platform_enable_phys (struct ahci_host_priv*) ; 
 int ahci_platform_enable_regulators (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

int ahci_platform_enable_resources(struct ahci_host_priv *hpriv)
{
	int rc;

	rc = ahci_platform_enable_regulators(hpriv);
	if (rc)
		return rc;

	rc = ahci_platform_enable_clks(hpriv);
	if (rc)
		goto disable_regulator;

	rc = reset_control_deassert(hpriv->rsts);
	if (rc)
		goto disable_clks;

	rc = ahci_platform_enable_phys(hpriv);
	if (rc)
		goto disable_resets;

	return 0;

disable_resets:
	reset_control_assert(hpriv->rsts);

disable_clks:
	ahci_platform_disable_clks(hpriv);

disable_regulator:
	ahci_platform_disable_regulators(hpriv);

	return rc;
}