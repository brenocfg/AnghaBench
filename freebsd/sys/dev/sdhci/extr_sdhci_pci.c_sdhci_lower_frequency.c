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
struct sdhci_pci_softc {void* cfg_freq; void* cfg_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDHC_PCI_BASE_FREQ ; 
 int /*<<< orphan*/  SDHC_PCI_BASE_FREQ_KEY ; 
 int /*<<< orphan*/  SDHC_PCI_MODE ; 
 int /*<<< orphan*/  SDHC_PCI_MODE_KEY ; 
 int SDHC_PCI_MODE_SD20 ; 
 struct sdhci_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
sdhci_lower_frequency(device_t dev)
{
	struct sdhci_pci_softc *sc = device_get_softc(dev);

	/*
	 * Enable SD2.0 mode.
	 * NB: for RICOH R5CE823, this changes the PCI device ID to 0xe822.
	 */
	pci_write_config(dev, SDHC_PCI_MODE_KEY, 0xfc, 1);
	sc->cfg_mode = pci_read_config(dev, SDHC_PCI_MODE, 1);
	pci_write_config(dev, SDHC_PCI_MODE, SDHC_PCI_MODE_SD20, 1);
	pci_write_config(dev, SDHC_PCI_MODE_KEY, 0x00, 1);

	/*
	 * Some SD/MMC cards don't work with the default base
	 * clock frequency of 200 MHz.  Lower it to 50 MHz.
	 */
	pci_write_config(dev, SDHC_PCI_BASE_FREQ_KEY, 0x01, 1);
	sc->cfg_freq = pci_read_config(dev, SDHC_PCI_BASE_FREQ, 1);
	pci_write_config(dev, SDHC_PCI_BASE_FREQ, 50, 1);
	pci_write_config(dev, SDHC_PCI_BASE_FREQ_KEY, 0x00, 1);
}