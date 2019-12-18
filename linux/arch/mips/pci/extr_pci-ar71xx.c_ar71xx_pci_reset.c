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
 int AR71XX_RESET_PCI_BUS ; 
 int AR71XX_RESET_PCI_CORE ; 
 int /*<<< orphan*/  ath79_ddr_set_pci_windows () ; 
 int /*<<< orphan*/  ath79_device_reset_clear (int) ; 
 int /*<<< orphan*/  ath79_device_reset_set (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void ar71xx_pci_reset(void)
{
	ath79_device_reset_set(AR71XX_RESET_PCI_BUS | AR71XX_RESET_PCI_CORE);
	mdelay(100);

	ath79_device_reset_clear(AR71XX_RESET_PCI_BUS | AR71XX_RESET_PCI_CORE);
	mdelay(100);

	ath79_ddr_set_pci_windows();
	mdelay(100);
}