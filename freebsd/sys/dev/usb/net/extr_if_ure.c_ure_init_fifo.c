#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; } ;
struct ure_softc {int sc_flags; int sc_chip; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int URE_ADC_EN ; 
 int URE_CHIP_VER_5C00 ; 
 int URE_CHIP_VER_5C10 ; 
 int URE_CHIP_VER_5C20 ; 
 int URE_CKADSEL_L ; 
 int URE_CPCR_RX_VLAN ; 
 int URE_CTAP_SHORT_EN ; 
 int URE_EEE_CLKDIV_EN ; 
 int URE_EN_10M_BGOFF ; 
 int URE_EN_10M_PLLOFF ; 
 int URE_EN_EMI_L ; 
 int URE_FLAG_8152 ; 
 int URE_LINK_LIST_READY ; 
 int URE_MCU_BORW_EN ; 
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 int URE_NOW_IS_OOB ; 
 int /*<<< orphan*/  URE_OCP_ADC_CFG ; 
 int /*<<< orphan*/  URE_OCP_DOWN_SPEED ; 
 int /*<<< orphan*/  URE_OCP_EEE_CFG ; 
 int /*<<< orphan*/  URE_OCP_POWER_CFG ; 
 int /*<<< orphan*/  URE_OCP_SRAM_ADDR ; 
 int /*<<< orphan*/  URE_OCP_SRAM_DATA ; 
 int URE_PFM_PWM_SWITCH ; 
 int /*<<< orphan*/  URE_PLA_CPCR ; 
 int /*<<< orphan*/  URE_PLA_CR ; 
 int /*<<< orphan*/  URE_PLA_MISC_1 ; 
 int /*<<< orphan*/  URE_PLA_OOB_CTRL ; 
 int /*<<< orphan*/  URE_PLA_PHY_PWR ; 
 int /*<<< orphan*/  URE_PLA_RCR ; 
 int /*<<< orphan*/  URE_PLA_RXFIFO_CTRL0 ; 
 int /*<<< orphan*/  URE_PLA_RXFIFO_CTRL1 ; 
 int /*<<< orphan*/  URE_PLA_RXFIFO_CTRL2 ; 
 int /*<<< orphan*/  URE_PLA_SFF_STS_7 ; 
 int /*<<< orphan*/  URE_PLA_TCR0 ; 
 int /*<<< orphan*/  URE_PLA_TXFIFO_CTRL ; 
 int URE_RCR_ACPT_ALL ; 
 int URE_RE_INIT_LL ; 
 int URE_RXDY_GATED_EN ; 
 int URE_RXFIFO_THR1_NORMAL ; 
 int URE_RXFIFO_THR2_FULL ; 
 int URE_RXFIFO_THR2_HIGH ; 
 int URE_RXFIFO_THR3_FULL ; 
 int URE_RXFIFO_THR3_HIGH ; 
 int URE_SRAM_10M_AMP1 ; 
 int URE_SRAM_10M_AMP2 ; 
 int URE_SRAM_IMPEDANCE ; 
 int URE_SRAM_LPF_CFG ; 
 int URE_TCR0_AUTO_FIFO ; 
 int URE_TIMEOUT ; 
 int URE_TXFIFO_THR_NORMAL ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  uether_pause (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ure_disable_teredo (struct ure_softc*) ; 
 int ure_ocp_reg_read (struct ure_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_ocp_reg_write (struct ure_softc*,int /*<<< orphan*/ ,int) ; 
 int ure_read_1 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ure_read_2 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ure_read_4 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_reset (struct ure_softc*) ; 
 int /*<<< orphan*/  ure_write_1 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ure_write_2 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ure_write_4 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ure_init_fifo(struct ure_softc *sc)
{
	uint32_t rx_fifo1, rx_fifo2;
	int i;

	ure_write_2(sc, URE_PLA_MISC_1, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_MISC_1, URE_MCU_TYPE_PLA) |
	    URE_RXDY_GATED_EN);

	ure_disable_teredo(sc);

	ure_write_4(sc, URE_PLA_RCR, URE_MCU_TYPE_PLA,
	    ure_read_4(sc, URE_PLA_RCR, URE_MCU_TYPE_PLA) &
	    ~URE_RCR_ACPT_ALL);

	if (!(sc->sc_flags & URE_FLAG_8152)) {
		if (sc->sc_chip & (URE_CHIP_VER_5C00 | URE_CHIP_VER_5C10 |
		    URE_CHIP_VER_5C20)) {
				ure_ocp_reg_write(sc, URE_OCP_ADC_CFG,
				    URE_CKADSEL_L | URE_ADC_EN | URE_EN_EMI_L);
		}
		if (sc->sc_chip & URE_CHIP_VER_5C00) {
			ure_ocp_reg_write(sc, URE_OCP_EEE_CFG,
			    ure_ocp_reg_read(sc, URE_OCP_EEE_CFG) & 
			    ~URE_CTAP_SHORT_EN);
		}
		ure_ocp_reg_write(sc, URE_OCP_POWER_CFG,
		    ure_ocp_reg_read(sc, URE_OCP_POWER_CFG) |
		    URE_EEE_CLKDIV_EN);
		ure_ocp_reg_write(sc, URE_OCP_DOWN_SPEED,
		    ure_ocp_reg_read(sc, URE_OCP_DOWN_SPEED) |
		    URE_EN_10M_BGOFF);
		ure_ocp_reg_write(sc, URE_OCP_POWER_CFG,
		    ure_ocp_reg_read(sc, URE_OCP_POWER_CFG) |
		    URE_EN_10M_PLLOFF);
		ure_ocp_reg_write(sc, URE_OCP_SRAM_ADDR, URE_SRAM_IMPEDANCE);
		ure_ocp_reg_write(sc, URE_OCP_SRAM_DATA, 0x0b13);
		ure_write_2(sc, URE_PLA_PHY_PWR, URE_MCU_TYPE_PLA,
		    ure_read_2(sc, URE_PLA_PHY_PWR, URE_MCU_TYPE_PLA) |
		    URE_PFM_PWM_SWITCH);

		/* Enable LPF corner auto tune. */
		ure_ocp_reg_write(sc, URE_OCP_SRAM_ADDR, URE_SRAM_LPF_CFG);
		ure_ocp_reg_write(sc, URE_OCP_SRAM_DATA, 0xf70f);

		/* Adjust 10M amplitude. */
		ure_ocp_reg_write(sc, URE_OCP_SRAM_ADDR, URE_SRAM_10M_AMP1);
		ure_ocp_reg_write(sc, URE_OCP_SRAM_DATA, 0x00af);
		ure_ocp_reg_write(sc, URE_OCP_SRAM_ADDR, URE_SRAM_10M_AMP2);
		ure_ocp_reg_write(sc, URE_OCP_SRAM_DATA, 0x0208);
	}

	ure_reset(sc);

	ure_write_1(sc, URE_PLA_CR, URE_MCU_TYPE_PLA, 0);

	ure_write_1(sc, URE_PLA_OOB_CTRL, URE_MCU_TYPE_PLA,
	    ure_read_1(sc, URE_PLA_OOB_CTRL, URE_MCU_TYPE_PLA) &
	    ~URE_NOW_IS_OOB);

	ure_write_2(sc, URE_PLA_SFF_STS_7, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_SFF_STS_7, URE_MCU_TYPE_PLA) &
	    ~URE_MCU_BORW_EN);
	for (i = 0; i < URE_TIMEOUT; i++) {
		if (ure_read_1(sc, URE_PLA_OOB_CTRL, URE_MCU_TYPE_PLA) &
		    URE_LINK_LIST_READY)
			break;
		uether_pause(&sc->sc_ue, hz / 100);
	}
	if (i == URE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev,
		    "timeout waiting for OOB control\n");
	ure_write_2(sc, URE_PLA_SFF_STS_7, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_SFF_STS_7, URE_MCU_TYPE_PLA) |
	    URE_RE_INIT_LL);
	for (i = 0; i < URE_TIMEOUT; i++) {
		if (ure_read_1(sc, URE_PLA_OOB_CTRL, URE_MCU_TYPE_PLA) &
		    URE_LINK_LIST_READY)
			break;
		uether_pause(&sc->sc_ue, hz / 100);
	}
	if (i == URE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev,
		    "timeout waiting for OOB control\n");

	ure_write_2(sc, URE_PLA_CPCR, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_CPCR, URE_MCU_TYPE_PLA) &
	    ~URE_CPCR_RX_VLAN);
	ure_write_2(sc, URE_PLA_TCR0, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_TCR0, URE_MCU_TYPE_PLA) |
	    URE_TCR0_AUTO_FIFO);

	/* Configure Rx FIFO threshold. */
	ure_write_4(sc, URE_PLA_RXFIFO_CTRL0, URE_MCU_TYPE_PLA,
	    URE_RXFIFO_THR1_NORMAL);
	if (usbd_get_speed(sc->sc_ue.ue_udev) == USB_SPEED_FULL) {
		rx_fifo1 = URE_RXFIFO_THR2_FULL;
		rx_fifo2 = URE_RXFIFO_THR3_FULL;
	} else {
		rx_fifo1 = URE_RXFIFO_THR2_HIGH;
		rx_fifo2 = URE_RXFIFO_THR3_HIGH;
	}
	ure_write_4(sc, URE_PLA_RXFIFO_CTRL1, URE_MCU_TYPE_PLA, rx_fifo1);
	ure_write_4(sc, URE_PLA_RXFIFO_CTRL2, URE_MCU_TYPE_PLA, rx_fifo2);

	/* Configure Tx FIFO threshold. */
	ure_write_4(sc, URE_PLA_TXFIFO_CTRL, URE_MCU_TYPE_PLA,
	    URE_TXFIFO_THR_NORMAL);
}