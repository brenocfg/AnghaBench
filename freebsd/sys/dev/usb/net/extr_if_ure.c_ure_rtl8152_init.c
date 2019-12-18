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
struct ure_softc {int sc_chip; int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int URE_CHIP_VER_4C00 ; 
 int URE_D3_CLK_GATED_EN ; 
 int URE_DIS_SDSAVE ; 
 int URE_ENPDNPS ; 
 int URE_GPHY_STS_MSK ; 
 int URE_LED_MODE_MASK ; 
 int URE_LINKENA ; 
 int URE_MCU_CLK_RATIO ; 
 int URE_MCU_CLK_RATIO_MASK ; 
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 int /*<<< orphan*/  URE_MCU_TYPE_USB ; 
 int /*<<< orphan*/  URE_OCP_ALDPS_CONFIG ; 
 int URE_PFM_PWM_SWITCH ; 
 int /*<<< orphan*/  URE_PLA_GPHY_INTR_IMR ; 
 int /*<<< orphan*/  URE_PLA_LED_FEATURE ; 
 int /*<<< orphan*/  URE_PLA_MAC_PWR_CTRL ; 
 int /*<<< orphan*/  URE_PLA_PHY_PWR ; 
 int URE_POWER_CUT ; 
 int URE_RESUME_INDICATE ; 
 int URE_RX_AGG_DISABLE ; 
 int URE_RX_THR_HIGH ; 
 int URE_SPDWN_LINKCHG_MSK ; 
 int URE_SPDWN_RXDV_MSK ; 
 int URE_SPEED_DOWN_MSK ; 
 int URE_TEST_MODE_DISABLE ; 
 int URE_TX_10M_IDLE_EN ; 
 int /*<<< orphan*/  URE_TX_AGG_MAX_THRESHOLD ; 
 int URE_TX_SIZE_ADJUST1 ; 
 int /*<<< orphan*/  URE_USB_PM_CTRL_STATUS ; 
 int /*<<< orphan*/  URE_USB_RX_BUF_TH ; 
 int /*<<< orphan*/  URE_USB_TX_AGG ; 
 int /*<<< orphan*/  URE_USB_TX_DMA ; 
 int /*<<< orphan*/  URE_USB_UPS_CTRL ; 
 int /*<<< orphan*/  URE_USB_USB_CTRL ; 
 int hz ; 
 int /*<<< orphan*/  uether_pause (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ure_init_fifo (struct ure_softc*) ; 
 int /*<<< orphan*/  ure_ocp_reg_write (struct ure_softc*,int /*<<< orphan*/ ,int) ; 
 int ure_read_2 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ure_read_4 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_write_1 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_write_2 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ure_write_4 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ure_rtl8152_init(struct ure_softc *sc)
{
	uint32_t pwrctrl;

	/* Disable ALDPS. */
	ure_ocp_reg_write(sc, URE_OCP_ALDPS_CONFIG, URE_ENPDNPS | URE_LINKENA |
	    URE_DIS_SDSAVE);
	uether_pause(&sc->sc_ue, hz / 50);

	if (sc->sc_chip & URE_CHIP_VER_4C00) {
		ure_write_2(sc, URE_PLA_LED_FEATURE, URE_MCU_TYPE_PLA,
		    ure_read_2(sc, URE_PLA_LED_FEATURE, URE_MCU_TYPE_PLA) &
		    ~URE_LED_MODE_MASK);
	}

	ure_write_2(sc, URE_USB_UPS_CTRL, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_UPS_CTRL, URE_MCU_TYPE_USB) &
	    ~URE_POWER_CUT);
	ure_write_2(sc, URE_USB_PM_CTRL_STATUS, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_PM_CTRL_STATUS, URE_MCU_TYPE_USB) &
	    ~URE_RESUME_INDICATE);

	ure_write_2(sc, URE_PLA_PHY_PWR, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_PHY_PWR, URE_MCU_TYPE_PLA) |
	    URE_TX_10M_IDLE_EN | URE_PFM_PWM_SWITCH);
	pwrctrl = ure_read_4(sc, URE_PLA_MAC_PWR_CTRL, URE_MCU_TYPE_PLA);
	pwrctrl &= ~URE_MCU_CLK_RATIO_MASK;
	pwrctrl |= URE_MCU_CLK_RATIO | URE_D3_CLK_GATED_EN;
	ure_write_4(sc, URE_PLA_MAC_PWR_CTRL, URE_MCU_TYPE_PLA, pwrctrl);
	ure_write_2(sc, URE_PLA_GPHY_INTR_IMR, URE_MCU_TYPE_PLA,
	    URE_GPHY_STS_MSK | URE_SPEED_DOWN_MSK | URE_SPDWN_RXDV_MSK |
	    URE_SPDWN_LINKCHG_MSK);

	/* Disable Rx aggregation. */
	ure_write_2(sc, URE_USB_USB_CTRL, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_USB_CTRL, URE_MCU_TYPE_USB) |
	    URE_RX_AGG_DISABLE);

        /* Disable ALDPS. */
	ure_ocp_reg_write(sc, URE_OCP_ALDPS_CONFIG, URE_ENPDNPS | URE_LINKENA |
	    URE_DIS_SDSAVE);
	uether_pause(&sc->sc_ue, hz / 50);

	ure_init_fifo(sc);

	ure_write_1(sc, URE_USB_TX_AGG, URE_MCU_TYPE_USB,
	    URE_TX_AGG_MAX_THRESHOLD);
	ure_write_4(sc, URE_USB_RX_BUF_TH, URE_MCU_TYPE_USB, URE_RX_THR_HIGH);
	ure_write_4(sc, URE_USB_TX_DMA, URE_MCU_TYPE_USB,
	    URE_TEST_MODE_DISABLE | URE_TX_SIZE_ADJUST1);
}