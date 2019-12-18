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
 scalar_t__ MT7620_MAX_RETRIES ; 
 int /*<<< orphan*/  MT7620_PCIE_PHY_CFG ; 
 int MT_READ32 (struct mtk_pci_softc*,int /*<<< orphan*/ ) ; 
 int PHY_BUSY ; 

__attribute__((used)) static int
mtk_pcie_phy_mt7620_wait_busy(struct mtk_pci_softc *sc)
{
	uint32_t reg_value, retry;

	reg_value = retry = 0;

	while (retry++ < MT7620_MAX_RETRIES) {
		reg_value = MT_READ32(sc, MT7620_PCIE_PHY_CFG);
		if (reg_value & PHY_BUSY)
			DELAY(100000);
		else
			break;
	}

	if (retry >= MT7620_MAX_RETRIES)
		return (ENXIO);

	return (0);
}