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
struct mtk_pci_softc {int num_slots; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MT7628_PERST ; 
 int /*<<< orphan*/  MT7628_PERST_GPIO_MODE ; 
 int /*<<< orphan*/  MTK_PCI_PCICFG ; 
 int /*<<< orphan*/  MTK_PCI_RESET ; 
 int /*<<< orphan*/  MT_CLR_SET32 (struct mtk_pci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_GPIOMODE ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_phy_mt7628_setup (struct mtk_pci_softc*,int) ; 
 scalar_t__ mtk_pcie_phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sysctl_clr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pcie_phy_mt7628_init(device_t dev)
{
	struct mtk_pci_softc *sc = device_get_softc(dev);

	/* Set PCIe reset to normal mode */
	mtk_sysctl_clr_set(SYSCTL_GPIOMODE, MT7628_PERST_GPIO_MODE,
	    MT7628_PERST);

	/* Start the PHY */
	if (mtk_pcie_phy_start(dev))
		return (ENXIO);

	/* Give it a chance to sink in */
	DELAY(100000);

	/* Setup the PHY */
	mtk_pcie_phy_mt7628_setup(sc, 0x9000);

	/* Deassert PCIe device reset */
	MT_CLR_SET32(sc, MTK_PCI_PCICFG, MTK_PCI_RESET, 0);

	/* Set number of slots supported */
	sc->num_slots = 1;

	return (0);
}