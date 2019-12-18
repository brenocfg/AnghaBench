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
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MT7620_PCIE_PHY_CFG ; 
 int /*<<< orphan*/  MT_WRITE32 (struct mtk_pci_softc*,int /*<<< orphan*/ ,int) ; 
 int PHY_ADDR_OFFSET ; 
 int PHY_MODE_WRITE ; 
 scalar_t__ mtk_pcie_phy_mt7620_wait_busy (struct mtk_pci_softc*) ; 

__attribute__((used)) static int
mtk_pcie_phy_mt7620_set(struct mtk_pci_softc *sc, uint32_t reg,
    uint32_t val)
{
	uint32_t reg_val;

	if (mtk_pcie_phy_mt7620_wait_busy(sc))
		return (ENXIO);

	reg_val = PHY_MODE_WRITE | ((reg & 0xff) << PHY_ADDR_OFFSET) |
	    (val & 0xff);
	MT_WRITE32(sc, MT7620_PCIE_PHY_CFG, reg_val);
	DELAY(1000);

	if (mtk_pcie_phy_mt7620_wait_busy(sc))
		return (ENXIO);

	return (0);
}