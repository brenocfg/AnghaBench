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
struct tegra_ahci_sc {int dummy; } ;
struct sata_pad_calibration {int gen1_tx_amp; int gen1_tx_peak; int gen2_tx_amp; int gen2_tx_peak; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_SATA_CALIB ; 
 int FUSE_SATA_CALIB_MASK ; 
 scalar_t__ SATA_CONFIGURATION ; 
 int SATA_CONFIGURATION_EN_FPCI ; 
 scalar_t__ SATA_FPCI_BAR5 ; 
 int SATA_FPCI_BAR5_START_SHIFT ; 
 scalar_t__ SATA_INTR_MASK ; 
 int SATA_INTR_MASK_IP_INT_MASK ; 
 int SATA_RD4 (struct tegra_ahci_sc*,scalar_t__) ; 
 int /*<<< orphan*/  SATA_WR4 (struct tegra_ahci_sc*,scalar_t__,int) ; 
 scalar_t__ SCFG_OFFSET ; 
 scalar_t__ T_SATA0_BKDOOR_CC ; 
 scalar_t__ T_SATA0_CFG_1 ; 
 int T_SATA0_CFG_1_BUS_MASTER ; 
 int T_SATA0_CFG_1_IO_SPACE ; 
 int T_SATA0_CFG_1_MEMORY_SPACE ; 
 int T_SATA0_CFG_1_SERR ; 
 scalar_t__ T_SATA0_CFG_9 ; 
 int T_SATA0_CFG_9_BASE_ADDRESS_SHIFT ; 
 scalar_t__ T_SATA0_CFG_SATA ; 
 int T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL11 ; 
 int T_SATA0_CHX_PHY_CTRL11_GEN2_RX_EQ ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL1_GEN1 ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_MASK ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_MASK ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL1_GEN2 ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_MASK ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_SHIFT ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_MASK ; 
 int T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_SHIFT ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL2 ; 
 int T_SATA0_CHX_PHY_CTRL2_CDR_CNTL_GEN1 ; 
 scalar_t__ T_SATA0_INDEX ; 
 struct sata_pad_calibration* tegra124_pad_calibration ; 
 int tegra_fuse_read_4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_ahci_ctrl_init(struct tegra_ahci_sc *sc)
{
	uint32_t val;
	const struct sata_pad_calibration *calib;

	val = SATA_RD4(sc, SATA_CONFIGURATION);
	val |= SATA_CONFIGURATION_EN_FPCI;
	SATA_WR4(sc, SATA_CONFIGURATION, val);


	/* Pad calibration. */
	val = tegra_fuse_read_4(FUSE_SATA_CALIB);
	calib = tegra124_pad_calibration + (val & FUSE_SATA_CALIB_MASK);
	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_INDEX, 1);

	val = SATA_RD4(sc, SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN1);
	val &= ~(T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_MASK <<
	    T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT);
	val &= ~(T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_MASK <<
	    T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT);
	val |= calib->gen1_tx_amp << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_AMP_SHIFT;
	val |= calib->gen1_tx_peak << T_SATA0_CHX_PHY_CTRL1_GEN1_TX_PEAK_SHIFT;
	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN1, val);

	val = SATA_RD4(sc, SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN2);
	val &= ~(T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_MASK <<
	    T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_SHIFT);
	val &= ~(T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_MASK <<
	    T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_SHIFT);
	val |= calib->gen2_tx_amp << T_SATA0_CHX_PHY_CTRL1_GEN2_TX_AMP_SHIFT;
	val |= calib->gen2_tx_peak << T_SATA0_CHX_PHY_CTRL1_GEN2_TX_PEAK_SHIFT;
	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL1_GEN2, val);

	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL11,
	    T_SATA0_CHX_PHY_CTRL11_GEN2_RX_EQ);

	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL2,
	    T_SATA0_CHX_PHY_CTRL2_CDR_CNTL_GEN1);

	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_INDEX, 0);

	/* Set device ID. */
	val = SATA_RD4(sc, SCFG_OFFSET + T_SATA0_CFG_SATA);
	val |= T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN;
	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CFG_SATA, val);

	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_BKDOOR_CC, 0x01060100);

	val = SATA_RD4(sc, SCFG_OFFSET + T_SATA0_CFG_SATA);
	val &= ~T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN;
	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CFG_SATA, val);

	/* Enable IO & memory access, bus master mode */
	val = SATA_RD4(sc, SCFG_OFFSET + T_SATA0_CFG_1);
	val |= T_SATA0_CFG_1_IO_SPACE;
	val |= T_SATA0_CFG_1_MEMORY_SPACE;
	val |= T_SATA0_CFG_1_BUS_MASTER;
	val |= T_SATA0_CFG_1_SERR;
	SATA_WR4(sc, SCFG_OFFSET + T_SATA0_CFG_1, val);

	/* SATA MMIO. */
	SATA_WR4(sc, SATA_FPCI_BAR5, 0x10000 << SATA_FPCI_BAR5_START_SHIFT);
	/* AHCI bar */
	SATA_WR4(sc,  SCFG_OFFSET + T_SATA0_CFG_9,
	    0x08000 << T_SATA0_CFG_9_BASE_ADDRESS_SHIFT);

	/* Unmask  interrupts. */
	val = SATA_RD4(sc, SATA_INTR_MASK);
	val |= SATA_INTR_MASK_IP_INT_MASK;
	SATA_WR4(sc, SATA_INTR_MASK, val);

	return (0);
}