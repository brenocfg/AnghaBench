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
struct rt2860_softc {int mac_ver; int mac_rev; scalar_t__ patch_dac; } ;

/* Variables and functions */
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT3070_LDO_CFG0 ; 
 int RT3070_RF_BLOCK ; 
 int RT3070_RX_CTB ; 
 int RT3593_CP_IC_MASK ; 
 int RT3593_CP_IC_SHIFT ; 
 int RT3593_LDO_PLL_VC_MASK ; 
 int RT3593_LDO_RF_VC_MASK ; 
 int RT3593_RESCAL ; 
 int RT3593_RX_CTB ; 
 int RT3593_VCO ; 
 int RT3593_VCOCAL ; 
 int RT3593_VCO_IC ; 
 int rt3090_rf_read (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt3090_rf_write (struct rt2860_softc*,int,int) ; 

__attribute__((used)) static void
rt3090_rf_wakeup(struct rt2860_softc *sc)
{
	uint32_t tmp;
	uint8_t rf;

	if (sc->mac_ver == 0x3593) {
		/* enable VCO */
		rf = rt3090_rf_read(sc, 1);
		rt3090_rf_write(sc, 1, rf | RT3593_VCO);

		/* initiate VCO calibration */
		rf = rt3090_rf_read(sc, 3);
		rt3090_rf_write(sc, 3, rf | RT3593_VCOCAL);

		/* enable VCO bias current control */
		rf = rt3090_rf_read(sc, 6);
		rt3090_rf_write(sc, 6, rf | RT3593_VCO_IC);

		/* initiate res calibration */
		rf = rt3090_rf_read(sc, 2);
		rt3090_rf_write(sc, 2, rf | RT3593_RESCAL);

		/* set reference current control to 0.33 mA */
		rf = rt3090_rf_read(sc, 22);
		rf &= ~RT3593_CP_IC_MASK;
		rf |= 1 << RT3593_CP_IC_SHIFT;
		rt3090_rf_write(sc, 22, rf);

		/* enable RX CTB */
		rf = rt3090_rf_read(sc, 46);
		rt3090_rf_write(sc, 46, rf | RT3593_RX_CTB);

		rf = rt3090_rf_read(sc, 20);
		rf &= ~(RT3593_LDO_RF_VC_MASK | RT3593_LDO_PLL_VC_MASK);
		rt3090_rf_write(sc, 20, rf);
	} else {
		/* enable RF block */
		rf = rt3090_rf_read(sc, 1);
		rt3090_rf_write(sc, 1, rf | RT3070_RF_BLOCK);

		/* enable VCO bias current control */
		rf = rt3090_rf_read(sc, 7);
		rt3090_rf_write(sc, 7, rf | 0x30);

		rf = rt3090_rf_read(sc, 9);
		rt3090_rf_write(sc, 9, rf | 0x0e);

		/* enable RX CTB */
		rf = rt3090_rf_read(sc, 21);
		rt3090_rf_write(sc, 21, rf | RT3070_RX_CTB);

		/* fix Tx to Rx IQ glitch by raising RF voltage */
		rf = rt3090_rf_read(sc, 27);
		rf &= ~0x77;
		if (sc->mac_rev < 0x0211)
			rf |= 0x03;
		rt3090_rf_write(sc, 27, rf);
	}
	if (sc->patch_dac && sc->mac_rev < 0x0211) {
		tmp = RAL_READ(sc, RT3070_LDO_CFG0);
		tmp = (tmp & ~0x1f000000) | 0x0d000000;
		RAL_WRITE(sc, RT3070_LDO_CFG0, tmp);
	}
}