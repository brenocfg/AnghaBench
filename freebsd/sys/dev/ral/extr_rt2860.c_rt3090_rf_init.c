#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct rt2860_softc {int mac_rev; int mac_ver; int rf24_20mhz; int rf24_40mhz; scalar_t__ rf_rev; int ntxchains; int nrxchains; int txmixgain_2ghz; int /*<<< orphan*/  ext_2ghz_lna; scalar_t__ patch_dac; } ;
struct TYPE_3__ {int reg; int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT3070_GPIO_SWITCH ; 
 int /*<<< orphan*/  RT3070_LDO_CFG0 ; 
 int /*<<< orphan*/  RT3070_OPT_14 ; 
 scalar_t__ RT3070_RF_3020 ; 
 int RT3070_RF_BLOCK ; 
 int RT3070_RX0_PD ; 
 int RT3070_RX1_PD ; 
 int RT3070_RX_LO1 ; 
 int RT3070_RX_LO2 ; 
 int RT3070_TX0_PD ; 
 int RT3070_TX1_PD ; 
 int RT3070_TX_LO1 ; 
 int RT3070_TX_LO2 ; 
 int nitems (TYPE_1__*) ; 
 int rt2860_mcu_bbp_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt2860_mcu_bbp_write (struct rt2860_softc*,int,int) ; 
 TYPE_1__* rt3090_def_rf ; 
 int /*<<< orphan*/  rt3090_filter_calib (struct rt2860_softc*,int,int,int*) ; 
 int rt3090_rf_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt3090_rf_write (struct rt2860_softc*,int,int) ; 
 int /*<<< orphan*/  rt3090_set_rx_antenna (struct rt2860_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt3090_rf_init(struct rt2860_softc *sc)
{
	uint32_t tmp;
	uint8_t rf, bbp;
	int i;

	rf = rt3090_rf_read(sc, 30);
	/* toggle RF R30 bit 7 */
	rt3090_rf_write(sc, 30, rf | 0x80);
	DELAY(1000);
	rt3090_rf_write(sc, 30, rf & ~0x80);

	tmp = RAL_READ(sc, RT3070_LDO_CFG0);
	tmp &= ~0x1f000000;
	if (sc->patch_dac && sc->mac_rev < 0x0211)
		tmp |= 0x0d000000;	/* 1.35V */
	else
		tmp |= 0x01000000;	/* 1.2V */
	RAL_WRITE(sc, RT3070_LDO_CFG0, tmp);

	/* patch LNA_PE_G1 */
	tmp = RAL_READ(sc, RT3070_GPIO_SWITCH);
	RAL_WRITE(sc, RT3070_GPIO_SWITCH, tmp & ~0x20);

	/* initialize RF registers to default value */
	for (i = 0; i < nitems(rt3090_def_rf); i++) {
		rt3090_rf_write(sc, rt3090_def_rf[i].reg,
		    rt3090_def_rf[i].val);
	}

	/* select 20MHz bandwidth */
	rt3090_rf_write(sc, 31, 0x14);

	rf = rt3090_rf_read(sc, 6);
	rt3090_rf_write(sc, 6, rf | 0x40);

	if (sc->mac_ver != 0x3593) {
		/* calibrate filter for 20MHz bandwidth */
		sc->rf24_20mhz = 0x1f;	/* default value */
		rt3090_filter_calib(sc, 0x07, 0x16, &sc->rf24_20mhz);

		/* select 40MHz bandwidth */
		bbp = rt2860_mcu_bbp_read(sc, 4);
		rt2860_mcu_bbp_write(sc, 4, (bbp & ~0x08) | 0x10);
		rf = rt3090_rf_read(sc, 31);
		rt3090_rf_write(sc, 31, rf | 0x20);

		/* calibrate filter for 40MHz bandwidth */
		sc->rf24_40mhz = 0x2f;	/* default value */
		rt3090_filter_calib(sc, 0x27, 0x19, &sc->rf24_40mhz);

		/* go back to 20MHz bandwidth */
		bbp = rt2860_mcu_bbp_read(sc, 4);
		rt2860_mcu_bbp_write(sc, 4, bbp & ~0x18);
	}
	if (sc->mac_rev < 0x0211)
		rt3090_rf_write(sc, 27, 0x03);

	tmp = RAL_READ(sc, RT3070_OPT_14);
	RAL_WRITE(sc, RT3070_OPT_14, tmp | 1);

	if (sc->rf_rev == RT3070_RF_3020)
		rt3090_set_rx_antenna(sc, 0);

	bbp = rt2860_mcu_bbp_read(sc, 138);
	if (sc->mac_ver == 0x3593) {
		if (sc->ntxchains == 1)
			bbp |= 0x60;	/* turn off DAC1 and DAC2 */
		else if (sc->ntxchains == 2)
			bbp |= 0x40;	/* turn off DAC2 */
		if (sc->nrxchains == 1)
			bbp &= ~0x06;	/* turn off ADC1 and ADC2 */
		else if (sc->nrxchains == 2)
			bbp &= ~0x04;	/* turn off ADC2 */
	} else {
		if (sc->ntxchains == 1)
			bbp |= 0x20;	/* turn off DAC1 */
		if (sc->nrxchains == 1)
			bbp &= ~0x02;	/* turn off ADC1 */
	}
	rt2860_mcu_bbp_write(sc, 138, bbp);

	rf = rt3090_rf_read(sc, 1);
	rf &= ~(RT3070_RX0_PD | RT3070_TX0_PD);
	rf |= RT3070_RF_BLOCK | RT3070_RX1_PD | RT3070_TX1_PD;
	rt3090_rf_write(sc, 1, rf);

	rf = rt3090_rf_read(sc, 15);
	rt3090_rf_write(sc, 15, rf & ~RT3070_TX_LO2);

	rf = rt3090_rf_read(sc, 17);
	rf &= ~RT3070_TX_LO1;
	if (sc->mac_rev >= 0x0211 && !sc->ext_2ghz_lna)
		rf |= 0x20;	/* fix for long range Rx issue */
	if (sc->txmixgain_2ghz >= 2)
		rf = (rf & ~0x7) | sc->txmixgain_2ghz;
	rt3090_rf_write(sc, 17, rf);

	rf = rt3090_rf_read(sc, 20);
	rt3090_rf_write(sc, 20, rf & ~RT3070_RX_LO1);

	rf = rt3090_rf_read(sc, 21);
	rt3090_rf_write(sc, 21, rf & ~RT3070_RX_LO2);

	return (0);
}