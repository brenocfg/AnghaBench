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
struct run_softc {int* lna; int mac_ver; int nrxchains; int ntxchains; scalar_t__ ext_5ghz_lna; scalar_t__ ext_2ghz_lna; } ;

/* Variables and functions */
 int RT2860_5G_BAND_SEL_N ; 
 int RT2860_5G_BAND_SEL_P ; 
 int /*<<< orphan*/  RT2860_GPIO_CTRL ; 
 int RT2860_LNA_PE0_EN ; 
 int RT2860_LNA_PE1_EN ; 
 int RT2860_PA_PE_A0_EN ; 
 int RT2860_PA_PE_A1_EN ; 
 int RT2860_PA_PE_G0_EN ; 
 int RT2860_PA_PE_G1_EN ; 
 int RT2860_RFTR_EN ; 
 int RT2860_TRSW_EN ; 
 int /*<<< orphan*/  RT2860_TX_BAND_CFG ; 
 int /*<<< orphan*/  RT2860_TX_PIN_CFG ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  run_rt3070_rf_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_set_agc (struct run_softc*,int) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_select_chan_group(struct run_softc *sc, int group)
{
	uint32_t tmp;
	uint8_t agc;

	run_bbp_write(sc, 62, 0x37 - sc->lna[group]);
	run_bbp_write(sc, 63, 0x37 - sc->lna[group]);
	run_bbp_write(sc, 64, 0x37 - sc->lna[group]);
	if (sc->mac_ver < 0x3572)
		run_bbp_write(sc, 86, 0x00);

	if (sc->mac_ver == 0x3593) {
		run_bbp_write(sc, 77, 0x98);
		run_bbp_write(sc, 83, (group == 0) ? 0x8a : 0x9a);
	}

	if (group == 0) {
		if (sc->ext_2ghz_lna) {
			if (sc->mac_ver >= 0x5390)
				run_bbp_write(sc, 75, 0x52);
			else {
				run_bbp_write(sc, 82, 0x62);
				run_bbp_write(sc, 75, 0x46);
			}
		} else {
			if (sc->mac_ver == 0x5592) {
				run_bbp_write(sc, 79, 0x1c);
				run_bbp_write(sc, 80, 0x0e);
				run_bbp_write(sc, 81, 0x3a);
				run_bbp_write(sc, 82, 0x62);

				run_bbp_write(sc, 195, 0x80);
				run_bbp_write(sc, 196, 0xe0);
				run_bbp_write(sc, 195, 0x81);
				run_bbp_write(sc, 196, 0x1f);
				run_bbp_write(sc, 195, 0x82);
				run_bbp_write(sc, 196, 0x38);
				run_bbp_write(sc, 195, 0x83);
				run_bbp_write(sc, 196, 0x32);
				run_bbp_write(sc, 195, 0x85);
				run_bbp_write(sc, 196, 0x28);
				run_bbp_write(sc, 195, 0x86);
				run_bbp_write(sc, 196, 0x19);
			} else if (sc->mac_ver >= 0x5390)
				run_bbp_write(sc, 75, 0x50);
			else {
				run_bbp_write(sc, 82,
				    (sc->mac_ver == 0x3593) ? 0x62 : 0x84);
				run_bbp_write(sc, 75, 0x50);
			}
		}
	} else {
		if (sc->mac_ver == 0x5592) {
			run_bbp_write(sc, 79, 0x18);
			run_bbp_write(sc, 80, 0x08);
			run_bbp_write(sc, 81, 0x38);
			run_bbp_write(sc, 82, 0x92);

			run_bbp_write(sc, 195, 0x80);
			run_bbp_write(sc, 196, 0xf0);
			run_bbp_write(sc, 195, 0x81);
			run_bbp_write(sc, 196, 0x1e);
			run_bbp_write(sc, 195, 0x82);
			run_bbp_write(sc, 196, 0x28);
			run_bbp_write(sc, 195, 0x83);
			run_bbp_write(sc, 196, 0x20);
			run_bbp_write(sc, 195, 0x85);
			run_bbp_write(sc, 196, 0x7f);
			run_bbp_write(sc, 195, 0x86);
			run_bbp_write(sc, 196, 0x7f);
		} else if (sc->mac_ver == 0x3572)
			run_bbp_write(sc, 82, 0x94);
		else
			run_bbp_write(sc, 82,
			    (sc->mac_ver == 0x3593) ? 0x82 : 0xf2);
		if (sc->ext_5ghz_lna)
			run_bbp_write(sc, 75, 0x46);
		else 
			run_bbp_write(sc, 75, 0x50);
	}

	run_read(sc, RT2860_TX_BAND_CFG, &tmp);
	tmp &= ~(RT2860_5G_BAND_SEL_N | RT2860_5G_BAND_SEL_P);
	tmp |= (group == 0) ? RT2860_5G_BAND_SEL_N : RT2860_5G_BAND_SEL_P;
	run_write(sc, RT2860_TX_BAND_CFG, tmp);

	/* enable appropriate Power Amplifiers and Low Noise Amplifiers */
	tmp = RT2860_RFTR_EN | RT2860_TRSW_EN | RT2860_LNA_PE0_EN;
	if (sc->mac_ver == 0x3593)
		tmp |= 1 << 29 | 1 << 28;
	if (sc->nrxchains > 1)
		tmp |= RT2860_LNA_PE1_EN;
	if (group == 0) {	/* 2GHz */
		tmp |= RT2860_PA_PE_G0_EN;
		if (sc->ntxchains > 1)
			tmp |= RT2860_PA_PE_G1_EN;
		if (sc->mac_ver == 0x3593) {
			if (sc->ntxchains > 2)
				tmp |= 1 << 25;
		}
	} else {		/* 5GHz */
		tmp |= RT2860_PA_PE_A0_EN;
		if (sc->ntxchains > 1)
			tmp |= RT2860_PA_PE_A1_EN;
	}
	if (sc->mac_ver == 0x3572) {
		run_rt3070_rf_write(sc, 8, 0x00);
		run_write(sc, RT2860_TX_PIN_CFG, tmp);
		run_rt3070_rf_write(sc, 8, 0x80);
	} else
		run_write(sc, RT2860_TX_PIN_CFG, tmp);

	if (sc->mac_ver == 0x5592) {
		run_bbp_write(sc, 195, 0x8d);
		run_bbp_write(sc, 196, 0x1a);
	}

	if (sc->mac_ver == 0x3593) {
		run_read(sc, RT2860_GPIO_CTRL, &tmp);
		tmp &= ~0x01010000;
		if (group == 0)
			tmp |= 0x00010000;
		tmp = (tmp & ~0x00009090) | 0x00000090;
		run_write(sc, RT2860_GPIO_CTRL, tmp);
	}

	/* set initial AGC value */
	if (group == 0) {	/* 2GHz band */
		if (sc->mac_ver >= 0x3070)
			agc = 0x1c + sc->lna[0] * 2;
		else
			agc = 0x2e + sc->lna[0];
	} else {		/* 5GHz band */
		if (sc->mac_ver == 0x5592)
			agc = 0x24 + sc->lna[group] * 2;
		else if (sc->mac_ver == 0x3572 || sc->mac_ver == 0x3593)
			agc = 0x22 + (sc->lna[group] * 5) / 3;
		else
			agc = 0x32 + (sc->lna[group] * 5) / 3;
	}
	run_set_agc(sc, agc);
}