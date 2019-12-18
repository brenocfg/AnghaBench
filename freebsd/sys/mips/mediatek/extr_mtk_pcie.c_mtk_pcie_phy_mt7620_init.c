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
 int LC_CKDRVHZ ; 
 int LC_CKDRVOHZ ; 
 int LC_CKDRVPD ; 
 int MT7620_PERST ; 
 int MT7620_PERST_GPIO_MODE ; 
 int MT7620_PKG_BGA ; 
 int /*<<< orphan*/  MT7620_PPLL_CFG0 ; 
 int /*<<< orphan*/  MT7620_PPLL_CFG1 ; 
 int /*<<< orphan*/  MT7620_PPLL_DRV ; 
 int /*<<< orphan*/  MTK_PCI_PCICFG ; 
 int /*<<< orphan*/  MTK_PCI_RESET ; 
 int /*<<< orphan*/  MT_CLR_SET32 (struct mtk_pci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PDRV_SW_SET ; 
 int PPLL_LOCKED ; 
 int PPLL_PD ; 
 int PPLL_SW_SET ; 
 int /*<<< orphan*/  SYSCTL_GPIOMODE ; 
 int /*<<< orphan*/  SYSCTL_REVID ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mtk_pcie_phy_mt7620_set (struct mtk_pci_softc*,int,int) ; 
 scalar_t__ mtk_pcie_phy_start (int /*<<< orphan*/ ) ; 
 scalar_t__ mtk_pcie_phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sysctl_clr_set (int /*<<< orphan*/ ,int,int) ; 
 int mtk_sysctl_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pcie_phy_mt7620_init(device_t dev)
{
	struct mtk_pci_softc *sc = device_get_softc(dev);

	/*
	 * The below sets the PCIe PHY to bypass the PCIe DLL and enables
	 * "elastic buffer control", whatever that may be...
	 */
	if (mtk_pcie_phy_mt7620_set(sc, 0x00, 0x80) ||
	    mtk_pcie_phy_mt7620_set(sc, 0x01, 0x04) ||
	    mtk_pcie_phy_mt7620_set(sc, 0x68, 0x84))
		return (ENXIO);

	/* Stop PCIe */
	if (mtk_pcie_phy_stop(dev))
		return (ENXIO);

	/* Restore PPLL to a sane state before going on */
	mtk_sysctl_clr_set(MT7620_PPLL_DRV, LC_CKDRVPD, PDRV_SW_SET);

	/* No PCIe on the MT7620N */
	if (!(mtk_sysctl_get(SYSCTL_REVID) & MT7620_PKG_BGA)) {
		device_printf(dev, "PCIe disabled for MT7620N\n");
		mtk_sysctl_clr_set(MT7620_PPLL_CFG0, 0, PPLL_SW_SET);
		mtk_sysctl_clr_set(MT7620_PPLL_CFG1, 0, PPLL_PD);
		return (ENXIO);
	}

	/* PCIe device reset pin is in normal mode */
	mtk_sysctl_clr_set(SYSCTL_GPIOMODE, MT7620_PERST_GPIO_MODE,
	    MT7620_PERST);

	/* Enable PCIe now */
	if (mtk_pcie_phy_start(dev))
		return (ENXIO);

	/* Give it a chance to sink in */
	DELAY(100000);

	/* If PLL is not locked - bail */
	if (!(mtk_sysctl_get(MT7620_PPLL_CFG1) & PPLL_LOCKED)) {
		device_printf(dev, "no PPLL not lock\n");
		mtk_pcie_phy_stop(dev);
		return (ENXIO);
	}

	/* Configure PCIe PLL */
	mtk_sysctl_clr_set(MT7620_PPLL_DRV, LC_CKDRVOHZ | LC_CKDRVHZ,
	    LC_CKDRVPD | PDRV_SW_SET);

	/* and give it a chance to settle */
	DELAY(100000);

	/* Deassert PCIe device reset */
	MT_CLR_SET32(sc, MTK_PCI_PCICFG, MTK_PCI_RESET, 0);

	/* MT7620 supports one PCIe slot */
	sc->num_slots = 1;

	return (0);
}