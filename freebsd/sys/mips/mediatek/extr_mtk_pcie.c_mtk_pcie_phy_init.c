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
struct mtk_pci_softc {int socid; scalar_t__ num_slots; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
#define  MTK_SOC_MT7620A 133 
#define  MTK_SOC_MT7621 132 
#define  MTK_SOC_MT7628 131 
#define  MTK_SOC_MT7688 130 
#define  MTK_SOC_RT3662 129 
#define  MTK_SOC_RT3883 128 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtk_pcie_phy_mt7620_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_phy_mt7621_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_phy_mt7628_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_phy_rt3883_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_phy_setup_slots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pcie_phy_init(device_t dev)
{
	struct mtk_pci_softc *sc;

	/* Get our softc */
	sc = device_get_softc(dev);

	/* We don't know how many slots we have yet */
	sc->num_slots = 0;

	/* Handle SoC specific PCIe init */
	switch (sc->socid) {
	case MTK_SOC_MT7628: /* Fallthrough */
	case MTK_SOC_MT7688:
		if (mtk_pcie_phy_mt7628_init(dev))
			return (ENXIO);
		break;
	case MTK_SOC_MT7621:
		if (mtk_pcie_phy_mt7621_init(dev))
			return (ENXIO);
		break;
	case MTK_SOC_MT7620A:
		if (mtk_pcie_phy_mt7620_init(dev))
			return (ENXIO);
		break;
	case MTK_SOC_RT3662: /* Fallthrough */
	case MTK_SOC_RT3883:
		if (mtk_pcie_phy_rt3883_init(dev))
			return (ENXIO);
		break;
	default:
		device_printf(dev, "unsupported device %x\n", sc->socid);
		return (ENXIO);
	}

	/*
	 * If we were successful so far go and set up the PCIe slots, so we
	 * may allocate mem/io/irq resources and enumerate busses later.
	 */
	mtk_pcie_phy_setup_slots(dev);

	return (0);
}