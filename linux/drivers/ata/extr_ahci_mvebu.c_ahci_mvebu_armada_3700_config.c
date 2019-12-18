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
typedef  int /*<<< orphan*/  u32 ;
struct ahci_host_priv {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ AHCI_VENDOR_SPECIFIC_0_ADDR ; 
 scalar_t__ AHCI_VENDOR_SPECIFIC_0_DATA ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ahci_mvebu_armada_3700_config(struct ahci_host_priv *hpriv)
{
	u32 reg;

	writel(0, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_ADDR);

	reg = readl(hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_DATA);
	reg |= BIT(6);
	writel(reg, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_DATA);

	return 0;
}