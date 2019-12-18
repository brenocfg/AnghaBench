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

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_PCI_WIN0_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN1_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN2_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN3_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN4_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN5_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN6_OFFS ; 
 int /*<<< orphan*/  AR71XX_PCI_WIN7_OFFS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ath79_ddr_pci_win_base ; 

void ath79_ddr_set_pci_windows(void)
{
	BUG_ON(!ath79_ddr_pci_win_base);

	__raw_writel(AR71XX_PCI_WIN0_OFFS, ath79_ddr_pci_win_base + 0x0);
	__raw_writel(AR71XX_PCI_WIN1_OFFS, ath79_ddr_pci_win_base + 0x4);
	__raw_writel(AR71XX_PCI_WIN2_OFFS, ath79_ddr_pci_win_base + 0x8);
	__raw_writel(AR71XX_PCI_WIN3_OFFS, ath79_ddr_pci_win_base + 0xc);
	__raw_writel(AR71XX_PCI_WIN4_OFFS, ath79_ddr_pci_win_base + 0x10);
	__raw_writel(AR71XX_PCI_WIN5_OFFS, ath79_ddr_pci_win_base + 0x14);
	__raw_writel(AR71XX_PCI_WIN6_OFFS, ath79_ddr_pci_win_base + 0x18);
	__raw_writel(AR71XX_PCI_WIN7_OFFS, ath79_ddr_pci_win_base + 0x1c);
}