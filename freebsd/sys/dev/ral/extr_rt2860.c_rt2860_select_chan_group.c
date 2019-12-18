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
typedef  int uint32_t ;
struct rt2860_softc {int* lna; int nrxchains; int mac_ver; int ntxchains; int sc_flags; scalar_t__ ext_5ghz_lna; scalar_t__ ext_2ghz_lna; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2860_5G_BAND_SEL_N ; 
 int RT2860_5G_BAND_SEL_P ; 
 int /*<<< orphan*/  RT2860_GPIO_CTRL ; 
 int RT2860_LNA_PE0_EN ; 
 int RT2860_LNA_PE1_EN ; 
 int RT2860_PA_PE_A0_EN ; 
 int RT2860_PA_PE_A1_EN ; 
 int RT2860_PA_PE_G0_EN ; 
 int RT2860_PA_PE_G1_EN ; 
 int RT2860_PCIE ; 
 int RT2860_RFTR_EN ; 
 int RT2860_TRSW_EN ; 
 int /*<<< orphan*/  RT2860_TX_BAND_CFG ; 
 int /*<<< orphan*/  RT2860_TX_PIN_CFG ; 
 int RT3593_LNA_PE2_EN ; 
 int RT3593_PA_PE_A2_EN ; 
 int RT3593_PA_PE_G2_EN ; 
 int /*<<< orphan*/  rt2860_mcu_bbp_write (struct rt2860_softc*,int,int) ; 

__attribute__((used)) static void
rt2860_select_chan_group(struct rt2860_softc *sc, int group)
{
	uint32_t tmp;
	uint8_t agc;

	rt2860_mcu_bbp_write(sc, 62, 0x37 - sc->lna[group]);
	rt2860_mcu_bbp_write(sc, 63, 0x37 - sc->lna[group]);
	rt2860_mcu_bbp_write(sc, 64, 0x37 - sc->lna[group]);
	rt2860_mcu_bbp_write(sc, 86, 0x00);

	if (group == 0) {
		if (sc->ext_2ghz_lna) {
			rt2860_mcu_bbp_write(sc, 82, 0x62);
			rt2860_mcu_bbp_write(sc, 75, 0x46);
		} else {
			rt2860_mcu_bbp_write(sc, 82, 0x84);
			rt2860_mcu_bbp_write(sc, 75, 0x50);
		}
	} else {
		if (sc->ext_5ghz_lna) {
			rt2860_mcu_bbp_write(sc, 82, 0xf2);
			rt2860_mcu_bbp_write(sc, 75, 0x46);
		} else {
			rt2860_mcu_bbp_write(sc, 82, 0xf2);
			rt2860_mcu_bbp_write(sc, 75, 0x50);
		}
	}

	tmp = RAL_READ(sc, RT2860_TX_BAND_CFG);
	tmp &= ~(RT2860_5G_BAND_SEL_N | RT2860_5G_BAND_SEL_P);
	tmp |= (group == 0) ? RT2860_5G_BAND_SEL_N : RT2860_5G_BAND_SEL_P;
	RAL_WRITE(sc, RT2860_TX_BAND_CFG, tmp);

	/* enable appropriate Power Amplifiers and Low Noise Amplifiers */
	tmp = RT2860_RFTR_EN | RT2860_TRSW_EN | RT2860_LNA_PE0_EN;
	if (sc->nrxchains > 1)
		tmp |= RT2860_LNA_PE1_EN;
	if (sc->mac_ver == 0x3593 && sc->nrxchains > 2)
		tmp |= RT3593_LNA_PE2_EN;
	if (group == 0) {	/* 2GHz */
		tmp |= RT2860_PA_PE_G0_EN;
		if (sc->ntxchains > 1)
			tmp |= RT2860_PA_PE_G1_EN;
		if (sc->mac_ver == 0x3593 && sc->ntxchains > 2)
			tmp |= RT3593_PA_PE_G2_EN;
	} else {		/* 5GHz */
		tmp |= RT2860_PA_PE_A0_EN;
		if (sc->ntxchains > 1)
			tmp |= RT2860_PA_PE_A1_EN;
		if (sc->mac_ver == 0x3593 && sc->ntxchains > 2)
			tmp |= RT3593_PA_PE_A2_EN;
	}
	RAL_WRITE(sc, RT2860_TX_PIN_CFG, tmp);

	if (sc->mac_ver == 0x3593) {
		tmp = RAL_READ(sc, RT2860_GPIO_CTRL);
		if (sc->sc_flags & RT2860_PCIE) {
			tmp &= ~0x01010000;
			if (group == 0)
				tmp |= 0x00010000;
		} else {
			tmp &= ~0x00008080;
			if (group == 0)
				tmp |= 0x00000080;
		}
		tmp = (tmp & ~0x00001000) | 0x00000010;
		RAL_WRITE(sc, RT2860_GPIO_CTRL, tmp);
	}

	/* set initial AGC value */
	if (group == 0) {	/* 2GHz band */
		if (sc->mac_ver >= 0x3071)
			agc = 0x1c + sc->lna[0] * 2;
		else
			agc = 0x2e + sc->lna[0];
	} else {		/* 5GHz band */
		agc = 0x32 + (sc->lna[group] * 5) / 3;
	}
	rt2860_mcu_bbp_write(sc, 66, agc);

	DELAY(1000);
}