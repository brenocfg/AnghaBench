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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u1u2 ;
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; } ;
struct ure_softc {int sc_chip; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int URE_ALDPS_SPDWN_RATIO ; 
 int URE_AUTOLOAD_DONE ; 
 int URE_BYTE_EN_SIX_BYTES ; 
 int URE_CHIP_VER_5C00 ; 
 int URE_CHIP_VER_5C10 ; 
 int URE_CHIP_VER_5C20 ; 
 int URE_CHIP_VER_5C30 ; 
 int URE_DYNAMIC_BURST ; 
 int URE_ECM_ALDPS ; 
 int URE_EEE_SPDWN_EN ; 
 int URE_EEE_SPDWN_RATIO ; 
 int URE_EN_ALDPS ; 
 int URE_EP4_FULL_FC ; 
 int URE_FIFO_EMPTY_1FB ; 
 int URE_L1_SPDWN_EN ; 
 int URE_LED_MODE_MASK ; 
 int URE_LPM_TIMER_500MS ; 
 int URE_LPM_TIMER_500US ; 
 int URE_MCU_TYPE_PLA ; 
 int URE_MCU_TYPE_USB ; 
 int /*<<< orphan*/  URE_OCP_PHY_STATUS ; 
 int /*<<< orphan*/  URE_OCP_POWER_CFG ; 
 int URE_PCUT_STATUS ; 
 int URE_PHASE2_EN ; 
 int URE_PHY_STAT_LAN_ON ; 
 int URE_PHY_STAT_MASK ; 
 int URE_PHY_STAT_PWRDN ; 
 int URE_PKT_AVAIL_SPDWN_EN ; 
 int /*<<< orphan*/  URE_PLA_BOOT_CTRL ; 
 int /*<<< orphan*/  URE_PLA_DMY_REG0 ; 
 int /*<<< orphan*/  URE_PLA_LED_FEATURE ; 
 int /*<<< orphan*/  URE_PLA_MAC_PWR_CTRL ; 
 int /*<<< orphan*/  URE_PLA_MAC_PWR_CTRL2 ; 
 int /*<<< orphan*/  URE_PLA_MAC_PWR_CTRL3 ; 
 int /*<<< orphan*/  URE_PLA_MAC_PWR_CTRL4 ; 
 int URE_PWD_DN_SCALE (int) ; 
 int URE_PWD_DN_SCALE_MASK ; 
 int URE_PWRSAVE_SPDWN_EN ; 
 int URE_PWR_EN ; 
 int URE_ROK_EXIT_LPM ; 
 int URE_RXDV_SPDWN_EN ; 
 int URE_RX_AGG_DISABLE ; 
 int URE_SEL_RXIDLE ; 
 int URE_SEN_VAL_MASK ; 
 int URE_SEN_VAL_NORMAL ; 
 int URE_SUSPEND_SPDWN_EN ; 
 int URE_TIMEOUT ; 
 int URE_TIMER11_EN ; 
 int URE_TP1000_SPDWN_EN ; 
 int URE_TP100_SPDWN_EN ; 
 int URE_TP500_SPDWN_EN ; 
 int URE_TX10MIDLE_EN ; 
 int URE_U1U2_SPDWN_EN ; 
 int URE_U2P3_ENABLE ; 
 int URE_USB2PHY_L1 ; 
 int URE_USB2PHY_SUSPEND ; 
 int /*<<< orphan*/  URE_USB_AFE_CTRL2 ; 
 int /*<<< orphan*/  URE_USB_BURST_SIZE ; 
 int /*<<< orphan*/  URE_USB_CONNECT_TIMER ; 
 int /*<<< orphan*/  URE_USB_CSR_DUMMY1 ; 
 int /*<<< orphan*/  URE_USB_CSR_DUMMY2 ; 
 int /*<<< orphan*/  URE_USB_LPM_CTRL ; 
 int /*<<< orphan*/  URE_USB_MISC_0 ; 
 int /*<<< orphan*/  URE_USB_POWER_CUT ; 
 int /*<<< orphan*/  URE_USB_SSPHYLINK2 ; 
 int /*<<< orphan*/  URE_USB_TOLERANCE ; 
 int /*<<< orphan*/  URE_USB_U2P3_CTRL ; 
 int /*<<< orphan*/  URE_USB_USB2PHY ; 
 int /*<<< orphan*/  URE_USB_USB_CTRL ; 
 int /*<<< orphan*/  URE_USB_WDT11_CTRL ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uether_pause (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ure_init_fifo (struct ure_softc*) ; 
 int ure_ocp_reg_read (struct ure_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_ocp_reg_write (struct ure_softc*,int /*<<< orphan*/ ,int) ; 
 int ure_read_1 (struct ure_softc*,int /*<<< orphan*/ ,int) ; 
 int ure_read_2 (struct ure_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ure_write_1 (struct ure_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ure_write_2 (struct ure_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ure_write_mem (struct ure_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ure_rtl8153_init(struct ure_softc *sc)
{
	uint16_t val;
	uint8_t u1u2[8];
	int i;

	/* Disable ALDPS. */
	ure_ocp_reg_write(sc, URE_OCP_POWER_CFG,
	    ure_ocp_reg_read(sc, URE_OCP_POWER_CFG) & ~URE_EN_ALDPS);
	uether_pause(&sc->sc_ue, hz / 50);

	memset(u1u2, 0x00, sizeof(u1u2));
	ure_write_mem(sc, URE_USB_TOLERANCE,
	    URE_MCU_TYPE_USB | URE_BYTE_EN_SIX_BYTES, u1u2, sizeof(u1u2));

        for (i = 0; i < URE_TIMEOUT; i++) {
		if (ure_read_2(sc, URE_PLA_BOOT_CTRL, URE_MCU_TYPE_PLA) &
		    URE_AUTOLOAD_DONE)
			break;
		uether_pause(&sc->sc_ue, hz / 100);
	}
	if (i == URE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev,
		    "timeout waiting for chip autoload\n");

        for (i = 0; i < URE_TIMEOUT; i++) {
		val = ure_ocp_reg_read(sc, URE_OCP_PHY_STATUS) &
		    URE_PHY_STAT_MASK;
		if (val == URE_PHY_STAT_LAN_ON || val == URE_PHY_STAT_PWRDN)
			break;
		uether_pause(&sc->sc_ue, hz / 100);
	}
	if (i == URE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev,
		    "timeout waiting for phy to stabilize\n");
	
	ure_write_2(sc, URE_USB_U2P3_CTRL, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_U2P3_CTRL, URE_MCU_TYPE_USB) &
	    ~URE_U2P3_ENABLE);

	if (sc->sc_chip & URE_CHIP_VER_5C10) {
		val = ure_read_2(sc, URE_USB_SSPHYLINK2, URE_MCU_TYPE_USB);
		val &= ~URE_PWD_DN_SCALE_MASK;
		val |= URE_PWD_DN_SCALE(96);
		ure_write_2(sc, URE_USB_SSPHYLINK2, URE_MCU_TYPE_USB, val);

		ure_write_1(sc, URE_USB_USB2PHY, URE_MCU_TYPE_USB,
		    ure_read_1(sc, URE_USB_USB2PHY, URE_MCU_TYPE_USB) |
		    URE_USB2PHY_L1 | URE_USB2PHY_SUSPEND);
	} else if (sc->sc_chip & URE_CHIP_VER_5C20) {
		ure_write_1(sc, URE_PLA_DMY_REG0, URE_MCU_TYPE_PLA,
		    ure_read_1(sc, URE_PLA_DMY_REG0, URE_MCU_TYPE_PLA) &
		    ~URE_ECM_ALDPS);
	}
	if (sc->sc_chip & (URE_CHIP_VER_5C20 | URE_CHIP_VER_5C30)) {
		val = ure_read_1(sc, URE_USB_CSR_DUMMY1, URE_MCU_TYPE_USB);
		if (ure_read_2(sc, URE_USB_BURST_SIZE, URE_MCU_TYPE_USB) ==
		    0)
			val &= ~URE_DYNAMIC_BURST;
		else
			val |= URE_DYNAMIC_BURST;
		ure_write_1(sc, URE_USB_CSR_DUMMY1, URE_MCU_TYPE_USB, val);
	}

	ure_write_1(sc, URE_USB_CSR_DUMMY2, URE_MCU_TYPE_USB,
	    ure_read_1(sc, URE_USB_CSR_DUMMY2, URE_MCU_TYPE_USB) |
	    URE_EP4_FULL_FC);
	
	ure_write_2(sc, URE_USB_WDT11_CTRL, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_WDT11_CTRL, URE_MCU_TYPE_USB) &
	    ~URE_TIMER11_EN);

	ure_write_2(sc, URE_PLA_LED_FEATURE, URE_MCU_TYPE_PLA,
	    ure_read_2(sc, URE_PLA_LED_FEATURE, URE_MCU_TYPE_PLA) &
	    ~URE_LED_MODE_MASK);
	    
	if ((sc->sc_chip & URE_CHIP_VER_5C10) &&
	    usbd_get_speed(sc->sc_ue.ue_udev) != USB_SPEED_SUPER)
		val = URE_LPM_TIMER_500MS;
	else
		val = URE_LPM_TIMER_500US;
	ure_write_1(sc, URE_USB_LPM_CTRL, URE_MCU_TYPE_USB,
	    val | URE_FIFO_EMPTY_1FB | URE_ROK_EXIT_LPM);

	val = ure_read_2(sc, URE_USB_AFE_CTRL2, URE_MCU_TYPE_USB);
	val &= ~URE_SEN_VAL_MASK;
	val |= URE_SEN_VAL_NORMAL | URE_SEL_RXIDLE;
	ure_write_2(sc, URE_USB_AFE_CTRL2, URE_MCU_TYPE_USB, val);

	ure_write_2(sc, URE_USB_CONNECT_TIMER, URE_MCU_TYPE_USB, 0x0001);

	ure_write_2(sc, URE_USB_POWER_CUT, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_POWER_CUT, URE_MCU_TYPE_USB) &
	    ~(URE_PWR_EN | URE_PHASE2_EN));
	ure_write_2(sc, URE_USB_MISC_0, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_MISC_0, URE_MCU_TYPE_USB) &
	    ~URE_PCUT_STATUS);

	memset(u1u2, 0xff, sizeof(u1u2));
	ure_write_mem(sc, URE_USB_TOLERANCE,
	    URE_MCU_TYPE_USB | URE_BYTE_EN_SIX_BYTES, u1u2, sizeof(u1u2));

	ure_write_2(sc, URE_PLA_MAC_PWR_CTRL, URE_MCU_TYPE_PLA,
	    URE_ALDPS_SPDWN_RATIO);
	ure_write_2(sc, URE_PLA_MAC_PWR_CTRL2, URE_MCU_TYPE_PLA,
	    URE_EEE_SPDWN_RATIO);
	ure_write_2(sc, URE_PLA_MAC_PWR_CTRL3, URE_MCU_TYPE_PLA,
	    URE_PKT_AVAIL_SPDWN_EN | URE_SUSPEND_SPDWN_EN |
	    URE_U1U2_SPDWN_EN | URE_L1_SPDWN_EN);
	ure_write_2(sc, URE_PLA_MAC_PWR_CTRL4, URE_MCU_TYPE_PLA,
	    URE_PWRSAVE_SPDWN_EN | URE_RXDV_SPDWN_EN | URE_TX10MIDLE_EN |
	    URE_TP100_SPDWN_EN | URE_TP500_SPDWN_EN | URE_TP1000_SPDWN_EN |
	    URE_EEE_SPDWN_EN);

	val = ure_read_2(sc, URE_USB_U2P3_CTRL, URE_MCU_TYPE_USB);
	if (!(sc->sc_chip & (URE_CHIP_VER_5C00 | URE_CHIP_VER_5C10)))
		val |= URE_U2P3_ENABLE;
	else
		val &= ~URE_U2P3_ENABLE;
	ure_write_2(sc, URE_USB_U2P3_CTRL, URE_MCU_TYPE_USB, val);

	memset(u1u2, 0x00, sizeof(u1u2));
        ure_write_mem(sc, URE_USB_TOLERANCE,
	    URE_MCU_TYPE_USB | URE_BYTE_EN_SIX_BYTES, u1u2, sizeof(u1u2));

	/* Disable ALDPS. */
	ure_ocp_reg_write(sc, URE_OCP_POWER_CFG,
	    ure_ocp_reg_read(sc, URE_OCP_POWER_CFG) & ~URE_EN_ALDPS);
	uether_pause(&sc->sc_ue, hz / 50);

	ure_init_fifo(sc);

	/* Disable Rx aggregation. */
	ure_write_2(sc, URE_USB_USB_CTRL, URE_MCU_TYPE_USB,
	    ure_read_2(sc, URE_USB_USB_CTRL, URE_MCU_TYPE_USB) |
	    URE_RX_AGG_DISABLE);

	val = ure_read_2(sc, URE_USB_U2P3_CTRL, URE_MCU_TYPE_USB);
	if (!(sc->sc_chip & (URE_CHIP_VER_5C00 | URE_CHIP_VER_5C10)))
		val |= URE_U2P3_ENABLE;
	else
		val &= ~URE_U2P3_ENABLE;
	ure_write_2(sc, URE_USB_U2P3_CTRL, URE_MCU_TYPE_USB, val);

	memset(u1u2, 0xff, sizeof(u1u2));
	ure_write_mem(sc, URE_USB_TOLERANCE,
	    URE_MCU_TYPE_USB | URE_BYTE_EN_SIX_BYTES, u1u2, sizeof(u1u2));
}