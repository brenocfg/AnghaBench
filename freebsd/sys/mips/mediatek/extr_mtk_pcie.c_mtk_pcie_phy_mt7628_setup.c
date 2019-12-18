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
typedef  int uint32_t ;
struct mtk_pci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSCTL_SYSCFG ; 
 int /*<<< orphan*/  mtk_pcie_phy_set (struct mtk_pci_softc*,int,int,int,int) ; 
 int mtk_sysctl_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtk_pcie_phy_mt7628_setup(struct mtk_pci_softc *sc, uint32_t off)
{
	uint32_t xtal_sel;

	xtal_sel = mtk_sysctl_get(SYSCTL_SYSCFG) >> 6;
	xtal_sel &= 0x1;

	mtk_pcie_phy_set(sc, off + 0x400,  8, 1, 1);
	mtk_pcie_phy_set(sc, off + 0x400,  9, 2, 0);
	mtk_pcie_phy_set(sc, off + 0x000,  4, 1, 1);
	mtk_pcie_phy_set(sc, off + 0x000,  5, 1, 0);
	mtk_pcie_phy_set(sc, off + 0x4ac, 16, 3, 3);

	if (xtal_sel == 1) {
		mtk_pcie_phy_set(sc, off + 0x4bc, 24,  8, 0x7d);
		mtk_pcie_phy_set(sc, off + 0x490, 12,  4, 0x08);
		mtk_pcie_phy_set(sc, off + 0x490,  6,  2, 0x01);
		mtk_pcie_phy_set(sc, off + 0x4c0,  0, 32, 0x1f400000);
		mtk_pcie_phy_set(sc, off + 0x4a4,  0, 16, 0x013d);
		mtk_pcie_phy_set(sc, off + 0x4a8, 16, 16, 0x74);
		mtk_pcie_phy_set(sc, off + 0x4a8,  0, 16, 0x74);
	} else {
		mtk_pcie_phy_set(sc, off + 0x4bc, 24,  8, 0x64);
		mtk_pcie_phy_set(sc, off + 0x490, 12,  4, 0x0a);
		mtk_pcie_phy_set(sc, off + 0x490,  6,  2, 0x00);
		mtk_pcie_phy_set(sc, off + 0x4c0,  0, 32, 0x19000000);
		mtk_pcie_phy_set(sc, off + 0x4a4,  0, 16, 0x018d);
		mtk_pcie_phy_set(sc, off + 0x4a8, 16, 16, 0x4a);
		mtk_pcie_phy_set(sc, off + 0x4a8,  0, 16, 0x4a);
	}

	mtk_pcie_phy_set(sc, off + 0x498, 0, 8, 5);
	mtk_pcie_phy_set(sc, off + 0x000, 5, 1, 1);
	mtk_pcie_phy_set(sc, off + 0x000, 4, 1, 0);
}