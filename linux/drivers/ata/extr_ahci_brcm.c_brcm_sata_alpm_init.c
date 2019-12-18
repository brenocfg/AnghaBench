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
typedef  int u32 ;
struct brcm_ahci_priv {int port_mask; } ;
struct ahci_host_priv {scalar_t__ mmio; int /*<<< orphan*/  flags; struct brcm_ahci_priv* plat_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_HFLAG_YES_ALPM ; 
 int BIT (int) ; 
 scalar_t__ HOST_CAP ; 
 int HOST_CAP_ALPM ; 
 int SATA_FIRST_PORT_CTRL ; 
 scalar_t__ SATA_NEXT_PORT_CTRL_OFFSET ; 
 scalar_t__ SATA_PORT_PCTRL6 (int) ; 
 int SATA_TOP_MAX_PHYS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void brcm_sata_alpm_init(struct ahci_host_priv *hpriv)
{
	struct brcm_ahci_priv *priv = hpriv->plat_data;
	u32 port_ctrl, host_caps;
	int i;

	/* Enable support for ALPM */
	host_caps = readl(hpriv->mmio + HOST_CAP);
	if (!(host_caps & HOST_CAP_ALPM))
		hpriv->flags |= AHCI_HFLAG_YES_ALPM;

	/*
	 * Adjust timeout to allow PLL sufficient time to lock while waking
	 * up from slumber mode.
	 */
	for (i = 0, port_ctrl = SATA_FIRST_PORT_CTRL;
	     i < SATA_TOP_MAX_PHYS;
	     i++, port_ctrl += SATA_NEXT_PORT_CTRL_OFFSET) {
		if (priv->port_mask & BIT(i))
			writel(0xff1003fc,
			       hpriv->mmio + SATA_PORT_PCTRL6(port_ctrl));
	}
}