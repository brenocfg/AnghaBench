#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct rt2860_softc {int mac_ver; int rf24_20mhz; int rf24_40mhz; int mac_rev; int ntxchains; int nrxchains; } ;
struct TYPE_4__ {int reg; int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2860_TX_SW_CFG1 ; 
 int /*<<< orphan*/  RT2860_TX_SW_CFG2 ; 
 int /*<<< orphan*/  RT3070_OPT_14 ; 
 int RT3593_RESCAL ; 
 int RT5390_MAC_IF_CTRL ; 
 int RT5390_RX_LO1 ; 
 int RT5390_RX_LO2 ; 
 int nitems (TYPE_1__*) ; 
 int rt2860_mcu_bbp_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt2860_mcu_bbp_write (struct rt2860_softc*,int,int) ; 
 int rt3090_rf_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt3090_rf_write (struct rt2860_softc*,int,int) ; 
 int /*<<< orphan*/  rt3090_set_rx_antenna (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rt5390_def_rf ; 
 TYPE_1__* rt5392_def_rf ; 

__attribute__((used)) static void
rt5390_rf_init(struct rt2860_softc *sc)
{
	uint8_t rf, bbp;
	int i;

	rf = rt3090_rf_read(sc, 2);
	/* Toggle RF R2 bit 7. */
	rt3090_rf_write(sc, 2, rf | RT3593_RESCAL);
	DELAY(1000);
	rt3090_rf_write(sc, 2, rf & ~RT3593_RESCAL);

	/* Initialize RF registers to default value. */
	if (sc->mac_ver == 0x5392) {
		for (i = 0; i < nitems(rt5392_def_rf); i++) {
			rt3090_rf_write(sc, rt5392_def_rf[i].reg,
			    rt5392_def_rf[i].val);
		}
	} else {
		for (i = 0; i < nitems(rt5390_def_rf); i++) {
			rt3090_rf_write(sc, rt5390_def_rf[i].reg,
			    rt5390_def_rf[i].val);
		}
	}

	sc->rf24_20mhz = 0x1f;
	sc->rf24_40mhz = 0x2f;

	if (sc->mac_rev < 0x0211)
		rt3090_rf_write(sc, 27, 0x03);

	/* Set led open drain enable. */
	RAL_WRITE(sc, RT3070_OPT_14, RAL_READ(sc, RT3070_OPT_14) | 1);

	RAL_WRITE(sc, RT2860_TX_SW_CFG1, 0);
	RAL_WRITE(sc, RT2860_TX_SW_CFG2, 0);

	if (sc->mac_ver == 0x5390)
		rt3090_set_rx_antenna(sc, 0);

	/* Patch RSSI inaccurate issue. */
	rt2860_mcu_bbp_write(sc, 79, 0x13);
	rt2860_mcu_bbp_write(sc, 80, 0x05);
	rt2860_mcu_bbp_write(sc, 81, 0x33);

	/* Enable DC filter. */
	if (sc->mac_rev >= 0x0211)
		rt2860_mcu_bbp_write(sc, 103, 0xc0);

	bbp = rt2860_mcu_bbp_read(sc, 138);
	if (sc->ntxchains == 1)
		bbp |= 0x20;	/* Turn off DAC1. */
	if (sc->nrxchains == 1)
		bbp &= ~0x02;	/* Turn off ADC1. */
	rt2860_mcu_bbp_write(sc, 138, bbp);

	/* Enable RX LO1 and LO2. */
	rt3090_rf_write(sc, 38, rt3090_rf_read(sc, 38) & ~RT5390_RX_LO1);
	rt3090_rf_write(sc, 39, rt3090_rf_read(sc, 39) & ~RT5390_RX_LO2);

	/* Avoid data lost and CRC error. */
	rt2860_mcu_bbp_write(sc, 4,
	    rt2860_mcu_bbp_read(sc, 4) | RT5390_MAC_IF_CTRL);

	rf = rt3090_rf_read(sc, 30);
	rf = (rf & ~0x18) | 0x10;
	rt3090_rf_write(sc, 30, rf);
}