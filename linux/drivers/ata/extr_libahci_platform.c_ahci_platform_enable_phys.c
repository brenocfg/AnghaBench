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
struct ahci_host_priv {int nports; int /*<<< orphan*/ * phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MODE_SATA ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int phy_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahci_platform_enable_phys(struct ahci_host_priv *hpriv)
{
	int rc, i;

	for (i = 0; i < hpriv->nports; i++) {
		rc = phy_init(hpriv->phys[i]);
		if (rc)
			goto disable_phys;

		rc = phy_set_mode(hpriv->phys[i], PHY_MODE_SATA);
		if (rc) {
			phy_exit(hpriv->phys[i]);
			goto disable_phys;
		}

		rc = phy_power_on(hpriv->phys[i]);
		if (rc) {
			phy_exit(hpriv->phys[i]);
			goto disable_phys;
		}
	}

	return 0;

disable_phys:
	while (--i >= 0) {
		phy_power_off(hpriv->phys[i]);
		phy_exit(hpriv->phys[i]);
	}
	return rc;
}