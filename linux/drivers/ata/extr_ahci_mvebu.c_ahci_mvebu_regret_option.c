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
struct ahci_host_priv {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ AHCI_VENDOR_SPECIFIC_0_ADDR ; 
 scalar_t__ AHCI_VENDOR_SPECIFIC_0_DATA ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ahci_mvebu_regret_option(struct ahci_host_priv *hpriv)
{
	/*
	 * Enable the regret bit to allow the SATA unit to regret a
	 * request that didn't receive an acknowlegde and avoid a
	 * deadlock
	 */
	writel(0x4, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_ADDR);
	writel(0x80, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_DATA);
}