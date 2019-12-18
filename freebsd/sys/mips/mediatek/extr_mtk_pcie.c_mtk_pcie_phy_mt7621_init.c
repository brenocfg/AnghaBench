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
 int /*<<< orphan*/  MT7621_GPIO_CTRL0 ; 
 int /*<<< orphan*/  MT7621_GPIO_DATA0 ; 
 int /*<<< orphan*/  MT7621_PCIE_RST ; 
 int MT7621_PERST_GPIO ; 
 int MT7621_PERST_GPIO_MODE ; 
 int MT7621_UARTL3_GPIO ; 
 int MT7621_UARTL3_GPIO_MODE ; 
 int /*<<< orphan*/  SYSCTL_GPIOMODE ; 
 int SYSCTL_MT7621_REV_E ; 
 int /*<<< orphan*/  SYSCTL_REVID ; 
 int SYSCTL_REVID_MASK ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_gpio_clr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_phy_mt7621_bypass_pipe_rst (struct mtk_pci_softc*,int) ; 
 int /*<<< orphan*/  mtk_pcie_phy_mt7621_setup_ssc (struct mtk_pci_softc*,int) ; 
 scalar_t__ mtk_pcie_phy_start (int /*<<< orphan*/ ) ; 
 scalar_t__ mtk_pcie_phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sysctl_clr_set (int /*<<< orphan*/ ,int,int) ; 
 int mtk_sysctl_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pcie_phy_mt7621_init(device_t dev)
{
	struct mtk_pci_softc *sc = device_get_softc(dev);

	/* First off, stop the PHY */
	if (mtk_pcie_phy_stop(dev))
		return (ENXIO);

	/* PCIe resets are GPIO pins */
	mtk_sysctl_clr_set(SYSCTL_GPIOMODE, MT7621_PERST_GPIO_MODE |
	    MT7621_UARTL3_GPIO_MODE, MT7621_PERST_GPIO | MT7621_UARTL3_GPIO);

	/* Set GPIO pins as outputs */
	mtk_gpio_clr_set(MT7621_GPIO_CTRL0, 0, MT7621_PCIE_RST);

	/* Assert resets to PCIe devices */
	mtk_gpio_clr_set(MT7621_GPIO_DATA0, MT7621_PCIE_RST, 0);

	/* Give everything a chance to sink in */
	DELAY(100000);

	/* Now start the PHY again */
	if (mtk_pcie_phy_start(dev))
		return (ENXIO);

	/* Wait for things to settle */
	DELAY(100000);

	/* Only apply below to REV-E hardware */
	if ((mtk_sysctl_get(SYSCTL_REVID) & SYSCTL_REVID_MASK) == 
	    SYSCTL_MT7621_REV_E)
		mtk_pcie_phy_mt7621_bypass_pipe_rst(sc, 0x9000);

	/* Setup PCIe ports 0 and 1 */
	mtk_pcie_phy_mt7621_setup_ssc(sc, 0x9000);
	/* Setup PCIe port 2 */
	mtk_pcie_phy_mt7621_setup_ssc(sc, 0xa000);

	/* Deassert resets to PCIe devices */
	mtk_gpio_clr_set(MT7621_GPIO_DATA0, 0, MT7621_PCIE_RST);

	/* Set number of slots supported */
	sc->num_slots = 3;

	/* Give it a chance to sink in */
	DELAY(100000);

	return (0);
}