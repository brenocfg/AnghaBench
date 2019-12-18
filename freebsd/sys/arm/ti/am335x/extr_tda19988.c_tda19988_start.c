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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct tda19988_softc {int sc_version; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CEC_FRO_IM_CLK_CTRL_GHOST_DIS ; 
 int CEC_FRO_IM_CLK_CTRL_IMCLK_SEL ; 
 int DDC_ENABLE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENAMODS_HDMI ; 
 int ENAMODS_RXSENS ; 
 int MAIN_CNTRL0_SR ; 
 int PLL_SERIAL_2_SRL_NOSC (int) ; 
 int SEL_CLK_ENA_SC_CLK ; 
 int SEL_CLK_SEL_CLK1 ; 
#define  TDA19988 128 
 int /*<<< orphan*/  TDA_BUFFER_OUT ; 
 int /*<<< orphan*/  TDA_CEC_ENAMODS ; 
 int /*<<< orphan*/  TDA_CEC_FRO_IM_CLK_CTRL ; 
 int /*<<< orphan*/  TDA_DDC_CTRL ; 
 int /*<<< orphan*/  TDA_MAIN_CNTRL0 ; 
 int /*<<< orphan*/  TDA_MUX_VP_VIP_OUT ; 
 int /*<<< orphan*/  TDA_PLL_SCG1 ; 
 int /*<<< orphan*/  TDA_PLL_SCG2 ; 
 int /*<<< orphan*/  TDA_PLL_SCGN1 ; 
 int /*<<< orphan*/  TDA_PLL_SCGN2 ; 
 int /*<<< orphan*/  TDA_PLL_SCGR1 ; 
 int /*<<< orphan*/  TDA_PLL_SCGR2 ; 
 int /*<<< orphan*/  TDA_PLL_SERIAL_1 ; 
 int /*<<< orphan*/  TDA_PLL_SERIAL_2 ; 
 int /*<<< orphan*/  TDA_PLL_SERIAL_3 ; 
 int /*<<< orphan*/  TDA_SEL_CLK ; 
 int /*<<< orphan*/  TDA_SERIALIZER ; 
 int /*<<< orphan*/  TDA_SOFTRESET ; 
 int /*<<< orphan*/  TDA_TX3 ; 
 int /*<<< orphan*/  TDA_VERSION ; 
 int /*<<< orphan*/  TDA_VERSION_MSB ; 
 int /*<<< orphan*/  TDA_VIP_CNTRL_0 ; 
 int /*<<< orphan*/  TDA_VIP_CNTRL_1 ; 
 int /*<<< orphan*/  TDA_VIP_CNTRL_2 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tda19988_cec_read (struct tda19988_softc*,int,int*) ; 
 int /*<<< orphan*/  tda19988_cec_write (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tda19988_read_edid (struct tda19988_softc*) ; 
 int /*<<< orphan*/  tda19988_reg_clear (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda19988_reg_read (struct tda19988_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tda19988_reg_set (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda19988_reg_write (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tda19988_start(struct tda19988_softc *sc)
{
	device_t dev;
	uint8_t data;
	uint16_t version;

	dev = sc->sc_dev;
	
	tda19988_cec_write(sc, TDA_CEC_ENAMODS, ENAMODS_RXSENS | ENAMODS_HDMI);
	DELAY(1000);
	tda19988_cec_read(sc, 0xfe, &data);

	/* Reset core */
	tda19988_reg_set(sc, TDA_SOFTRESET, 3);
	DELAY(100);
	tda19988_reg_clear(sc, TDA_SOFTRESET, 3);
	DELAY(100);

	/* reset transmitter: */
	tda19988_reg_set(sc, TDA_MAIN_CNTRL0, MAIN_CNTRL0_SR);
	tda19988_reg_clear(sc, TDA_MAIN_CNTRL0, MAIN_CNTRL0_SR);

	/* PLL registers common configuration */
	tda19988_reg_write(sc, TDA_PLL_SERIAL_1, 0x00);
	tda19988_reg_write(sc, TDA_PLL_SERIAL_2, PLL_SERIAL_2_SRL_NOSC(1));
	tda19988_reg_write(sc, TDA_PLL_SERIAL_3, 0x00);
	tda19988_reg_write(sc, TDA_SERIALIZER, 0x00);
	tda19988_reg_write(sc, TDA_BUFFER_OUT, 0x00);
	tda19988_reg_write(sc, TDA_PLL_SCG1, 0x00);
	tda19988_reg_write(sc, TDA_SEL_CLK, SEL_CLK_SEL_CLK1 | SEL_CLK_ENA_SC_CLK);
	tda19988_reg_write(sc, TDA_PLL_SCGN1, 0xfa);
	tda19988_reg_write(sc, TDA_PLL_SCGN2, 0x00);
	tda19988_reg_write(sc, TDA_PLL_SCGR1, 0x5b);
	tda19988_reg_write(sc, TDA_PLL_SCGR2, 0x00);
	tda19988_reg_write(sc, TDA_PLL_SCG2, 0x10);

	/* Write the default value MUX register */
	tda19988_reg_write(sc, TDA_MUX_VP_VIP_OUT, 0x24);

	version = 0;
	tda19988_reg_read(sc, TDA_VERSION, &data);
	version |= data;
	tda19988_reg_read(sc, TDA_VERSION_MSB, &data);
	version |= (data << 8);

	/* Clear feature bits */
	sc->sc_version = version & ~0x30;
	switch (sc->sc_version) {
		case TDA19988:
			device_printf(dev, "TDA19988\n");
			break;
		default:
			device_printf(dev, "Unknown device: %04x\n", sc->sc_version);
			return;
	}

	tda19988_reg_write(sc, TDA_DDC_CTRL, DDC_ENABLE);
	tda19988_reg_write(sc, TDA_TX3, 39);

    	tda19988_cec_write(sc, TDA_CEC_FRO_IM_CLK_CTRL,
            CEC_FRO_IM_CLK_CTRL_GHOST_DIS | CEC_FRO_IM_CLK_CTRL_IMCLK_SEL);

	if (tda19988_read_edid(sc) < 0) {
		device_printf(dev, "failed to read EDID\n");
		return;
	}

	/* Default values for RGB 4:4:4 mapping */
	tda19988_reg_write(sc, TDA_VIP_CNTRL_0, 0x23);
	tda19988_reg_write(sc, TDA_VIP_CNTRL_1, 0x01);
	tda19988_reg_write(sc, TDA_VIP_CNTRL_2, 0x45);
}