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
struct sdhci_pci_softc {int cfg_mode; int cfg_freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDHC_PCI_BASE_FREQ ; 
 int /*<<< orphan*/  SDHC_PCI_BASE_FREQ_KEY ; 
 int /*<<< orphan*/  SDHC_PCI_MODE ; 
 int /*<<< orphan*/  SDHC_PCI_MODE_KEY ; 
 struct sdhci_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
sdhci_restore_frequency(device_t dev)
{
	struct sdhci_pci_softc *sc = device_get_softc(dev);

	/* Restore mode. */
	pci_write_config(dev, SDHC_PCI_MODE_KEY, 0xfc, 1);
	pci_write_config(dev, SDHC_PCI_MODE, sc->cfg_mode, 1);
	pci_write_config(dev, SDHC_PCI_MODE_KEY, 0x00, 1);

	/* Restore frequency. */
	pci_write_config(dev, SDHC_PCI_BASE_FREQ_KEY, 0x01, 1);
	pci_write_config(dev, SDHC_PCI_BASE_FREQ, sc->cfg_freq, 1);
	pci_write_config(dev, SDHC_PCI_BASE_FREQ_KEY, 0x00, 1);
}