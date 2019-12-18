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
 int /*<<< orphan*/  ahci_platform_disable_phys (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_platform_disable_regulators (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

void ahci_platform_disable_resources(struct ahci_host_priv *hpriv)
{
	ahci_platform_disable_phys(hpriv);

	reset_control_assert(hpriv->rsts);

	ahci_platform_disable_clks(hpriv);

	ahci_platform_disable_regulators(hpriv);
}