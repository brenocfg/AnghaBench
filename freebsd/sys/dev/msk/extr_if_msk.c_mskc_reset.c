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
typedef  int uint16_t ;
struct msk_stat_desc {int dummy; } ;
struct msk_softc {scalar_t__ msk_hw_id; int msk_bustype; int msk_num_port; scalar_t__ msk_hw_rev; scalar_t__ msk_pcixcap; scalar_t__ msk_expcap; int msk_stat_count; int /*<<< orphan*/  msk_stat_ring_paddr; int /*<<< orphan*/  msk_stat_map; int /*<<< orphan*/  msk_stat_tag; scalar_t__ msk_stat_cons; int /*<<< orphan*/  msk_stat_ring; int /*<<< orphan*/  msk_dev; int /*<<< orphan*/  msk_intrhwemask; int /*<<< orphan*/  msk_intrmask; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_HWE_IMSK ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B28_DPT_CTRL ; 
 int /*<<< orphan*/  B28_Y2_ASF_HCU_CCSR ; 
 int /*<<< orphan*/  B28_Y2_ASF_STAT_CMD ; 
 int /*<<< orphan*/  B28_Y2_CPU_WDOG ; 
 int /*<<< orphan*/  B2_I2C_IRQ ; 
 int /*<<< orphan*/  B2_TI_CTRL ; 
 int /*<<< orphan*/  B2_TST_CTRL1 ; 
 int /*<<< orphan*/  B3_RI_CTRL ; 
 int /*<<< orphan*/  B3_RI_RTO_R1 ; 
 int /*<<< orphan*/  B3_RI_RTO_R2 ; 
 int /*<<< orphan*/  B3_RI_RTO_XA1 ; 
 int /*<<< orphan*/  B3_RI_RTO_XA2 ; 
 int /*<<< orphan*/  B3_RI_RTO_XS1 ; 
 int /*<<< orphan*/  B3_RI_RTO_XS2 ; 
 int /*<<< orphan*/  B3_RI_WTO_R1 ; 
 int /*<<< orphan*/  B3_RI_WTO_R2 ; 
 int /*<<< orphan*/  B3_RI_WTO_XA1 ; 
 int /*<<< orphan*/  B3_RI_WTO_XA2 ; 
 int /*<<< orphan*/  B3_RI_WTO_XS1 ; 
 int /*<<< orphan*/  B3_RI_WTO_XS2 ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ CHIP_ID_YUKON_EC ; 
 scalar_t__ CHIP_ID_YUKON_EX ; 
 scalar_t__ CHIP_ID_YUKON_FE ; 
 scalar_t__ CHIP_ID_YUKON_OPT ; 
 scalar_t__ CHIP_ID_YUKON_SUPR ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 scalar_t__ CHIP_REV_YU_EC_A1 ; 
 scalar_t__ CHIP_REV_YU_SU_B0 ; 
 scalar_t__ CHIP_REV_YU_XL_A0 ; 
 int CSR_PCI_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_PCI_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int CSR_READ_2 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int CS_MRST_CLR ; 
 int CS_RST_CLR ; 
 int CS_RST_SET ; 
 int DPT_STOP ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMAC_TI_ST_CTRL ; 
 int GMC_BYP_MACSECRX_ON ; 
 int GMC_BYP_MACSECTX_ON ; 
 int GMC_BYP_RETR_ON ; 
 int GMC_F_LOOPB_OFF ; 
 int GMC_RST_CLR ; 
 int GMC_RST_SET ; 
 int GMT_ST_CLR_IRQ ; 
 int GMT_ST_STOP ; 
 int GPC_RST_CLR ; 
 int GPC_RST_SET ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int I2C_CLR_IRQ ; 
 int /*<<< orphan*/  MR_ADDR (int,int /*<<< orphan*/ ) ; 
 int MSK_ADDR_HI (int /*<<< orphan*/ ) ; 
 int MSK_ADDR_LO (int /*<<< orphan*/ ) ; 
#define  MSK_PCIX_BUS 130 
#define  MSK_PCI_BUS 129 
#define  MSK_PEX_BUS 128 
 int /*<<< orphan*/  MSK_PHY_POWERUP ; 
 int MSK_RI_TO_53 ; 
 int MSK_USECS (struct msk_softc*,int) ; 
 int PCIM_STATUS_MDPERR ; 
 int PCIM_STATUS_PERR ; 
 int PCIM_STATUS_RMABORT ; 
 int PCIM_STATUS_RTABORT ; 
 int PCIM_STATUS_SERR ; 
 scalar_t__ PCIR_CACHELNSZ ; 
 scalar_t__ PCIR_STATUS ; 
 int PCIXM_COMMAND_MAX_SPLITS ; 
 scalar_t__ PCIXR_COMMAND ; 
 int PCI_CLK_MACSEC_DIS ; 
 int PCI_CLS_OPT ; 
 scalar_t__ PCI_OUR_REG_1 ; 
 int /*<<< orphan*/  PCI_OUR_REG_3 ; 
 int PEX_RX_OV ; 
 int /*<<< orphan*/  PEX_UNC_ERR_STAT ; 
 int RI_RST_CLR ; 
 int RI_RST_SET ; 
 int SC_STAT_OP_ON ; 
 int SC_STAT_RST_CLR ; 
 int SC_STAT_RST_SET ; 
 int /*<<< orphan*/  SELECT_RAM_BUFFER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAT_CTRL ; 
 int /*<<< orphan*/  STAT_FIFO_ISR_WM ; 
 int /*<<< orphan*/  STAT_FIFO_WM ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_ISR_TIMER_INI ; 
 int /*<<< orphan*/  STAT_LAST_IDX ; 
 int /*<<< orphan*/  STAT_LEV_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_LIST_ADDR_HI ; 
 int /*<<< orphan*/  STAT_LIST_ADDR_LO ; 
 int /*<<< orphan*/  STAT_TX_IDX_TH ; 
 int /*<<< orphan*/  STAT_TX_TIMER_CTRL ; 
 int /*<<< orphan*/  STAT_TX_TIMER_INI ; 
 int ST_TXTH_IDX_MASK ; 
 int TIM_CLR_IRQ ; 
 int TIM_START ; 
 int TIM_STOP ; 
 int TST_CFG_WRITE_OFF ; 
 int TST_CFG_WRITE_ON ; 
 int Y2_ASF_DISABLE ; 
 int Y2_ASF_HCU_CCSR_AHB_RST ; 
 int Y2_ASF_HCU_CCSR_CPU_CLK_DIVIDE_MSK ; 
 int Y2_ASF_HCU_CCSR_CPU_RST_MODE ; 
 int Y2_ASF_HCU_CCSR_UC_STATE_MSK ; 
 int Y2_ASF_RESET ; 
 int /*<<< orphan*/  Y2_IS_HW_ERR ; 
 int /*<<< orphan*/  Y2_IS_PCI_EXP ; 
 int Y2_LED_STAT_ON ; 
 int /*<<< orphan*/  Y2_PEX_PHY_DATA ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msk_phy_power (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int pci_get_max_read_req (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_set_max_read_req (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
mskc_reset(struct msk_softc *sc)
{
	bus_addr_t addr;
	uint16_t status;
	uint32_t val;
	int i, initram;

	/* Disable ASF. */
	if (sc->msk_hw_id >= CHIP_ID_YUKON_XL &&
	    sc->msk_hw_id <= CHIP_ID_YUKON_SUPR) {
		if (sc->msk_hw_id == CHIP_ID_YUKON_EX ||
		    sc->msk_hw_id == CHIP_ID_YUKON_SUPR) {
			CSR_WRITE_4(sc, B28_Y2_CPU_WDOG, 0);
			status = CSR_READ_2(sc, B28_Y2_ASF_HCU_CCSR);
			/* Clear AHB bridge & microcontroller reset. */
			status &= ~(Y2_ASF_HCU_CCSR_AHB_RST |
			    Y2_ASF_HCU_CCSR_CPU_RST_MODE);
			/* Clear ASF microcontroller state. */
			status &= ~Y2_ASF_HCU_CCSR_UC_STATE_MSK;
			status &= ~Y2_ASF_HCU_CCSR_CPU_CLK_DIVIDE_MSK;
			CSR_WRITE_2(sc, B28_Y2_ASF_HCU_CCSR, status);
			CSR_WRITE_4(sc, B28_Y2_CPU_WDOG, 0);
		} else
			CSR_WRITE_1(sc, B28_Y2_ASF_STAT_CMD, Y2_ASF_RESET);
		CSR_WRITE_2(sc, B0_CTST, Y2_ASF_DISABLE);
		/*
		 * Since we disabled ASF, S/W reset is required for
		 * Power Management.
		 */
		CSR_WRITE_2(sc, B0_CTST, CS_RST_SET);
		CSR_WRITE_2(sc, B0_CTST, CS_RST_CLR);
	}

	/* Clear all error bits in the PCI status register. */
	status = pci_read_config(sc->msk_dev, PCIR_STATUS, 2);
	CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_ON);

	pci_write_config(sc->msk_dev, PCIR_STATUS, status |
	    PCIM_STATUS_PERR | PCIM_STATUS_SERR | PCIM_STATUS_RMABORT |
	    PCIM_STATUS_RTABORT | PCIM_STATUS_MDPERR, 2);
	CSR_WRITE_2(sc, B0_CTST, CS_MRST_CLR);

	switch (sc->msk_bustype) {
	case MSK_PEX_BUS:
		/* Clear all PEX errors. */
		CSR_PCI_WRITE_4(sc, PEX_UNC_ERR_STAT, 0xffffffff);
		val = CSR_PCI_READ_4(sc, PEX_UNC_ERR_STAT);
		if ((val & PEX_RX_OV) != 0) {
			sc->msk_intrmask &= ~Y2_IS_HW_ERR;
			sc->msk_intrhwemask &= ~Y2_IS_PCI_EXP;
		}
		break;
	case MSK_PCI_BUS:
	case MSK_PCIX_BUS:
		/* Set Cache Line Size to 2(8bytes) if configured to 0. */
		val = pci_read_config(sc->msk_dev, PCIR_CACHELNSZ, 1);
		if (val == 0)
			pci_write_config(sc->msk_dev, PCIR_CACHELNSZ, 2, 1);
		if (sc->msk_bustype == MSK_PCIX_BUS) {
			/* Set Cache Line Size opt. */
			val = pci_read_config(sc->msk_dev, PCI_OUR_REG_1, 4);
			val |= PCI_CLS_OPT;
			pci_write_config(sc->msk_dev, PCI_OUR_REG_1, val, 4);
		}
		break;
	}
	/* Set PHY power state. */
	msk_phy_power(sc, MSK_PHY_POWERUP);

	/* Reset GPHY/GMAC Control */
	for (i = 0; i < sc->msk_num_port; i++) {
		/* GPHY Control reset. */
		CSR_WRITE_1(sc, MR_ADDR(i, GPHY_CTRL), GPC_RST_SET);
		CSR_WRITE_1(sc, MR_ADDR(i, GPHY_CTRL), GPC_RST_CLR);
		/* GMAC Control reset. */
		CSR_WRITE_4(sc, MR_ADDR(i, GMAC_CTRL), GMC_RST_SET);
		CSR_WRITE_4(sc, MR_ADDR(i, GMAC_CTRL), GMC_RST_CLR);
		CSR_WRITE_4(sc, MR_ADDR(i, GMAC_CTRL), GMC_F_LOOPB_OFF);
		if (sc->msk_hw_id == CHIP_ID_YUKON_EX ||
		    sc->msk_hw_id == CHIP_ID_YUKON_SUPR)
			CSR_WRITE_4(sc, MR_ADDR(i, GMAC_CTRL),
			    GMC_BYP_MACSECRX_ON | GMC_BYP_MACSECTX_ON |
			    GMC_BYP_RETR_ON);
	}

	if (sc->msk_hw_id == CHIP_ID_YUKON_SUPR &&
	    sc->msk_hw_rev > CHIP_REV_YU_SU_B0)
		CSR_PCI_WRITE_4(sc, PCI_OUR_REG_3, PCI_CLK_MACSEC_DIS);
	if (sc->msk_hw_id == CHIP_ID_YUKON_OPT && sc->msk_hw_rev == 0) {
		/* Disable PCIe PHY powerdown(reg 0x80, bit7). */
		CSR_WRITE_4(sc, Y2_PEX_PHY_DATA, (0x0080 << 16) | 0x0080);
	}
	CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

	/* LED On. */
	CSR_WRITE_2(sc, B0_CTST, Y2_LED_STAT_ON);

	/* Clear TWSI IRQ. */
	CSR_WRITE_4(sc, B2_I2C_IRQ, I2C_CLR_IRQ);

	/* Turn off hardware timer. */
	CSR_WRITE_1(sc, B2_TI_CTRL, TIM_STOP);
	CSR_WRITE_1(sc, B2_TI_CTRL, TIM_CLR_IRQ);

	/* Turn off descriptor polling. */
	CSR_WRITE_1(sc, B28_DPT_CTRL, DPT_STOP);

	/* Turn off time stamps. */
	CSR_WRITE_1(sc, GMAC_TI_ST_CTRL, GMT_ST_STOP);
	CSR_WRITE_1(sc, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);

	initram = 0;
	if (sc->msk_hw_id == CHIP_ID_YUKON_XL ||
	    sc->msk_hw_id == CHIP_ID_YUKON_EC ||
	    sc->msk_hw_id == CHIP_ID_YUKON_FE)
		initram++;

	/* Configure timeout values. */
	for (i = 0; initram > 0 && i < sc->msk_num_port; i++) {
		CSR_WRITE_2(sc, SELECT_RAM_BUFFER(i, B3_RI_CTRL), RI_RST_SET);
		CSR_WRITE_2(sc, SELECT_RAM_BUFFER(i, B3_RI_CTRL), RI_RST_CLR);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_WTO_R1),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_WTO_XA1),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_WTO_XS1),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_RTO_R1),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_RTO_XA1),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_RTO_XS1),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_WTO_R2),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_WTO_XA2),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_WTO_XS2),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_RTO_R2),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_RTO_XA2),
		    MSK_RI_TO_53);
		CSR_WRITE_1(sc, SELECT_RAM_BUFFER(i, B3_RI_RTO_XS2),
		    MSK_RI_TO_53);
	}

	/* Disable all interrupts. */
	CSR_WRITE_4(sc, B0_HWE_IMSK, 0);
	CSR_READ_4(sc, B0_HWE_IMSK);
	CSR_WRITE_4(sc, B0_IMSK, 0);
	CSR_READ_4(sc, B0_IMSK);

        /*
         * On dual port PCI-X card, there is an problem where status
         * can be received out of order due to split transactions.
         */
	if (sc->msk_pcixcap != 0 && sc->msk_num_port > 1) {
		uint16_t pcix_cmd;

		pcix_cmd = pci_read_config(sc->msk_dev,
		    sc->msk_pcixcap + PCIXR_COMMAND, 2);
		/* Clear Max Outstanding Split Transactions. */
		pcix_cmd &= ~PCIXM_COMMAND_MAX_SPLITS;
		CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_write_config(sc->msk_dev,
		    sc->msk_pcixcap + PCIXR_COMMAND, pcix_cmd, 2);
		CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
        }
	if (sc->msk_expcap != 0) {
		/* Change Max. Read Request Size to 2048 bytes. */
		if (pci_get_max_read_req(sc->msk_dev) == 512)
			pci_set_max_read_req(sc->msk_dev, 2048);
	}

	/* Clear status list. */
	bzero(sc->msk_stat_ring,
	    sizeof(struct msk_stat_desc) * sc->msk_stat_count);
	sc->msk_stat_cons = 0;
	bus_dmamap_sync(sc->msk_stat_tag, sc->msk_stat_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	CSR_WRITE_4(sc, STAT_CTRL, SC_STAT_RST_SET);
	CSR_WRITE_4(sc, STAT_CTRL, SC_STAT_RST_CLR);
	/* Set the status list base address. */
	addr = sc->msk_stat_ring_paddr;
	CSR_WRITE_4(sc, STAT_LIST_ADDR_LO, MSK_ADDR_LO(addr));
	CSR_WRITE_4(sc, STAT_LIST_ADDR_HI, MSK_ADDR_HI(addr));
	/* Set the status list last index. */
	CSR_WRITE_2(sc, STAT_LAST_IDX, sc->msk_stat_count - 1);
	if (sc->msk_hw_id == CHIP_ID_YUKON_EC &&
	    sc->msk_hw_rev == CHIP_REV_YU_EC_A1) {
		/* WA for dev. #4.3 */
		CSR_WRITE_2(sc, STAT_TX_IDX_TH, ST_TXTH_IDX_MASK);
		/* WA for dev. #4.18 */
		CSR_WRITE_1(sc, STAT_FIFO_WM, 0x21);
		CSR_WRITE_1(sc, STAT_FIFO_ISR_WM, 0x07);
	} else {
		CSR_WRITE_2(sc, STAT_TX_IDX_TH, 0x0a);
		CSR_WRITE_1(sc, STAT_FIFO_WM, 0x10);
		if (sc->msk_hw_id == CHIP_ID_YUKON_XL &&
		    sc->msk_hw_rev == CHIP_REV_YU_XL_A0)
			CSR_WRITE_1(sc, STAT_FIFO_ISR_WM, 0x04);
		else
			CSR_WRITE_1(sc, STAT_FIFO_ISR_WM, 0x10);
		CSR_WRITE_4(sc, STAT_ISR_TIMER_INI, 0x0190);
	}
	/*
	 * Use default value for STAT_ISR_TIMER_INI, STAT_LEV_TIMER_INI.
	 */
	CSR_WRITE_4(sc, STAT_TX_TIMER_INI, MSK_USECS(sc, 1000));

	/* Enable status unit. */
	CSR_WRITE_4(sc, STAT_CTRL, SC_STAT_OP_ON);

	CSR_WRITE_1(sc, STAT_TX_TIMER_CTRL, TIM_START);
	CSR_WRITE_1(sc, STAT_LEV_TIMER_CTRL, TIM_START);
	CSR_WRITE_1(sc, STAT_ISR_TIMER_CTRL, TIM_START);
}